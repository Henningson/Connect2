#include "GameLostState.h"
#include "PlayingState.h"
#include "MainMenueBackgroundState.h"
#include "MainMenueState.h"

GameLostState::GameLostState(sf::RenderWindow* window, std::string title) : GUIState(window, title) {
	sf::Text* box1 = new sf::Text();
	box1->setFont(this->font);
	box1->setString("Restart Level");
	box1->setCharacterSize(24);
	box1->setStyle(sf::Text::Regular);
	box1->setOrigin(sf::Vector2f(box1->getLocalBounds().width / 2.f, box1->getLocalBounds().height / 2.f));
	box1->setPosition(sf::Vector2f(window->getSize().x / 2.f, (window->getSize().y / 5.f) * 2.f));
	Button* button1 = new Button(box1);
	button1->setOnClickEvent(std::bind(&GameLostState::restartLevel, this, std::placeholders::_1));
	this->buttons.push_back(button1);

	sf::Text* box3 = new sf::Text();
	box3->setFont(this->font);
	box3->setString("Exit Level");
	box3->setCharacterSize(24);
	box3->setStyle(sf::Text::Regular);
	box3->setOrigin(sf::Vector2f(box3->getLocalBounds().width / 2.f, box3->getLocalBounds().height / 2.f));
	box3->setPosition(sf::Vector2f(window->getSize().x / 2.f, (window->getSize().y / 5.f) * 3.f));
	Button* button3 = new Button(box3);
	button3->setOnClickEvent(std::bind(&GameLostState::exitLevel, this, std::placeholders::_1));
	this->buttons.push_back(button3);

	this->im = new GuiInputManager(this);
}

void GameLostState::restartLevel(std::string text) {
	this->kill();
	this->killEverything = false;
	this->messageForPrev = "restart";
}

void GameLostState::exitLevel(std::string text) {
	std::vector<GameState*> vec;
	vec.push_back(new MainMenueBackgroundState(this->getWindow()));
	vec.push_back(new MainMenueState(this->getWindow(), "Connect 2"));
	this->setNextStates(vec);
	this->kill();
	this->setKillEverything();
}