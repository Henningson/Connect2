#pragma once
#include "InputManager.h"
#include <SFML\Graphics.hpp>


class InputManager;
class GameState {
	public:
		GameState(sf::RenderWindow* window);

	public:
		sf::RenderWindow* getWindow();
		virtual void processEvents();
		virtual void clear() = 0;
		virtual void draw() = 0;
		void kill();
		bool isPendingForKill();
		std::vector<GameState*> getNextStates();
		void setNextStates(std::vector<GameState*> states);
		void setKillEverything();
		bool getKillEverything();
		std::string getMessageForPrev();
		virtual void useMessageFromPrev(std::string message);
		InputManager* getIM();

	protected:
		InputManager* im;
		sf::RenderWindow* window;
		bool toBeKilled = false;
		bool killEverything = false;
		std::vector<GameState*> nextStates;
		std::string messageForPrev = "";
};