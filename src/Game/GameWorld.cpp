#include "GameWorld.h"
#include <stdio.h>


GameWorld::GameWorld(float scale, float timeFrame) {
	this->scale = scale;
	this->timeFrame = timeFrame;
	this->world = new b2World(this->gravity);
}

float GameWorld::GameWorld::getScale() {
	return this->scale;
}

b2World* GameWorld::getPhysWorld() {
	return this->world;
}

void GameWorld::doStep() {
	this->world->Step(this->timeFrame, this->velocityIterations, this->positionIterations);
	for (unsigned int i = 0; i < this->dynamicEntities.size(); i++)
		this->dynamicEntities[i]->update();
}

void GameWorld::draw() {
	for (unsigned int i = 0; i < this->dynamicEntities.size(); i++)
		this->dynamicEntities[i]->update();

	for (unsigned int i = 0; i < this->staticEntities.size(); i++)
		this->staticEntities[i]->update();
}

void GameWorld::registerEntity(Entity* e) {
	if (e->getBody()->GetType() == b2_dynamicBody) {
		this->dynamicEntities.push_back(e);
	}
	else {
		this->staticEntities.push_back(e);
	}
}

std::vector<Entity*> GameWorld::getEntities() {
	std::vector<Entity*> vec;
	vec.insert(vec.end(), this->dynamicEntities.begin(), this->dynamicEntities.end());
	vec.insert(vec.end(), this->staticEntities.begin(), this->staticEntities.end());
	return vec;
}

std::vector<NonDrawableSurface*> GameWorld::getNonDrawableSurfaces() {
	return this->nonDrawableSurfaces;
}

void GameWorld::setGravity(b2Vec2 gravity) {
	this->gravity = gravity;
	this->world->SetGravity(gravity);
}

void GameWorld::swapObjectType(b2Vec2 pos) {
	sf::Vector2f position = ConvB2VecToSff(pos, this->scale);

	for (unsigned int i = 0; i < this->dynamicEntities.size(); i++) {
		if (this->dynamicEntities[i]->contains(position)) {
			this->dynamicEntities[i]->changeType(b2_staticBody);
			this->staticEntities.push_back(this->dynamicEntities[i]);
			this->dynamicEntities.erase(this->dynamicEntities.begin() + i);
			return;
		}
	}


	for (unsigned int i = 0; i < this->staticEntities.size(); i++) {
		if (this->staticEntities[i]->contains(position)) {
			this->staticEntities[i]->changeType(b2_dynamicBody);
			this->dynamicEntities.push_back(this->staticEntities[i]);
			this->staticEntities.erase(this->staticEntities.begin() + i);
			return;
		}
	}
}

void GameWorld::swapObjectType(Entity* e) {
	for (unsigned int i = 0; i < this->dynamicEntities.size(); i++) {
		if (this->dynamicEntities[i] == e) {
			this->dynamicEntities[i]->changeType(b2_staticBody);
			this->staticEntities.push_back(this->dynamicEntities[i]);
			this->dynamicEntities.erase(this->dynamicEntities.begin() + i);
			return;
		}
	}


	for (unsigned int i = 0; i < this->staticEntities.size(); i++) {
		if (this->staticEntities[i] == e) {
			this->staticEntities[i]->changeType(b2_dynamicBody);
			this->dynamicEntities.push_back(this->staticEntities[i]);
			this->staticEntities.erase(this->staticEntities.begin() + i);
			return;
		}
	}
}

void GameWorld::destroyObject(b2Vec2 pos) {
	sf::Vector2f position = ConvB2VecToSff(pos, this->scale);

	for (unsigned int i = 0; i < this->dynamicEntities.size(); i++) {
		if (this->dynamicEntities[i]->getShape()->getGlobalBounds().contains(position)) {
			this->world->DestroyBody(this->dynamicEntities[i]->getBody());
			delete this->dynamicEntities[i];
			this->dynamicEntities.erase(this->dynamicEntities.begin() + i);
			return;
		}
	}

	for (unsigned int i = 0; i < this->staticEntities.size(); i++) {
		if (this->staticEntities[i]->getShape()->getGlobalBounds().contains(position)) {
			this->world->DestroyBody(this->staticEntities[i]->getBody());
			delete this->staticEntities[i];
			this->staticEntities.erase(this->staticEntities.begin() + i);
			return;
		}
	}
}

void GameWorld::clear() {
	for (unsigned int i = 0; i < this->dynamicEntities.size(); i++)
		this->world->DestroyBody(this->dynamicEntities[i]->getBody());

	for (unsigned int i = 0; i < this->staticEntities.size(); i++)
		this->world->DestroyBody(this->staticEntities[i]->getBody());

	this->nonDrawableSurfaces.clear();
	this->dynamicEntities.clear();
	this->staticEntities.clear();
}

bool GameWorld::contains(sf::Vector2f pos) {
	for (unsigned int i = 0; i < this->nonDrawableSurfaces.size(); i++) {
		if (this->nonDrawableSurfaces[i]->getGlobalBounds().contains(pos))
			return true;
	}

	for (unsigned int i = 0; i < this->staticEntities.size(); i++) {
		if (this->staticEntities[i]->contains(pos))
			return true;
	}

	for (unsigned int i = 0; i < this->dynamicEntities.size(); i++) {
		if (this->dynamicEntities[i]->contains(pos))
			return true;
	}

	return false;
}

int GameWorld::getBodyCount() {
	return this->staticEntities.size() + this->dynamicEntities.size() + this->nonDrawableSurfaces.size();
}

void GameWorld::addBox(b2Vec2 pos, b2Vec2 size) {
	BoxEntity* e = new BoxEntity(pos, this->scale, b2_staticBody, size);
	e->setBody(this->world->CreateBody(&e->getBodyDef()));
	e->finalizeObject();
	this->registerEntity(e);
}

CircleEntity* GameWorld::addCircle(b2Vec2 pos, float radius) {
	CircleEntity* e = new CircleEntity(pos, this->scale, b2_dynamicBody, radius);
	e->setBody(this->world->CreateBody(&e->getBodyDef()));
	e->finalizeObject();
	this->registerEntity(e);
	return e;
}

SplineEntity* GameWorld::addSpline(b2Vec2 pos, float thickness) {
	SplineEntity* e = new SplineEntity(pos, this->scale, b2_staticBody, thickness);
	e->setBody(this->world->CreateBody(&e->getBodyDef()));
	this->registerEntity(e);
	return e;
}

CircleEntity* GameWorld::addCircleEntity(CircleEntity* e) {
	e->setBody(this->world->CreateBody(&e->getBodyDef()));
	e->finalizeObject();
	this->registerEntity(e);
	return e;
}

BoxEntity* GameWorld::addBoxEntity(BoxEntity* e) {
	e->setBody(this->world->CreateBody(&e->getBodyDef()));
	e->finalizeObject();
	this->registerEntity(e);
	return e;
}

PolygonEntity* GameWorld::addPolygonEntity(PolygonEntity* e) {
	e->setBody(this->world->CreateBody(&e->getBodyDef()));
	e->finalizeObject();
	this->registerEntity(e);
	return e;
}

void GameWorld::addNonDrawableSurfaces(std::vector<NonDrawableSurface*> nds) {
	this->nonDrawableSurfaces = nds;
}
