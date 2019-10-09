#include "SelectLevelState.h"
#include "MainMenueState.h"
#include "MainMenueBackgroundState.h"
#include "ImageButton.h"
#include "Level.h"
#include "PlayingState.h"
#include "DirReader.h"

SelectLevelState::SelectLevelState(sf::RenderWindow* window, std::string title) : GUIState(window, "Select your Level") {
	DirReader* dr = new DirReader("assets/Levels/");

	sf::Text* boxPrev = new sf::Text();
	boxPrev->setFont(this->font);
	boxPrev->setString("Previous");
	boxPrev->setCharacterSize(24);
	boxPrev->setStyle(sf::Text::Regular);
	boxPrev->setOrigin(sf::Vector2f(boxPrev->getLocalBounds().width / 2.f, boxPrev->getLocalBounds().height / 2.f));
	boxPrev->setPosition(sf::Vector2f((window->getSize().x / 5.f) * 0.5f, window->getSize().y / 2.f));
	Button* buttonPrev = new Button(boxPrev);
	buttonPrev->setOnClickEvent(std::bind(&SelectLevelState::browseBackward, this, std::placeholders::_1));
	this->buttons.push_back(buttonPrev);

	sf::Text* boxNext = new sf::Text();
	boxNext->setFont(this->font);
	boxNext->setString("Next");
	boxNext->setCharacterSize(24);
	boxNext->setStyle(sf::Text::Regular);
	boxNext->setOrigin(sf::Vector2f(boxNext->getLocalBounds().width / 2.f, boxNext->getLocalBounds().height / 2.f));
	boxNext->setPosition(sf::Vector2f((window->getSize().x / 5.f) * 4.5f, window->getSize().y / 2.f));
	Button* buttonNext = new Button(boxNext);
	buttonNext->setOnClickEvent(std::bind(&SelectLevelState::browseForward, this, std::placeholders::_1));
	this->buttons.push_back(buttonNext);

	sf::Text* boxMainMenue = new sf::Text();
	boxMainMenue->setFont(this->font);
	boxMainMenue->setString("Main Menue");
	boxMainMenue->setCharacterSize(24);
	boxMainMenue->setStyle(sf::Text::Regular);
	boxMainMenue->setOrigin(sf::Vector2f(boxMainMenue->getLocalBounds().width / 2.f, boxMainMenue->getLocalBounds().height / 2.f));
	boxMainMenue->setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 5.f * 4.f));
	Button* buttonMM = new Button(boxMainMenue);
	buttonMM->setOnClickEvent(std::bind(&SelectLevelState::mainMenue, this, std::placeholders::_1));
	this->buttons.push_back(buttonMM);

	for (unsigned int i = 0; i < dr->getLevels().size(); i++) {
		sf::Text* box1 = new sf::Text();
		box1->setFont(this->font);
		box1->setString(dr->getLevels()[i]);
		box1->setCharacterSize(24);
		box1->setStyle(sf::Text::Regular);
		box1->setOrigin(sf::Vector2f(box1->getLocalBounds().width / 2.f, box1->getLocalBounds().height / 2.f));
		if (i % 6 == 0) {
			box1->setPosition(sf::Vector2f((window->getSize().x / 5.f) * 1.5f, window->getSize().y / 5.f * 2.f));
		} else if (i % 6 == 1) {
			box1->setPosition(sf::Vector2f(window->getSize().x / 5.f * 2.5f, window->getSize().y / 5.f * 2.f));
		} else if (i % 6 == 2) {
			box1->setPosition(sf::Vector2f(window->getSize().x / 5.f * 3.5f, window->getSize().y / 5.f * 2.f));
		} else if (i % 6 == 3) {
			box1->setPosition(sf::Vector2f(window->getSize().x / 5.f * 1.5f, window->getSize().y / 5.f * 3.f));
		} else if (i % 6 == 4) {
			box1->setPosition(sf::Vector2f(window->getSize().x / 5.f * 2.5f, window->getSize().y / 5.f * 3.f));
		} else if (i % 6 == 5) {
			box1->setPosition(sf::Vector2f(window->getSize().x / 5.f * 3.5f, window->getSize().y / 5.f * 3.f));
		}
		
		Button* button = new Button(box1);
		button->setOnClickEvent(std::bind(&SelectLevelState::selectLevel, this, dr->getLevels()[i]));
		this->buttons.push_back(button);
	}
}

void SelectLevelState::mainMenue(std::string text) {
	std::vector<GameState*> vec;
	vec.push_back(new MainMenueState(this->getWindow(), "Connect 2"));
	this->setNextStates(vec);
	this->kill();
}

void SelectLevelState::selectLevel(std::string text) {
	std::vector<GameState*> vec;
	Level* level = new Level(this->window, 1000.f);
	level->loadLevel(text);
	vec.push_back(new PlayingState(this->getWindow(), true, level));
	this->setNextStates(vec);
	this->setKillEverything();
	this->kill();
}

void SelectLevelState::browseForward(std::string placeholder) {
	unsigned int end = ((this->pageNr + 1) * 6) + 3;
	if (end >= this->buttons.size())
		return;
	pageNr++;
}

void SelectLevelState::browseBackward(std::string placeholder) {
	this->pageNr = (this->pageNr == 0) ? 0 : this->pageNr - 1;
}

void SelectLevelState::draw() {
	this->window->draw(*this->title);

	unsigned int start = this->pageNr * 6 + 3;
	unsigned int end = ((this->pageNr + 1) * 6) + 3;
	if (end >= this->buttons.size())
		end = this->buttons.size();


	if (pageNr != 0)
		this->window->draw(*this->buttons[0]->getText());

	if (end != this->buttons.size())
		this->window->draw(*this->buttons[1]->getText());

	this->window->draw(*this->buttons[2]->getText());
	for (unsigned int i = start; i < end; i++)
		this->window->draw(*this->buttons[i]->getText());
}

std::vector<Button*> SelectLevelState::getButtons() {
	std::vector<Button*> btns;
	unsigned int start = this->pageNr * 6 + 3;
	unsigned int end = ((this->pageNr + 1) * 6) + 3;
	if (end >= this->buttons.size())
		end = this->buttons.size();

	for (int i = 0; i < 3; i++)
		btns.push_back(this->buttons[i]);

	for (unsigned int i = start; i < end; i++)
		btns.push_back(this->buttons[i]);

	return btns;
}