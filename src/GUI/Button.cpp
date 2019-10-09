#include "Button.h"

Button::Button(sf::Text* text) {
	this->text = text;
	this->text->setFillColor(sf::Color::Black);
}

void Button::select() {
	this->selected = true;
	this->text->setFillColor(sf::Color::Cyan);
}

void Button::deselect() {
	this->selected = false;
	this->text->setFillColor(sf::Color::Black);
}

bool Button::isSelected() {
	return this->selected;
}

bool Button::contains(sf::Vector2f pos) {
	return this->text->getGlobalBounds().contains(pos);
}

sf::Text* Button::getText() {
	return this->text;
}

sf::FloatRect Button::getLocalBounds() {
	return this->text->getLocalBounds();
}

void Button::setOnClickEvent(std::function<void(std::string text)> f) {
	this->func = f;
}

void Button::onClick(std::string text) {
	if (this->func != NULL)
		this->func(text);
}
