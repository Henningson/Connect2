#pragma once
#include "BoxEntity.h"

BoxEntity::BoxEntity(b2Vec2 position, float scale, b2BodyType type, b2Vec2 size, bool isLava) : Entity(position, scale, type, isLava) {
	this->size = size;
}

void BoxEntity::finalizeObject() {
	this->shape = new sf::RectangleShape(sf::Vector2f(size.x, size.y));
	this->setColor();
	this->shape->setOrigin(size.x / 2.f, size.y / 2.f);
	this->bodyShape = new b2PolygonShape();
	static_cast<b2PolygonShape*>(this->bodyShape)->SetAsBox(size.x / (2 * scale), size.y / (2 * scale));
	this->setBodyFix(0.3f, 0.5f, 0.25f);
	this->update();
}