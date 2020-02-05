#include "PolygonEntity.h"

PolygonEntity::PolygonEntity(std::vector<sf::Vector2f*> vertices, float scale, b2BodyType type, bool isLava) : Entity(b2Vec2(0,0), scale, type, isLava) {
	this->vertices = vertices;
}

void PolygonEntity::finalizeObject() {
	this->shape = new sf::ConvexShape(vertices.size());
	this->setColor();

	for (unsigned int i = 0; i < vertices.size(); i++)
		((sf::ConvexShape*)this->shape)->setPoint(i, *vertices[i]);

	b2Vec2* vert = new b2Vec2[vertices.size()];
	for (unsigned int i = 0; i < vertices.size(); i++)
		vert[i] = ConvSfToB2Vec(*vertices[i], 30.f);

	b2PolygonShape* shape = new b2PolygonShape();
	shape->m_count = vertices.size();
	shape->Set(vert, vertices.size());
	this->bodyShape = shape;
	this->setBodyFix(0.3f, 0.5f, 0.25f);
}

void PolygonEntity::update() {
	b2Transform xf = body->GetTransform();
	int k = 0;
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
		b2PolygonShape* poly = (b2PolygonShape*)f->GetShape();
		int32 vertexCount = poly->m_count;
		b2Vec2* vert = new b2Vec2[poly->m_count];

		for (int32 i = 0; i < vertexCount; ++i) {
			vert[i] = b2Mul(xf, poly->m_vertices[i]);
			sf::Vector2f transformedVec = ConvB2VecToSff(vert[i], this->scale);
			((sf::ConvexShape*)this->shape)->setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y)));
		}
		k++;
	}
}
