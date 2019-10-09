#pragma once
#include "GameState.h"
#include "GuiInputManager.h"
#include "Button.h"

class GUIState : public GameState {
	public:
		GUIState(sf::RenderWindow* window, std::string title);
		
	public:
		virtual std::vector<Button*> getButtons();
		virtual void processEvents() override;
		virtual void clear() override;
		virtual void draw() override;

	protected:
		std::vector<Button*> buttons;
		sf::Font font;
		sf::Text* title;
};