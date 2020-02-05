#include "FixtureEntity.h"
#pragma once

FixtureEntity::FixtureEntity(b2Vec2 pos, float scale, b2BodyType type, bool isLava) : Entity(pos, scale, type, isLava) {
	this->pos = pos;
}

void FixtureEntity::setBodyFix(float density, float friction, float restitution) {
	this->fixtureDef.density = density;
	this->fixtureDef.friction = friction;
	this->fixtureDef.restitution = restitution;
	this->body->CreateFixture(&this->fixtureDef);
}

bool FixtureEntity::contains(sf::Vector2f pos) {
	for (unsigned int i = 0; i < this->shapes.size(); i++)
		if (this->shapes[i]->getGlobalBounds().contains(pos))
			return true;

	return false;
}

void FixtureEntity::finalizeObject() {
	sf::Shape* circ1 = new sf::CircleShape(10.0f);
	circ1->setFillColor(sf::Color::Red);
	circ1->setPosition(ConvB2VecToSff(pos, scale));
	circ1->setOrigin(10.f, 10.f);
	this->shapes.push_back(circ1);

	sf::Shape* circ2 = new sf::CircleShape(10.0f);
	circ2->setFillColor(sf::Color::Blue);
	pos.x += 1.f;
	circ2->setPosition(ConvB2VecToSff(pos, scale));
	circ2->setOrigin(10.f, 10.f);
	this->shapes.push_back(circ2);

	this->bodyShape = new b2CircleShape();
	this->bodyShape->m_radius = 10.f / this->scale;
	this->setBodyFix(0.3f, 0.5f, 0.75f);

	this->bodyShape = new b2CircleShape();
	((b2CircleShape*)this->bodyShape)->m_p = pos;
	this->bodyShape->m_radius = 10.f / this->scale;
	this->setBodyFix(0.3f, 0.5f, 0.75f);
}

void FixtureEntity::update() {
	int i = 0;
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
		b2Vec2 tOrigin = ((b2CircleShape*)f->GetShape())->m_p;
		this->shapes[i]->setPosition(ConvB2VecToSff(tOrigin, this->scale));
		i++;
	}
}


std::vector<sf::Shape*> FixtureEntity::getShapes() {
	return this->shapes;
}