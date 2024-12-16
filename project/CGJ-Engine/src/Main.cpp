#include <iostream>
#include <cassert>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader/ShaderProgram.h"
#include "mesh/Mesh.h"
#include "camera/Camera.h"
#include "input/KeyBuffer.h"
#include "scene/SceneGraph.h"
#include "scene/Animator.h"
#include "physics/Physics.h"
#include <malloc.h>
#include <time.h>
#include "skybox/CubeMap.h"
#include <vector>
#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "ImageCreator.h"


#define BLACK engine::Vertex({ 0.0f, 0.0f, 0.0f, 1.0f })
#define RED engine::Vertex({1.0f, 0.0f, 0.0f, 1.0f})
#define GREEN engine::Vertex({0.0f, 1.0f, 0.0f, 1.0f})
#define BLUE engine::Vertex({0.0f, 0.0f, 1.0f, 1.0f})
#define CYAN (BLUE + GREEN)
#define MAGENTA (BLUE + RED)
#define YELLOW (GREEN + RED)
#define WHITE (RED + GREEN + BLUE)

#define WOOD_BROWN engine::Vertex({0.6f, 0.4f, 0.2f, 1.0f})
#define TEST_1 engine::Vertex({0.63f, 0.52f, 0.44f, 1.0f})

const char* title = "Exodus Engine";

engine::ShaderProgram* shaderProgram;
engine::ShaderProgram* simpleDepthShader;
engine::ShaderProgram* skyboxShader;
engine::Cubemap* skybox;
engine::Camera* camera;
engine::SceneGraph* sceneGraph;
engine::SceneNode* ground, * ball, * ball2, * pin;
engine::Vector3 lightPos = engine::Vector3(1.0, 20.0, -10.0);
unsigned int depthMapFBO;
unsigned int depthMap;
const unsigned int SHADOW_WIDTH = 3840, SHADOW_HEIGHT = 2160;
const unsigned int WINDOW_WIDTH = 1024, WINDOW_HEIGHT = 720;
float turbPower = 1.0f;

bool firstFrame = true;

std::map<engine::SceneNode*, engine::Animator*>* animators = new std::map<engine::SceneNode*, engine::Animator*>();

////////////////////////////////////////////////// ERROR CALLBACK (OpenGL 4.3+)

static const std::string errorSource(GLenum source) {
	switch (source) {
	case GL_DEBUG_SOURCE_API:				return "API";
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		return "window system";
	case GL_DEBUG_SOURCE_SHADER_COMPILER:	return "shader compiler";
	case GL_DEBUG_SOURCE_THIRD_PARTY:		return "third party";
	case GL_DEBUG_SOURCE_APPLICATION:		return "application";
	case GL_DEBUG_SOURCE_OTHER:				return "other";
	default:								exit(EXIT_FAILURE);
	}
}

static const std::string errorType(GLenum type) {
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:				return "error";
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:	return "deprecated behavior";
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:	return "undefined behavior";
	case GL_DEBUG_TYPE_PORTABILITY:			return "portability issue";
	case GL_DEBUG_TYPE_PERFORMANCE:			return "performance issue";
	case GL_DEBUG_TYPE_MARKER:				return "stream annotation";
	case GL_DEBUG_TYPE_PUSH_GROUP:			return "push group";
	case GL_DEBUG_TYPE_POP_GROUP:			return "pop group";
	case GL_DEBUG_TYPE_OTHER_ARB:			return "other";
	default:								exit(EXIT_FAILURE);
	}
}

static const std::string errorSeverity(GLenum severity) {
	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:			return "high";
	case GL_DEBUG_SEVERITY_MEDIUM:			return "medium";
	case GL_DEBUG_SEVERITY_LOW:				return "low";
	case GL_DEBUG_SEVERITY_NOTIFICATION:	return "notification";
	default:								exit(EXIT_FAILURE);
	}
}

static void error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
		return;
	}

	std::cerr << "GL ERROR:" << std::endl;
	std::cerr << "  source:     " << errorSource(source) << std::endl;
	std::cerr << "  type:       " << errorType(type) << std::endl;
	std::cerr << "  severity:   " << errorSeverity(severity) << std::endl;
	std::cerr << "  debug call: " << std::endl << message << std::endl << std::endl;
	std::cerr << "Press <return>.";
	std::cin.ignore();
}

void setupErrorCallback() {
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(error, 0);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);
}

/////////////////////////////////////////////////////////////////////// SHADERs

void createShaderProgram() {
	std::ifstream vertexFile("vertex_shader.glsl");
	std::ifstream fragmentFile("fragment_shader.glsl");
	shaderProgram = new engine::ShaderProgram(&vertexFile, &fragmentFile, 0);

	std::ifstream vertexFile2("shadowVS.glsl");
	std::ifstream fragmentFile2("shadowFS.glsl");
	simpleDepthShader = new engine::ShaderProgram(&vertexFile2, &fragmentFile2, 1);

	std::ifstream vertexFile3("skyboxVS.glsl");
	std::ifstream fragmentFile3("skyboxFS.glsl");
	skyboxShader = new engine::ShaderProgram(&vertexFile3, &fragmentFile3, 2);
}

void createCamera(int winx, int winy) {
	camera = new engine::Camera(shaderProgram->getBinding("UBO_BP"), -10, 10, 10, -10, 0.5, 100, 30, winx, winy);
}

/////////////////////////////////////////////////////////////////////// SCENE

void createBase() {
	engine::Mesh* mesh = engine::Mesh::parseMesh("../../assets/models/ground.obj", shaderProgram);
	engine::Mesh* mesh2 = engine::Mesh::parseMesh("../../assets/models/ground.obj", simpleDepthShader);

	engine::Material* baseMaterial = engine::Material::parseMaterial(0.3f, 0.3f, 12, 1.0f, 2);
	engine::PerlinTexture* basePerlin = engine::PerlinTexture::parsePerlin();

	ground = sceneGraph->createNode();
	ground->setPerlinTexture(basePerlin);
	ground->setMesh(mesh->inColor(WOOD_BROWN));
	ground->setMaterial(baseMaterial);
	ground->setShadowMesh(mesh2->inColor(WOOD_BROWN));
	ground->setScale({ 7.0f, 0.5f, 20.0f });
	ground->setPosition({ 0.0f, -19.0f, 0.0f });
	ground->addComponent(engine::Physics::newRigidBody(0.0f));
	ground->addComponent(engine::Physics::newBoxCollider(mesh));

}

void createObjects() {
	engine::SceneNode* superglue = sceneGraph->createNode();
	superglue->setPosition({ 0.0f, 1.90f, 1/2.5f });

	engine::Mesh* ballMesh = engine::Mesh::parseMesh("../../assets/models/ball.obj", shaderProgram);
	engine::Mesh* pinMesh = engine::Mesh::parseMesh("../../assets/models/pin.obj", shaderProgram);

	engine::Mesh* ballMesh2 = engine::Mesh::parseMesh("../../assets/models/ball.obj", simpleDepthShader);
	engine::Mesh* pinMesh2 = engine::Mesh::parseMesh("../../assets/models/pin.obj", simpleDepthShader);
	
	engine::PerlinTexture* textPerlin = engine::PerlinTexture::parsePerlin();
	engine::Texture* crystalTexture = engine::Texture::parseTexture("../../assets/textures/glass.jpg");

	engine::Material* ballMaterial = engine::Material::parseMaterial(0.3f, 0.5f, 32.0f, 1.0f, 3);
	engine::Material* transparentMaterial = engine::Material::parseMaterial(0.3f, 0.5f, 32.0f, 0.7f, 0);
	engine::Material* pinMaterial = engine::Material::parseMaterial(0.2f, 0.3f, 24.0f, 1.0f, 1);
	
	pin = superglue->createNode();
	pin->setMesh(pinMesh->inColor(TEST_1));
	pin->setPerlinTexture(textPerlin);
	pin->setMaterial(pinMaterial);
	pin->setShadowMesh(pinMesh2->inColor(TEST_1));
	pin->setScale({ 1.5f, 1.5f, 1.5f });
	pin->setPosition({ 0.0f, -19.2f, -5.0f });
	pin->setRotation(engine::Quaternion::fromAngleAxis(90.0f, engine::Vector3(1.0f, 0.0f, 0.0f)));
	pin->addComponent(engine::Physics::newRigidBody(0.1f));
	pin->addComponent(engine::Physics::newBoxCollider(pinMesh));

	ball2 = superglue->createNode();
	ball2->setMesh(ballMesh->inColor(RED));
	ball2->setMaterial(ballMaterial);
	ball2->setPosition({ 0.0f, -19.3f, 0.0f });
	ball2->setShadowMesh(ballMesh2->inColor(RED));
	ball2->addComponent(engine::Physics::newRigidBody(1.0f));
	ball2->addComponent(engine::Physics::newBoxCollider(ballMesh));

	ball = superglue->createNode();
	ball->setMesh(ballMesh->inColor(TEST_1));
	//ball->setPerlinTexture(textPerlin);
	ball->setTexture(crystalTexture);
	ball->setMaterial(transparentMaterial);
	ball->setPosition({ 0.0f, -19.3f, 5.0f });
	ball->setShadowMesh(ballMesh2->inColor(TEST_1));
	ball->addComponent(engine::Physics::newSphericalRigidBody(1.0f));
	ball->addComponent(engine::Physics::newBoxCollider(ballMesh));
}

void createSceneGraph() {
	sceneGraph = new engine::SceneGraph();
	sceneGraph->setCamera(camera);

	engine::SceneNode* root = sceneGraph->getRoot();
	root->setShaderProgram(shaderProgram);
	root->setShadowShaderProgram(simpleDepthShader);

	createBase();
	createObjects();
	//createTransperentObjects();
}

void drawScene() {
	// Move light position
	//lightPos.x = float(1.0f + sin(glfwGetTime()) * 2.0f);
	//lightPos.z = float(sin(glfwGetTime() / 2.0f) * 1.0f);
	// Create light model matrix
	engine::Matrix4 lightOrtho = camera->createOrthographicProjectionMatrix(-20, 20, -20, 20, 0.5, 100);
	engine::Matrix4 lightView = camera->createViewMatrix(lightPos, engine::Vector3(0), engine::Vector3(0.0f, 1.0f, 0.0f));
	engine::Matrix4 lightSpaceMatrix = lightOrtho * lightView;
	
	// Set uniform light matrix in depth shader
	simpleDepthShader->use();
	glUniformMatrix4fv(glGetUniformLocation(simpleDepthShader->getShaderId(), "lightSpaceMatrix"), 1, GL_FALSE, lightSpaceMatrix.elements);
	// Draw depth map scene
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);

		sceneGraph->drawDepthMap(simpleDepthShader);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Set light uniforms in normal shader
	shaderProgram->use();
	glUniform3f(glGetUniformLocation(shaderProgram->getShaderId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	engine::Vector3 eye = camera->getEye();
	glUniform3f(glGetUniformLocation(shaderProgram->getShaderId(), "viewPos"), eye.x, eye.y, eye.z);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->getShaderId(), "lightSpaceMatrix"), 1, GL_FALSE, lightSpaceMatrix.elements);
	// Draw normal scene
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthMap);
    if (firstFrame) {
		firstFrame = false;
	} else { 
		engine::Physics::getInstance()->update();
	}

	glCullFace(GL_BACK);
	skyboxShader->use();
	skybox->drawCubemap();
	glCullFace(GL_FRONT);

	sceneGraph->draw();
}

void createDepthMap() {
	glGenFramebuffers(1, &depthMapFBO);
	// Create depth texture
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// Attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void createSkybox() {
	engine::Mesh* skymesh = engine::Mesh::parseMesh("../../assets/models/skybox.obj", skyboxShader);
	
		std::vector<std::string> faces
	{
		"../../assets/skybox/is/right.jpg",
		"../../assets/skybox/is/left.jpg",
		"../../assets/skybox/is/top.jpg",
		"../../assets/skybox/is/bottom.jpg",
		"../../assets/skybox/is/front.jpg",
		"../../assets/skybox/is/back.jpg"
	};
	std::vector<std::string> faces2
	{
		"../../assets/skybox/dt/right.jpg",
		"../../assets/skybox/dt/left.jpg",
		"../../assets/skybox/dt/top.jpg",
		"../../assets/skybox/dt/bottom.jpg",
		"../../assets/skybox/dt/front.jpg",
		"../../assets/skybox/dt/back.jpg"
	};

	skybox = engine::Cubemap::loadCubemap(faces2, skymesh);
}

///////////////////////////////////////////////////////////////////// CALLBACKS

void window_close_callback(GLFWwindow* win) {
	delete shaderProgram;
	delete simpleDepthShader;
}

void window_size_callback(GLFWwindow* win, int winx, int winy) {
	glViewport(0, 0, winx, winy);
}

void moveForward() {
	camera->updateEye("f");
}

void moveBackward() {
	camera->updateEye("b");
}

void moveLeft() {
	camera->updateEye("l");
}

void moveRight() {
	camera->updateEye("r");
}

void moveUp() {
	camera->updateEye("u");
}

void moveDown() {
	camera->updateEye("d");
}

const char* createScreenshotBasename() {
	static char basename[30];
	time_t t = time(NULL);
	strftime(basename, 30, "%Y%m%d_%H%M%S.png", localtime(&t));
	return basename;
}

void saveScreenshot() {
	unsigned char* pixels = (unsigned char*)malloc(WINDOW_WIDTH * WINDOW_HEIGHT * 4);
	if (pixels != NULL) {
		glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	}
	char filename[50];
	strcpy(filename, "../../screenshots/");
	strcat(filename, createScreenshotBasename());

	stbi_flip_vertically_on_write(1);
	int saved = stbi_write_png(filename, WINDOW_WIDTH, WINDOW_HEIGHT, 4, pixels, 0);

	if (saved) printf("Successfully Saved Image: %s\n", filename);
	else fprintf(stderr, "Failed Saving Image: %s\n", filename);

	free(pixels);
}

void increaseTurbPower() {
	turbPower += 1.0f;
	glUniform1f(shaderProgram->getUniform("powerSlide"), turbPower);
}

void decreaseTurbPower() {
	turbPower -= 1.0f;
	glUniform1f(shaderProgram->getUniform("powerSlide"), turbPower);
}

void setupKeyBufferCallbacks() {
	engine::KeyBuffer::setCallback(GLFW_KEY_W, &moveForward);
	engine::KeyBuffer::setCallback(GLFW_KEY_S, &moveBackward);
	engine::KeyBuffer::setCallback(GLFW_KEY_A, &moveLeft);
	engine::KeyBuffer::setCallback(GLFW_KEY_D, &moveRight);
	engine::KeyBuffer::setCallback(GLFW_KEY_E, &moveUp);
	engine::KeyBuffer::setCallback(GLFW_KEY_LEFT_SHIFT, &moveDown);

	engine::KeyBuffer::setCallback(GLFW_KEY_Z, &increaseTurbPower);
	engine::KeyBuffer::setCallback(GLFW_KEY_X, &decreaseTurbPower);
}

void keyboard_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_P:
		if (action == GLFW_PRESS) {
			camera->toggleProjection();
		}
		return;
	case GLFW_KEY_G:
		if (action == GLFW_PRESS) {
			camera->toggleGimbalLock();
		}
		return;
	case GLFW_KEY_C:
		if (action == GLFW_PRESS) {
			engine::Physics::getInstance()->toggleShowColliders();
		}
		return;
	case GLFW_KEY_SPACE:
		if (action == GLFW_PRESS) {
			ball->addForce(engine::Vector3(0.0f, 300.0f, 0.0f));
		}
		return;
	case GLFW_KEY_UP:
		if (action == GLFW_PRESS) {
			ball->addForce(engine::Vector3(0.0f, 0.0f, -100.0f));
		}
		return;
	case GLFW_KEY_DOWN:
		if (action == GLFW_PRESS) {
			ball->addForce(engine::Vector3(0.0f, 0.0f, 100.0f));
		}
		return;
	case GLFW_KEY_LEFT:
		if (action == GLFW_PRESS) {
			ball->addForce(engine::Vector3(-100.0f, 0.0f, 0.0f));
		}
		return;
	case GLFW_KEY_RIGHT:
		if (action == GLFW_PRESS) {
			ball->addForce(engine::Vector3(100.0f, 0.0f, 0.0f));
		}
		return;
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS) {
			glfwSetWindowShouldClose(win, GLFW_TRUE);
			window_close_callback(win);
		}
		return;
	case GLFW_KEY_I:
		if (action == GLFW_PRESS) {
			saveScreenshot();
		}
		return;
	default:
		break;
	}
	engine::KeyBuffer::set(key, action == GLFW_PRESS || action == GLFW_REPEAT);
}

void mouse_callback(GLFWwindow* win, double x, double y) {
	camera->updateDirection((float)x, (float)y);
}

void scroll_callback(GLFWwindow* win, double xoffset, double yoffset) {
	camera->updateFoV(float(xoffset), float(yoffset));
}

///////////////////////////////////////////////////////////////////////// SETUP

void glfw_error_callback(int error, const char* description) {
	std::cerr << "GLFW Error: " << description << std::endl;
}

GLFWwindow* setupWindow(int winx, int winy, const char* title, int is_fullscreen, int is_vsync) {
	GLFWmonitor* monitor = is_fullscreen ? glfwGetPrimaryMonitor() : 0;
	GLFWwindow* win = glfwCreateWindow(winx, winy, title, monitor, 0);
	if (!win) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(win);
	glfwSwapInterval(is_vsync);
	return win;
}

void setupMouseInput(GLFWwindow* win) {
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(win, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

void setupCallbacks(GLFWwindow* win) {
	glfwSetWindowCloseCallback(win, window_close_callback);
	glfwSetWindowSizeCallback(win, window_size_callback);
	glfwSetKeyCallback(win, keyboard_callback);
	glfwSetCursorPosCallback(win, mouse_callback);
	glfwSetScrollCallback(win, scroll_callback);
}

GLFWwindow* setupGLFW(int gl_major, int gl_minor, int winx, int winy, const char* title, int is_fullscreen, int is_vsync) {
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	GLFWwindow* win = setupWindow(winx, winy, title, is_fullscreen, is_vsync);
	setupMouseInput(win);
	setupCallbacks(win);

#if _DEBUG
	std::cout << "GLFW " << glfwGetVersionString() << std::endl;
#endif
	return win;
}

void setupGLEW() {
	glewExperimental = GL_TRUE;
	GLenum result = glewInit();
	if (result != GLEW_OK) {
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
}

void checkOpenGLInfo() {
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cerr << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
	std::cerr << "OpenGL version " << version << std::endl;
	std::cerr << "GLSL version " << glslVersion << std::endl;
}

void setupOpenGL(int winx, int winy) {
#if _DEBUG
	checkOpenGLInfo();
#endif
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	glViewport(0, 0, winx, winy);
}

GLFWwindow* setup(int major = 4, int minor = 3, int winx = WINDOW_WIDTH, int winy = WINDOW_HEIGHT, int is_fullscreen = 0, int is_vsync = 1) {
	GLFWwindow* win = setupGLFW(major, minor, winx, winy, title, is_fullscreen, is_vsync);
	setupGLEW();
	setupOpenGL(winx, winy);
	setupKeyBufferCallbacks();
	setupErrorCallback();
	createShaderProgram();
	createCamera(winx, winy);
	createDepthMap();
	createSkybox();
	createSceneGraph();
	return win;
}

////////////////////////////////////////////////////////////////////////// RUN

void display(GLFWwindow* win, double elapsed_sec) {
	glfwSetWindowTitle(win, std::string(title).append(" - ").append(std::to_string(elapsed_sec)).append("s").c_str());
	drawScene();
}

void run(GLFWwindow* win) {
    double last_time = glfwGetTime();
	while (!glfwWindowShouldClose(win)) {
        double time = glfwGetTime();
		double elapsed_time = time - last_time;
		last_time = time;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		engine::KeyBuffer::runCallbacks();
		display(win, elapsed_time);
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	glfwDestroyWindow(win);
	glfwTerminate();
}

////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char* argv[]) {
	GLFWwindow* win = setup();
	run(win);
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////////////