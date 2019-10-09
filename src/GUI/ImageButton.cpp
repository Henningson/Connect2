#include "ImageButton.h"

ImageButton::ImageButton(sf::Shape* shape, sf::Text* text) : Button(text) {
	this->shape = shape;
	this->background = new sf::RectangleShape(sf::Vector2f(this->shape->getLocalBounds().width, this->shape->getLocalBounds().height));
	this->background->scale(sf::Vector2f(1.25f, 1.25f));
	this->background->setFillColor(sf::Color::Green);
}

bool ImageButton::contains(sf::Vector2f pos) {
	return this->background->getGlobalBounds().contains(pos);
}

void ImageButton::setPosition(sf::Vector2f pos) {
	this->shape->setPosition(pos);
	this->background->setPosition(pos);
}

void ImageButton::setSize(sf::Vector2f size) {
}
