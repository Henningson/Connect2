#include "GUIState.h"

GUIState::GUIState(sf::RenderWindow* window, std::string title) : GameState(window) {
	this->font.loadFromFile("assets/Fonts/kindergarten.ttf");

	this->title = new sf::Text();
	this->title->setFont(this->font);
	this->title->setString(title);
	this->title->setCharacterSize(50);
	this->title->setStyle(sf::Text::Regular);
	this->title->setFillColor(sf::Color::Black);
	this->title->setOrigin(sf::Vector2f(this->title->getLocalBounds().width / 2.f, this->title->getLocalBounds().height / 2.f));
	this->title->setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 5.f));

	this->im = new GuiInputManager(this);
}

void GUIState::clear(){
	for (unsigned int i = 0; i < this->buttons.size(); i++)
		delete this->buttons[i];
}

void GUIState::draw(){
	this->window->draw(*this->title);

	for (unsigned int i = 0; i < this->buttons.size(); i++)
		this->window->draw(*this->buttons[i]->getText());
}

std::vector<Button*> GUIState::getButtons() {
	return this->buttons;
}

void GUIState::processEvents() {
	this->draw();
	this->im->processEvents();
}