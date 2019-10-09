#pragma once
#include <SFML\Graphics.hpp>
#include "StateMachine.h"
#include "MainMenueState.h"
#include "PlayingState.h"
#include "MainMenueBackgroundState.h"

class InputManager;
class Game {
	public:
		Game(unsigned int xSize, unsigned int ySize, std::string title, bool fullscreen);
		void run();
		sf::RenderWindow* getWindow();
		void checkState();

	private:
		sf::RenderWindow* window;
		StateMachine* stateMachine;
		std::string title;
};