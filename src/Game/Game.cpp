#include "Game.h"
#include "PlayingState.h"

Game::Game(unsigned int xSize, unsigned int ySize, std::string title, bool fullscreen) {
	this->title = title;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	this->window = new sf::RenderWindow(sf::VideoMode(xSize, ySize), title, (fullscreen) ? sf::Style::Fullscreen : sf::Style::Default, settings);
	this->window->setFramerateLimit(60);
	this->window->setMouseCursorVisible(false);
	this->stateMachine = new StateMachine(new MainMenueBackgroundState(this->window));
	this->stateMachine->pushState(new MainMenueState(this->window, this->title));
}

void Game::run() {
	sf::Texture tex1;
	tex1.loadFromFile("assets/Game/cursor.png");
	sf::Sprite cursor(tex1);

	sf::Texture tex2;
	tex2.loadFromFile("assets/Game/Background.png");
	sf::RectangleShape bg = sf::RectangleShape(sf::Vector2f(this->window->getSize()));
	bg.setTexture(&tex2);

	while (this->window->isOpen()) {
		this->window->clear(sf::Color::White);
		this->window->draw(bg);
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
		if (this->stateMachine->getSize() > 0)
			this->stateMachine->top()->getIM()->processEvents();

		cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window)));
		this->window->draw(cursor);
		this->window->display();
	}
}

sf::RenderWindow* Game::getWindow() {
	return this->window;
}

void Game::checkState() {
	std::vector<GameState*> nextStates = this->stateMachine->top()->getNextStates();

	if (nextStates.size() == 0 && !this->stateMachine->top()->isPendingForKill())
		return;

	GameState* state = this->stateMachine->top();
	bool killEverything = this->stateMachine->top()->getKillEverything();
	
	if (state->isPendingForKill()) {
		std::string message = this->stateMachine->pop()->getMessageForPrev();
		if (this->stateMachine->getSize() > 0)
			this->stateMachine->top()->useMessageFromPrev(message);
	}

	if (killEverything)
		this->stateMachine->clear();

	if (nextStates.size() > 0) {
		for (unsigned int i = 0; i < nextStates.size(); i++) {
			this->stateMachine->pushState(nextStates[i]);
		}
	}
}