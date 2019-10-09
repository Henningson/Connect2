#include "Entity.h"

Entity::Entity(b2Vec2 position, float scale, b2BodyType type) {
	this->scale = scale;
	this->bodyDef.position.Set(position.x, position.y);
	this->bodyDef.type = type;
}

void Entity::setBody(b2Body* body) {
	this->body = body;
}

b2Body* Entity::getBody() {
	return this->body;
}

b2BodyDef Entity::getBodyDef() {
	return this->bodyDef;
}

sf::Shape* Entity::getShape() {
	return this->shape;
}

void Entity::setTexture(sf::Texture * tex) {
	this->texture = tex;
	this->shape->setFillColor(sf::Color::White);
	this->shape->setTexture(this->texture);
}

void Entity::update() {
	this->shape->setPosition(ConvB2VecToSff(this->body->GetPosition(), this->scale));
	this->shape->setRotation(this->body->GetAngle()*180.f / 3.141f);
}

void Entity::changeType(b2BodyType type) {
	this->bodyDef.type = type;
	b2World* world = this->body->GetWorld();
	this->bodyDef.position.Set(this->body->GetPosition().x, this->body->GetPosition().y);
	this->bodyDef.angle = this->body->GetAngle();
	world->DestroyBody(this->body);
	world->CreateBody(&this->getBodyDef());
	this->setBodyFix(0.3f, 0.5f, 0.75f);
	this->update();
}

void Entity::setBodyFix(float density, float friction, float restitution) {
	this->fixtureDef.shape = this->bodyShape;
	this->fixtureDef.density = density;
	this->fixtureDef.friction = friction;
	this->fixtureDef.restitution = restitution;
	this->body->CreateFixture(&this->fixtureDef);
}

bool Entity::contains(sf::Vector2f pos) {
	return this->getShape()->getGlobalBounds().contains(pos);
}