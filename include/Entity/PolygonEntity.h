#pragma once
#include "Entity.h"
#include "ComplexEntity.h"

class PolygonEntity : public ComplexEntity, public Entity {
	public:
		PolygonEntity(std::vector<sf::Vector2f*> vertices, float scale, b2BodyType type);

	public:
		void finalizeObject() override;
		void update() override;
		std::vector<sf::Vector2f*> vertices;
};