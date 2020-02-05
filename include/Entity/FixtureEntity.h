#pragma once
#include "Entity.h"
#include "ComplexEntity.h"

class FixtureEntity : public Entity, public ComplexEntity {
	public:
		FixtureEntity(b2Vec2 pos, float scale, b2BodyType type, bool isLava);
		std::vector<sf::Shape*> getShapes();

	public:
		virtual void setBodyFix(float density, float friction, float restitution) override;
		bool contains(sf::Vector2f pos) override;
		void finalizeObject() override;
		void update() override;

	private:
		b2Vec2 pos;
		b2CircleShape* bodyShape;
		std::vector<b2Vec2> origins;
		std::vector<b2Vec2> vertices;
		std::vector<sf::Vector2f> sfVertices;
		std::vector<sf::Shape*> shapes;
};