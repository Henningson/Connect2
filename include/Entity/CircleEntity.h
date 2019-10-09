#pragma once
#include "Entity.h"
#include "ComplexEntity.h"

class CircleEntity : public ComplexEntity, public Entity {
	public:
		CircleEntity(b2Vec2 pos, float scale, b2BodyType type, float radius);
		void finalizeObject() override;
		void startContact() { contacting = true; }
		void endContact() { contacting = false; }
		bool collision();
		float getRadius();

	private:
		float radius;
		bool contacting = false;
};