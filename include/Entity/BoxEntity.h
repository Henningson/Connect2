#pragma once
#include "Entity.h"
#include "ComplexEntity.h"

class BoxEntity : public ComplexEntity, public Entity {
	public:
		BoxEntity(b2Vec2 position, float scale, b2BodyType type, b2Vec2 size, bool isLava);
		void finalizeObject() override;

	private:
		b2Vec2 size;
		b2Vec2* verts;
		int vertCount = 4;
};