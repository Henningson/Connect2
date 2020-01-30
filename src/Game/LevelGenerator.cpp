#include "Game.h"
#include "PlayingState.h"
/*
Game::Game(unsigned int xSize, unsigned int ySize, std::string title, bool fullscreen) {
	this->title = title;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	this->window = new sf::RenderWindow(sf::VideoMode(xSize, ySize), title, (fullscreen) ? sf::Style::Fullscreen : sf::Style::Default, settings);
	this->window->setFramerateLimit(60);
	this->stateMachine = new StateMachine(new MainMenueBackgroundState(this->window));
	this->stateMachine->pushState(new MainMenueState(this->window, this->title));
}

void Game::run() {
	while (this->window->isOpen()) {
		this->window->clear(sf::Color::White);
		this->checkState();

		//Iterate through the stack, and draw each state on top of each other
		for (int i = 0; i < this->stateMachine->getSize(); i++) {
			if (i == this->stateMachine->getSize() - 1) {
				this->stateMachine->getAt(i)->processEvents();
				continue;
			}
			this->stateMachine->getAt(i)->processEvents();
		}

		//Only allow one IM to be active at all times
		this->stateMachine->top()->getIM()->processEvents();
		this->window->display();
	}
}

sf::RenderWindow* Game::getWindow() {
	return this->window;
}

void Game::checkState() {
	if (!this->stateMachine->top()->isPendingForKill())
		return;

	std::vector<GameState*> nextStates = this->stateMachine->top()->getNextStates();

	if (this->stateMachine->pop()->getKillEverything())
		this->stateMachine->clear();

	if (nextStates.size() > 0) {
		for (int i = 0; i < nextStates.size(); i++) {
			this->stateMachine->pushState(nextStates[i]);
		}
	}
}
*/