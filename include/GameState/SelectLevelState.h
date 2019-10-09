#pragma once
#include "GUIState.h"
#include "GuiInputManager.h"
#include "Button.h"

class SelectLevelState : public GUIState {
	public:
		SelectLevelState(sf::RenderWindow* window, std::string title);
		void selectLevel(std::string text);
		void browseForward(std::string placeholder);
		void browseBackward(std::string placeholder);
		void mainMenue(std::string placeholder);
		std::vector<Button*> getButtons() override;
		void draw() override;

	private:
		int pageNr = 0;
		Button* nextButton;
		Button* prevButton;
};