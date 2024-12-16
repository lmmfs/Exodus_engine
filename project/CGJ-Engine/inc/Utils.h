#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#define PI 3.14159265359
#define RAD	57.295779513082

namespace engine {

	class Math {

	public:
		static float angleToRad(float angle) {
			return (float)(angle * (PI / 180.0f));
		}
		static float radToAngle(float angle) {
			return (float)(angle * RAD);
		}

		static float sine(float angle) {
			if (angle == 90) return 1;
			else
				return sin(angleToRad(angle));
		}
		static float cosine(float angle) {
			if (angle == 0) return 1;
			if (angle == 90) return 0;
			if (angle == -90) return 0;
			else
				return cos(angleToRad(angle));
		}

		/**
		* Cleans a float based on a threshold
		* If the difference between closest int and the float
		* is less than the threshold, the clean returns the closest int
		*
		* @param float the float to clean
		* @param float the threshold to consider
		* @return the cleansed float
		*/
		static const float cleanFloat(const float f, const float threshold) {
			if (fabs(f) - floor(fabs(f)) < threshold)
				return floor(fabs(f)) == 0.0f ? 0.0f : (f < 0 ? floor(f) : ceil(f));
			if (ceil(fabs(f)) - fabs(f) < threshold)
				return ceil(fabs(f)) == 0.0f ? 0.0f : (f < 0 ? floor(f) : ceil(f));
			return f;
		}

	};

	/**
	*
	* Output utilities to format or help with data output
	*
	*/
	class IO {

	public:

		/**
		* Calculates the length of the "longest" number
		*
		* @param numbers The list of numbers to check
		* @param size The size of the list
		* @param precision The precision that shall be used in the output
		*
		* @return The length of the "longest" number
		*/
		static const size_t maxLengthForPadding(const float* numbers, int size, int precision) {

			size_t pad = 0;
			std::stringstream sstream;
			sstream.precision(precision);

			for (int i = 0; i < size; ++i) {
				std::string s;
				sstream << std::fixed << numbers[i];
				sstream >> s;

				pad = s.length() > pad ? s.length() : pad;

				s.clear();
				sstream.clear();
			}

			return pad;
		}

		/**
		* Converts the file to a collection of lines
		*
		* @param filename The name of the file to read the lines
		* @return vector<string> The lines
		*/
		static std::vector<std::string> linesFromFile(std::ifstream* file) {

			std::vector<std::string> lines;
			std::string line;
			if (file->is_open())
			{
				int i = 0;
				while (getline(*file, line))
				{
					lines.push_back(line);
				}
				file->close();
			}
			else {
				throw "File not found";
			}
			return (*new std::vector<std::string>(lines));

		}

		/**
		* Converts the file to a collection of lines
		*
		* @param filename The name of the file to read the lines
		* @return vector<string> The lines
		*/
		static std::vector<std::string> linesFromFile(const char* filename) {
			std::ifstream file(filename);
			return IO::linesFromFile(&file);
		}

		/**
		* Reads all lines from the file with given filename
		*
		* @param filename The name of the file to read the lines
		* @return char* The lines read
		*/
		static const char* readLinesFromFile(std::ifstream* file) {

			std::string lines;
			std::string line;
			if (file->is_open())
			{
				int i = 0;
				while (getline(*file, line))
				{
					lines += line;
					lines += '\n';
				}
				file->close();
			}
			return (*new std::string(lines)).c_str();

		}

		/**
		* Reads all lines from the file with given filename
		*
		* @param filename The name of the file to read the lines
		* @return char* The lines read
		*/
		static const char* readLinesFromFile(const char* filename) {
			std::ifstream file(filename);
			return IO::readLinesFromFile(&file);
		}

	};

}