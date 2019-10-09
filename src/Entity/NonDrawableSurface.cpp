#include "NonDrawableSurface.h"

NonDrawableSurface::NonDrawableSurface(sf::Vector2f position, sf::Vector2f size) : sf::RectangleShape(size) {
	this->setOrigin(sf::Vector2f(size.x / 2.f, size.y / 2.f));
	this->setPosition(position);
	this->setOutlineColor(sf::Color::Black);
	this->setOutlineThickness(-1.0f);
	this->texture = new sf::Texture();
	this->texture->loadFromFile("assets/Game/NonDrawableSurface.png");
	this->texture->setRepeated(true);
	this->setTextureRect(sf::IntRect(0, 0, (int)size.x, (int)size.y));
	this->setTexture(this->texture);
}
