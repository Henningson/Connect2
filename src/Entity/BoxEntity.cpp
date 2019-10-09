#pragma once
#include "BoxEntity.h"

BoxEntity::BoxEntity(b2Vec2 position, float scale, b2BodyType type, b2Vec2 size) : Entity(position, scale, type) {
	this->size = size;
}

void BoxEntity::finalizeObject() {
	this->shape = new sf::RectangleShape(sf::Vector2f(size.x, size.y));
	if (this->bodyDef.type == b2_dynamicBody) {
		this->shape->setFillColor(sf::Color(252, 221, 51, 255));
	} else {
		this->shape->setFillColor(sf::Color(156, 156, 156, 255));
	}
	this->shape->setOrigin(size.x / 2.f, size.y / 2.f);
	this->bodyShape = new b2PolygonShape();
	static_cast<b2PolygonShape*>(this->bodyShape)->SetAsBox(size.x / (2 * scale), size.y / (2 * scale));
	this->setBodyFix(0.3f, 0.5f, 0.25f);
	this->update();
}