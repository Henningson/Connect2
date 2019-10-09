#pragma once
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "CircleEntity.h"
#include "BoxEntity.h"
#include "SplineEntity.h"
#include "PolygonEntity.h"
#include "FixtureEntity.h"
#include <vector>
#include "SFMLDebugDraw.h"
#include "NonDrawableSurface.h"

class GameWorld {
	public:
		GameWorld(float scale, float timeFrame);
		void doStep();
		void draw();
		void setGravity(b2Vec2 gravity);
		void clear();
		bool contains(sf::Vector2f pos);
		int  getBodyCount();
		float getScale();
		b2World* getPhysWorld();
		void registerEntity(Entity* e);
		std::vector<Entity*> getEntities();
		std::vector<NonDrawableSurface*> getNonDrawableSurfaces();
		void destroyObject(b2Vec2 pos);
		void swapObjectType(b2Vec2 pos);
		void swapObjectType(Entity* e);

	public:
		void addBox(b2Vec2 pos, b2Vec2 size);
		CircleEntity* addCircle(b2Vec2 pos, float radius);
		SplineEntity* addSpline(b2Vec2 pos, float thickness);
		CircleEntity* addCircleEntity(CircleEntity* e);
		BoxEntity* addBoxEntity(BoxEntity* e);
		PolygonEntity* addPolygonEntity(PolygonEntity* e);
		void addNonDrawableSurfaces(std::vector<NonDrawableSurface*> nds);

	private:
		b2World* world;
		SFMLDebugDraw* debugDraw;
		float timeFrame;
		float scale = 30.f;
		int velocityIterations = 6;
		int positionIterations = 2;
		b2Vec2 gravity = b2Vec2(0.f, 20.f);
		std::vector<Entity*> dynamicEntities;
		std::vector<Entity*> staticEntities;
		std::vector<NonDrawableSurface*> nonDrawableSurfaces;
};