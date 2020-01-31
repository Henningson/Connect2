#include "PlayingInputManager.h"
#include "SFMLBoxHelper.h"
#include "PlayingState.h"
#include "MainMenueBackgroundState.h"
#include "MainMenueState.h"

PlayingInputManager::PlayingInputManager(GameState* game, float scale) : InputManager(game) {
	this->scale = scale;
	this->clock = sf::Clock();
}

void PlayingInputManager::handlePlayerInput(sf::Mouse::Button button) {
}

void PlayingInputManager::handlePlayerInput(sf::Keyboard::Key key, bool keyPressed) {
	if (key == sf::Keyboard::Key::Escape) {
		std::vector<GameState*> vec;
		vec.push_back(new MainMenueBackgroundState(this->state->getWindow()));
		vec.push_back(new MainMenueState(this->state->getWindow(), "Connect 2"));
		this->state->setNextStates(vec);
		this->state->kill();
	} else if (key == sf::Keyboard::Key::Return) {
		((PlayingState*)this->state)->restart();
	}
}

void PlayingInputManager::toggleDrag() {
	this->dragging = !this->dragging;
}

void PlayingInputManager::finalizeLine() {
	this->toggleDrag();
	this->spline->finalizeObject();
	this->length += this->spline->getLength();
	((PlayingState*)this->state)->getGameWorld()->swapObjectType(this->spline);
	((PlayingState*)this->state)->run();
}

float PlayingInputManager::getCurrentLength() {
	return this->currentLength;
}

void PlayingInputManager::processEvents() {
	sf::Event event;

	//Catch every event for 0.5s
	if (this->clock.getElapsedTime().asSeconds() < 0.1f) {
		this->state->getWindow()->pollEvent(event);
		return;
	}

	sf::Vector2i clickpos = sf::Mouse::getPosition(*this->state->getWindow());
	b2Vec2 b2clickpos = ConvSfToB2Vec(clickpos, this->scale);
	while (this->state->getWindow()->pollEvent(event)) {
		switch (event.type) {
		
		case sf::Event::KeyPressed:
			this->handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::MouseButtonPressed:
			if (denyDrawing || ((PlayingState*)this->state)->getGameWorld()->contains(sf::Vector2f(clickpos)))
				break;
			start = false;
			this->toggleDrag();
			this->spline = ((PlayingState*)this->state)->getGameWorld()->addSpline(b2clickpos, 5.f);
			break;

		case sf::Event::MouseButtonReleased:
			if (denyDrawing || start)
				break;

			this->finalizeLine();
			break;

		case sf::Event::MouseMoved:
			if (this->dragging && !((PlayingState*)this->state)->getGameWorld()->contains(sf::Vector2f(clickpos))) {
				this->spline->addVertex(b2clickpos);
				this->currentLength = this->length + this->spline->getLength();
				((PlayingState*)this->state)->setSplineLength(this->currentLength);
				if (this->currentLength > ((PlayingState*)this->state)->getLevel()->getMaxSplineLength()) {
					this->denyDrawing = true;
					this->finalizeLine();
				}
			}
			break;

		case sf::Event::Closed:
			this->state->getWindow()->close();
			break;

		default:
			break;
		}
	}

}
