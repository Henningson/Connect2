#include "Level.h"
#include <fstream>
#include <iostream>
#include "SFMLBoxHelper.h"

Level::Level(sf::RenderWindow* window, float maxLength) {
	this->window = window;
	this->maxLength = maxLength;
}

std::vector<BoxEntity*> Level::getBoxEntities() {
	return this->boxEntities;
}

std::vector<CircleEntity*> Level::getCircleEntities() {
	return this->circleEntities;
}

std::vector<PolygonEntity*> Level::getPolygonEntities() {
	return this->polygonEntities;
}

std::vector<NonDrawableSurface*> Level::getNonDrawableSurfaces() {
	return this->nonDrawableSurfaces;
}

CircleEntity * Level::getPlayerOne() {
	return this->playerOne;
}

CircleEntity* Level::getPlayerTwo() {
	return this->playerTwo;
}

float Level::getMaxSplineLength() {
	return this->maxLength;
}

void Level::loadLevel(std::string levelPath) {
	std::ifstream input;
	input.open("assets/Levels/" + levelPath + ".lvl");

	if (!input) {
		std::cout << "Error while loading lvl-file" << std::endl;
		return;
	}

	std::string line;
	sf::Vector2f pos;
	sf::Vector2f size;

	while (!input.eof()) {
		getline(input, line);

		if (line.substr(0, 2) == "SL")
			sscanf_s(line.c_str(), "SL %f", &this->maxLength);

		if (line.substr(0, 2) == "P1") {
			float x, y, radius;
			sscanf_s(line.c_str(), "P1 %f %f %f", &x, &y, &radius);
			this->playerOne = new CircleEntity(ConvSfToB2Vec(sf::Vector2f(this->window->getSize().x * x, this->window->getSize().y * y), 30.f), 30.f, b2_dynamicBody, this->window->getSize().x * radius, false);
		}

		if (line.substr(0, 2) == "P2") {
			float x, y, radius;
			sscanf_s(line.c_str(), "P2 %f %f %f", &x, &y, &radius);
			this->playerTwo = new CircleEntity(ConvSfToB2Vec(sf::Vector2f(this->window->getSize().x * x, this->window->getSize().y * y), 30.f), 30.f, b2_dynamicBody, this->window->getSize().x * radius, false);
		}

		//Parse Box
		if (line.substr(0, 3) == "BOX") {
			sf::Vector2f pos;
			sf::Vector2f size;
			b2BodyType type;
			bool isLava = false;
			do {
				if (line.substr(0, 3) == "pos") {
					float x, y;
					sscanf_s(line.c_str(), "pos %f %f", &x, &y);
					pos = sf::Vector2f(this->window->getSize().x * x, this->window->getSize().y * y);
				}

				if (line.substr(0, 4) == "size") {
					float x, y;
					sscanf_s(line.c_str(), "size %f %f", &x, &y);
					size = sf::Vector2f(this->window->getSize().x * x * 30.f, this->window->getSize().y * y * 30.f);
				}

				if (line.substr(0, 6) == "static")
					type = b2_staticBody;

				if (line.substr(0, 7) == "dynamic")
					type = b2_dynamicBody;

				if (line.substr(0, 6) == "lava")
					isLava = true;

				getline(input, line);
			} while (line.substr(0, 2) != "EO"); //End of Object
			this->boxEntities.push_back(new BoxEntity(ConvSfToB2Vec(pos, 30.f), 30.f, type, ConvSfToB2Vec(size, 30.f), isLava));
		}

		if (line.substr(0, 3) == "NDS") {
			sf::Vector2f pos;
			sf::Vector2f size;
			do {
				if (line.substr(0, 3) == "pos") {
					float x, y;
					sscanf_s(line.c_str(), "pos %f %f", &x, &y);
					pos = sf::Vector2f(this->window->getSize().x * x, this->window->getSize().y * y);
				}

				if (line.substr(0, 4) == "size") {
					float x, y;
					sscanf_s(line.c_str(), "size %f %f", &x, &y);
					size = sf::Vector2f(this->window->getSize().x * x, this->window->getSize().y * y);
				}

				getline(input, line);
			} while (line.substr(0, 2) != "EO"); //End of Object
			this->nonDrawableSurfaces.push_back(new NonDrawableSurface(pos, size));
		}


		//Parse Circle
		if (line.substr(0, 3) == "CIR") {
			sf::Vector2f pos;
			float radius;
			b2BodyType type;
			bool isLava = false;
			do {
				if (line.substr(0, 3) == "pos") {
					float x, y;
					sscanf_s(line.c_str(), "pos %f %f", &x, &y);
					pos = sf::Vector2f(this->window->getSize().x * x, this->window->getSize().y * y);
				}

				if (line.substr(0, 3) == "rad")
					sscanf_s(line.c_str(), "rad %f", &radius);

				if (line.substr(0, 6) == "static")
					type = b2_staticBody;

				if (line.substr(0, 6) == "lava")
					isLava = true;

				if (line.substr(0, 7) == "dynamic")
					type = b2_dynamicBody;

				getline(input, line);
			} while (line.substr(0, 2) != "EO"); //End of Object
			this->circleEntities.push_back(new CircleEntity(ConvSfToB2Vec(pos, 30.f), 30.f, type, radius*this->window->getSize().x, isLava));
		}

		//Parse Polygon
		if (line.substr(0, 3) == "POL") {
			b2BodyType type;
			std::vector<sf::Vector2f*> vec;
			bool isLava = false;
			do {
				if (line.substr(0, 3) == "vec") {
					float x, y;
					sscanf_s(line.c_str(), "vec %f %f", &x, &y);
					vec.push_back(new sf::Vector2f(this->window->getSize().x * x, this->window->getSize().y * y));
				}

				if (line.substr(0, 6) == "static")
					type = b2_staticBody;

				if (line.substr(0, 7) == "dynamic")
					type = b2_dynamicBody;

				if (line.substr(0, 6) == "lava")
					isLava = true;

				getline(input, line);
			} while (line.substr(0, 2) != "EO"); //End of Object
			this->polygonEntities.push_back(new PolygonEntity(vec, 30.f, type, isLava));
		}
	}
}
