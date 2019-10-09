#include "DirReader.h"

DirReader::DirReader(std::string path) {
	this->path = path;
	this->read();
}

void DirReader::read() {
	for (auto &p : fs::directory_iterator(path)) {
		if (p.path().filename().generic_string().find(".lvl") != std::string::npos) {
			this->levels.push_back(p.path().filename().generic_string().substr(0, p.path().filename().generic_string().size() - 4));
		} else {
			this->images.push_back(p.path().filename().generic_string());
		}
	}
}

void DirReader::setPath(std::string path) {
	this->path = path;
	this->read();
}

std::vector<std::string> DirReader::getLevels() {
	return this->levels;
}

std::vector<std::string> DirReader::getImages() {
	return this->images;
}
