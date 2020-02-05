#pragma once
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include "SFMLBoxHelper.h"

class Entity {
	public:
		Entity(b2Vec2 pos, float scale, b2BodyType type, bool isLava);
		b2Body* getBody();
		b2BodyDef getBodyDef();
		void setBody(b2Body* body);
		sf::Shape* getShape();
		void setTexture(sf::Texture* tex);
		void setColor();
		bool isEntityLava();
		bool collision() { return this->contacting; }
		void startContact() { this->contacting = true; }
		void endContact() { this->contacting = false; }

	//Polymorphic functions
	public:
		virtual void update();
		virtual void changeType(b2BodyType type);
		virtual bool contains(sf::Vector2f pos);
		virtual void setBodyFix(float density, float friction, float restitution);

	protected:
		bool isLava = false;
		float scale;
		b2Body* body;
		b2BodyDef bodyDef;
		b2Shape* bodyShape;
		b2FixtureDef fixtureDef;
		sf::Shape* shape;
		sf::Texture* texture;
		bool contacting = false;
};