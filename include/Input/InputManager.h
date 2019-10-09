#pragma once
#include "GameState.h"
#include <SFML\Graphics.hpp>

class GameState;
class InputManager {
	public:
		InputManager(GameState* state);
		virtual void processEvents();

	private:
		virtual void handlePlayerInput(sf::Mouse::Button button) = 0;
		virtual void handlePlayerInput(sf::Keyboard::Key key, bool keyPressed) = 0;

	protected:
		GameState* state;
};