#include "GuiInputManager.h"
#include "MainMenueState.h"
#include "PlayingState.h"

GuiInputManager::GuiInputManager(GameState* state) : InputManager(state) {
}

void GuiInputManager::handlePlayerInput(sf::Mouse::Button button) {
	if (this->button == NULL)
		return;

	this->button->onClick("");
}

void GuiInputManager::handlePlayerInput(sf::Keyboard::Key key, bool keyPressed) {

}

void GuiInputManager::checkHoverPosition(sf::Vector2i pos) {
	bool hoveringOnButton = false;
	std::vector<Button*> butt = ((MainMenueState*)this->state)->getButtons();
	for (unsigned int i = 0; i < butt.size(); i++) {
		if (butt[i]->contains(sf::Vector2f(pos))) {
			butt[i]->select();
			this->button = butt[i];
			hoveringOnButton = true;
			return;
		} else {
			butt[i]->deselect();
		}
	}
	if (!hoveringOnButton)
		this->button = NULL;
}

void GuiInputManager::processEvents() {
	sf::Event event;
	this->checkHoverPosition(sf::Mouse::getPosition(*this->state->getWindow()));

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
