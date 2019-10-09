#pragma once
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include "SFMLBoxHelper.h"

class Entity {
	public:
		Entity(b2Vec2 pos, float scale, b2BodyType type);
		b2Body* getBody();
		b2BodyDef getBodyDef();
		void setBody(b2Body* body);
		sf::Shape* getShape();
		void setTexture(sf::Texture* tex);

	//Polymorphic functions
	public:
		virtual void update();
		virtual void changeType(b2BodyType type);
		virtual bool contains(sf::Vector2f pos);
		virtual void setBodyFix(float density, float friction, float restitution);

	protected:
		float scale;
		b2Body* body;
		b2BodyDef bodyDef;
		b2Shape* bodyShape;
		b2FixtureDef fixtureDef;
		sf::Shape* shape;
		sf::Texture* texture;
};