#pragma once
#include "GUIState.h"
#include "GuiInputManager.h"
#include "Button.h"

class GameWonState : public GUIState {
	public:
		GameWonState(sf::RenderWindow* window, std::string title);
		
	public:
		void nextLevel(std::string text);
		void exitLevel(std::string text);
};