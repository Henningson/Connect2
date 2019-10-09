#pragma once
#include "GUIState.h"
#include "GuiInputManager.h"
#include "Button.h"

class MainMenueState : public GUIState {
	public:
		MainMenueState(sf::RenderWindow* window, std::string title);
		
	public:
		void startLevel(std::string text);
		void createLevel(std::string text);
		void exitGame(std::string text);

	private:
};