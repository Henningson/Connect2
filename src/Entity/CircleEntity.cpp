#pragma once
#include "CircleEntity.h"

CircleEntity::CircleEntity(b2Vec2 pos, float scale, b2BodyType type, float radius, bool isLava) : Entity(pos, scale, type, isLava) {
	this->radius = radius;
}

void CircleEntity::finalizeObject() {
	this->shape = new sf::CircleShape(radius);
	this->setColor();

	this->shape->setOrigin(radius, radius);
	this->bodyShape = new b2CircleShape();
	this->bodyShape->m_radius = radius / this->scale;
	this->setBodyFix(0.15f, 0.5f, 0.6f);
	this->update();
}

float CircleEntity::getRadius() {
	return this->radius;
}
