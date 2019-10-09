#pragma once
#include "Entity.h"
#include "CircleEntity.h"
#include "BoxEntity.h"
#include "PolygonEntity.h"
#include "Box2D\Box2D.h"
#include "NonDrawableSurface.h"

class Level {
	public:
		Level(sf::RenderWindow* window, float maxLength);
		std::vector<BoxEntity*> getBoxEntities();
		std::vector<CircleEntity*> getCircleEntities();
		std::vector<PolygonEntity*> getPolygonEntities();
		std::vector<NonDrawableSurface*> getNonDrawableSurfaces();
		CircleEntity* getPlayerOne();
		CircleEntity* getPlayerTwo();
		float getMaxSplineLength();
		void loadLevel(std::string levelPath);

	protected:
		std::vector<BoxEntity*> boxEntities;
		std::vector<CircleEntity*> circleEntities;
		std::vector<PolygonEntity*> polygonEntities;
		std::vector<NonDrawableSurface*> nonDrawableSurfaces;
		CircleEntity* playerOne;
		CircleEntity* playerTwo;
		sf::RenderWindow* window;
		float maxLength;
};
