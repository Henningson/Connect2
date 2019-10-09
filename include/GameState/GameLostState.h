#pragma once
#include "GUIState.h"
#include "GuiInputManager.h"
#include "Button.h"

class GameLostState : public GUIState {
	public:
		GameLostState(sf::RenderWindow* window, std::string title);
		
	public:
		void restartLevel(std::string text);
		void exitLevel(std::string text);
};