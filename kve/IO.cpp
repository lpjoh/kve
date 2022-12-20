#include "IO.h"
#include <fstream>

using namespace kve;

std::optional<std::string> IO::LoadFileString(const std::string filePath) {
	std::string fileString;
	std::ifstream file(filePath);

	if (file.is_open()) {
		std::string line;

		while (std::getline(file, line)) {
			fileString += line + "\n";
		}

		file.close();
	}
	else {
		// File does not exist
		return std::nullopt;
	}

	return { fileString };
}