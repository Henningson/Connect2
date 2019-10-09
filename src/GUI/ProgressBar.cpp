#include "ProgressBar.h"

ProgressBar::ProgressBar(sf::Vector2f pos, sf::Vector2f size, float maxLength) {
	this->maxLength = maxLength;

	this->background = new sf::RectangleShape(size);
	this->background->setOrigin(sf::Vector2f(this->background->getLocalBounds().width / 2.f, 
											 this->background->getLocalBounds().height / 2.f));
	this->background->setPosition(pos);
	this->background->setFillColor(sf::Color(100, 100, 100, 255));
	this->background->setOutlineColor(sf::Color(50, 50, 50, 255));
	this->background->setOutlineThickness(2.0f);

	sf::Vector2f progPos = sf::Vector2f(pos.x - (size.x / 2.f), pos.y - (size.y / 2.f));
	this->progress = new sf::RectangleShape(size);
	this->progress->setPosition(progPos);
	this->progress->setFillColor(sf::Color::Green);
}

void ProgressBar::setLength(float length) {
	//Progress is 100%
	if (this->maxLength <= length) {
		this->progress->setScale(sf::Vector2f(0.0f, 1.0f));
		return;
	}

	//Let's not divide by zero
	if (length < 0.01f)
		return;

	float scale = 1.0f - length / this->maxLength;
	this->progress->setScale(sf::Vector2f(scale, 1.0f));
}

sf::Shape * ProgressBar::getBackground() {
	return this->background;
}

sf::Shape * ProgressBar::getProgress() {
	return this->progress;
}
