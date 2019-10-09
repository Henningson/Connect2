#include "GameWonState.h"
#include "PlayingState.h"
#include "MainMenueBackgroundState.h"
#include "MainMenueState.h"

GameWonState::GameWonState(sf::RenderWindow* window, std::string title) : GUIState(window, title) {
	sf::Text* box3 = new sf::Text();
	box3->setFont(this->font);
	box3->setString("Exit Level");
	box3->setCharacterSize(24);
	box3->setStyle(sf::Text::Regular);
	box3->setOrigin(sf::Vector2f(box3->getLocalBounds().width / 2.f, box3->getLocalBounds().height / 2.f));
	box3->setPosition(sf::Vector2f(window->getSize().x / 2.f, (window->getSize().y / 5.f) * 2.f));
	Button* button3 = new Button(box3);
	button3->setOnClickEvent(std::bind(&GameWonState::exitLevel, this, std::placeholders::_1));
	this->buttons.push_back(button3);

	this->im = new GuiInputManager(this);
}

void GameWonState::nextLevel(std::string text) {
	//this->kill();
	//this->killEverything = false;
	//this->messageForPrev = "restart";
}

void GameWonState::exitLevel(std::string text) {
	std::vector<GameState*> vec;
	vec.push_back(new MainMenueBackgroundState(this->getWindow()));
	vec.push_back(new MainMenueState(this->getWindow(), "Connect 2"));
	this->setNextStates(vec);
	this->kill();
	this->setKillEverything();
}