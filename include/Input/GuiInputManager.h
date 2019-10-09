#pragma once
#include "InputManager.h"
#include "Button.h"

class GuiInputManager : public InputManager {
	public:
		GuiInputManager(GameState* state);
		void processEvents() override;
		Button* button;

	private:
		virtual void handlePlayerInput(sf::Mouse::Button button) override;
		virtual void handlePlayerInput(sf::Keyboard::Key key, bool keyPressed) override;
		void checkHoverPosition(sf::Vector2i pos);
};