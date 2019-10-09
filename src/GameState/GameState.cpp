#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) {
	this->window = window;
}

void GameState::processEvents() {
	this->draw();
	this->im->processEvents();
}

void GameState::kill() {
	this->toBeKilled = true;
}

bool GameState::isPendingForKill() {
	return this->toBeKilled;
}

std::vector<GameState*> GameState::getNextStates() {
	return this->nextStates;
}

void GameState::setNextStates(std::vector<GameState*> states) {
	this->nextStates = states;
}

sf::RenderWindow* GameState::getWindow() {
	return this->window;
}

void GameState::setKillEverything() {
	this->killEverything = true;
}

bool GameState::getKillEverything() {
	return this->killEverything;
}

std::string GameState::getMessageForPrev()
{
	return this->messageForPrev;
}

void GameState::useMessageFromPrev(std::string message) {
	//Do nothing, override this
}

InputManager* GameState::getIM() {
	return this->im;
}
