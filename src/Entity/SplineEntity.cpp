#include "SplineEntity.h"

SplineEntity::SplineEntity(b2Vec2 position, float scale, b2BodyType type, float thickness) : Entity(position, scale, type) {
	this->thickness = thickness;
	this->addVertex(position);
	this->bodyShape = new b2PolygonShape();
	this->fixtureDef.shape = this->bodyShape;
}

void SplineEntity::addVertex(b2Vec2 vertex) {
	//Drawing is fine
	bool addB2 = false;

	//Add first possible vertex
	if (this->vertices.size() == 0) {
		sf::Vector2f vecf = ConvB2VecToSff(vertex, this->scale);
		b2Vec2 vecb = ConvSfToB2Vec(vecf, this->scale);
		this->sfVertices.push_back(vecf);
		this->vertices.push_back(vertex);
		return;
	}

	//Catch the case, if the box2d units are too small
	float xLen = vertex.x - this->vertices.back().x;
	float yLen = vertex.y - this->vertices.back().y;
	if (!(0.1 < std::sqrt(xLen*xLen + yLen*yLen)))
		return;

	this->sfVertices.push_back(ConvB2VecToSff(vertex, this->scale));
	this->vertices.push_back(vertex);
	this->genRect();
}

void SplineEntity::finalizeObject() {
	//Change origin of every line-segment to Box2D Fixture Origin
	this->update();
}

void SplineEntity::genRect() {
	/*Create SFML-Shape*/
	sf::Vector2f pointA = this->sfVertices[this->sfVertices.size() - 2];
	sf::Vector2f pointB = this->sfVertices[this->sfVertices.size() - 1];
	sf::Vector2f direction = pointB - pointA;

	sf::Vector2f unitDirection = direction / std::sqrt(direction.x*direction.x + direction.y*direction.y);
	sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

	sf::Vector2f offset = (thickness / 2.f)*unitPerpendicular;

	float len = std::sqrt(direction.x*direction.x + direction.y*direction.y);
	float angle = std::atan2(direction.y, direction.x);
	sf::Vector2f origin = pointA + (direction / 2.f);

	sf::ConvexShape* rect = new sf::ConvexShape(4);
	rect->setFillColor(sf::Color::Black);
	rect->setPoint(0, pointA + offset);
	rect->setPoint(1, pointB + offset);
	rect->setPoint(2, pointB - offset);
	rect->setPoint(3, pointA - offset);
	this->shapes.push_back(rect);

	b2Vec2 vert[4];
	vert[0] = ConvSfToB2Vec(pointA - this->sfVertices[0] + offset, this->scale);
	vert[1] = ConvSfToB2Vec(pointB - this->sfVertices[0] + offset, this->scale);
	vert[2] = ConvSfToB2Vec(pointB - this->sfVertices[0] - offset, this->scale);
	vert[3] = ConvSfToB2Vec(pointA - this->sfVertices[0] - offset, this->scale);

	this->b2Shapes.push_back(vert);
	this->length += len;
	/*Create BOX2D-Shape*/
	b2Vec2 b2origin = ConvSfToB2Vec(origin, this->scale);
	b2Vec2 size = ConvSfToB2Vec(sf::Vector2f(thickness, len), this->scale);

	b2PolygonShape* shape = new b2PolygonShape();
	shape->m_count = 4;
	shape->Set(vert, 4);
	this->addFixture(15.0f, 0.1f, 0.1f, shape);
}

std::vector<sf::Shape*> SplineEntity::getShapes() {
	return this->shapes;
}

void SplineEntity::update() {
	b2Transform xf = body->GetTransform();
	int k = 0;
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
		b2PolygonShape* poly = (b2PolygonShape*)f->GetShape();
		int32 vertexCount = poly->m_count;
		b2Vec2 vert[4];

		for (int32 i = 0; i < vertexCount; ++i) {
			vert[i] = b2Mul(xf, poly->m_vertices[i]);
			sf::Vector2f transformedVec = ConvB2VecToSff(vert[i], this->scale);
			((sf::ConvexShape*)this->shapes[k])->setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y)));
		}
	k++;
	}
}

void SplineEntity::setBodyFix(float density, float friction, float restitution) {
	//Do nothing
}

bool SplineEntity::contains(sf::Vector2f pos) {
	for (unsigned int i = 0; i < this->shapes.size(); i++)
		if (this->shapes[i]->getGlobalBounds().contains(pos))
			return true;

	return false;
}

void SplineEntity::addFixture(float density, float friction, float restitution, b2PolygonShape* shape) {
	this->fixtureDef.shape = shape;
	this->fixtureDef.density = density;
	this->fixtureDef.friction = friction;
	this->fixtureDef.restitution = restitution;
	this->fixtures.push_back(this->fixtureDef);
	this->body->CreateFixture(&this->fixtureDef);
}

float SplineEntity::getLength() {
	return this->length;
}

void SplineEntity::changeType(b2BodyType type) {
	this->bodyDef.type = type;
	b2World* world = this->body->GetWorld();
	this->bodyDef.position.Set(this->body->GetPosition().x, this->body->GetPosition().y);
	this->bodyDef.angle = this->body->GetAngle();
	world->DestroyBody(this->body);
	world->CreateBody(&this->getBodyDef());
	for (unsigned int i = 0; i < this->fixtures.size(); i++) {
		this->body->CreateFixture(&this->fixtures[i]);
	}
	//this->setBodyFix(0.3f, 0.5f, 0.75f);
	this->update();
}