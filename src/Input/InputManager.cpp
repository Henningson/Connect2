#include "InputManager.h"

class GameState;
InputManager::InputManager(GameState* state) {
	this->state = state;
}

void InputManager::processEvents() {
	sf::Event event;
	while (this->state->getWindow()->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::KeyPressed:
			this->handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			this->handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::MouseButtonPressed:
			handlePlayerInput(event.mouseButton.button);
			break;
		case sf::Event::Closed:
			this->state->getWindow()->close();
			break;
		default:
			break;
		}
	}
}