#pragma once
#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::experimental::filesystem;

class DirReader {
	public:
		DirReader(std::string path);
		void read();
		void setPath(std::string path);
		std::vector<std::string> getLevels();
		std::vector<std::string> getImages();

	private:
		std::string path;
		std::vector<std::string> levels;
		std::vector<std::string> images;
};