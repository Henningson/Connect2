#pragma once
#include "CircleEntity.h"

CircleEntity::CircleEntity(b2Vec2 pos, float scale, b2BodyType type, float radius) : Entity(pos, scale, type) {
	this->radius = radius;
}

void CircleEntity::finalizeObject() {
	this->shape = new sf::CircleShape(radius);
	if (this->bodyDef.type == b2_dynamicBody) {
		this->shape->setFillColor(sf::Color(252, 221, 51, 255));
	} else {
		this->shape->setFillColor(sf::Color(156, 156, 156, 255));
	}
	this->shape->setOrigin(radius, radius);
	this->bodyShape = new b2CircleShape();
	this->bodyShape->m_radius = radius / this->scale;
	this->setBodyFix(0.15f, 0.5f, 0.6f);
	this->update();
}

bool CircleEntity::collision() {
	return this->contacting;
}

float CircleEntity::getRadius() {
	return this->radius;
}
