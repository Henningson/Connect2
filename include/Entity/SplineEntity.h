#pragma once
#include "Entity.h"
#include "ComplexEntity.h"

class SplineEntity : public ComplexEntity, public Entity {
	public:
		SplineEntity(b2Vec2 position, float scale, b2BodyType type, float thickness);
		void addVertex(b2Vec2 vertex);
		std::vector<sf::Shape*> getShapes();
		void addFixture(float density, float friction, float restitution, b2PolygonShape* shape);
		float getLength();

	public:
		virtual void setBodyFix(float density, float friction, float restitution) override;
		bool contains(sf::Vector2f pos) override;
		void finalizeObject() override;
		void update() override;
		void changeType(b2BodyType type) override;

	private:
		b2PolygonShape* bodyShape;
		float length = 0.f;
		float thickness = 5.f;
		void genRect();
		std::vector<b2FixtureDef> fixtures;
		std::vector<b2Vec2> vertices;
		std::vector<sf::Vector2f> sfVertices;
		std::vector<sf::Shape*> shapes;
		std::vector<b2Vec2*> b2Shapes;
};