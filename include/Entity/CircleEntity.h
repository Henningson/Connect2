#pragma once
#include "Entity.h"
#include "ComplexEntity.h"

class CircleEntity : public ComplexEntity, public Entity {
	public:
		CircleEntity(b2Vec2 pos, float scale, b2BodyType type, float radius, bool isLava);
		void finalizeObject() override;
		float getRadius();

	private:
		float radius;
		bool contacting = false;
};