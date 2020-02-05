#include "PlayingState.h"
#include "PlayingInputManager.h"
#include "GameLostState.h"
#include "GameWonState.h"
#include <iostream>

Animation winningAnimation1;
sf::Texture tex1;
Animation winningAnimation2;
sf::Texture tex2;

PlayingState::PlayingState(sf::RenderWindow * window, bool drawGui, Level* level) : GameState(window) {
	this->level = level;
	this->gameWorld = new GameWorld(30.f, 1.f / 60.f);
	this->drawGui = drawGui;

	this->im = new PlayingInputManager(this, 30.f);

	this->cl = new ContactListener();
	this->gameWorld->getPhysWorld()->SetContactListener(this->cl);
	this->generateLevel();

	if (!this->buffer.loadFromFile("assets/Sounds/win.wav"))
		return;

	if (!tex1.loadFromFile("assets/Animation/heartAnimation.png"))
		return;

	if (!tex2.loadFromFile("assets/Animation/heartAnimation.png"))
		return;

	winningAnimation1.setSpriteSheet(tex1);
	winningAnimation2.setSpriteSheet(tex2);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			winningAnimation1.addFrame(sf::IntRect(64 * j, 64 * i, 64, 64));
			winningAnimation2.addFrame(sf::IntRect(64 * j, 64 * i, 64, 64));
		}
	}

	this->gameWonSprite1 = new AnimatedSprite(sf::seconds(0.05), true, false);
	this->gameWonSprite1->setAnimation(winningAnimation1);
	this->gameWonSprite1->setOrigin(sf::Vector2f(64, 92));
	this->gameWonSprite2 = new AnimatedSprite(sf::seconds(0.05), true, false);
	this->gameWonSprite2->setAnimation(winningAnimation2);
	this->gameWonSprite2->setOrigin(sf::Vector2f(0, 92));
	this->frameClock.restart();
	this->sound.setBuffer(buffer);
}

void PlayingState::generateLevel() {
	sf::Texture* tex = new sf::Texture();
	tex->loadFromFile("assets/Object/Player1sad.jpg");
	this->playerOne = (CircleEntity*)this->getGameWorld()->addCircleEntity(this->level->getPlayerOne());
	this->playerOne->setTexture(tex);
	this->playerOne->getBody()->SetUserData(this->playerOne);

	sf::Texture* tex1 = new sf::Texture();
	tex1->loadFromFile("assets/Object/Player2sad.jpg");
	this->playerTwo = (CircleEntity*)this->getGameWorld()->addCircleEntity(this->level->getPlayerTwo());
	this->playerTwo->setTexture(tex1);
	this->playerTwo->getBody()->SetUserData(this->playerTwo);

	this->getGameWorld()->addNonDrawableSurfaces(this->level->getNonDrawableSurfaces());

	for (unsigned int i = 0; i < this->level->getCircleEntities().size(); i++)
		this->getGameWorld()->addCircleEntity(this->level->getCircleEntities()[i]);

	for (unsigned int i = 0; i < this->level->getBoxEntities().size(); i++)
		this->getGameWorld()->addBoxEntity(this->level->getBoxEntities()[i]);

	for (unsigned int i = 0; i < this->level->getPolygonEntities().size(); i++)
		this->getGameWorld()->addPolygonEntity(this->level->getPolygonEntities()[i]);

	this->progressBar = new ProgressBar(
						sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 30.f),
						sf::Vector2f(window->getSize().x / 3.f, window->getSize().y / 30.f),
						this->level->getMaxSplineLength());
}

GameWorld* PlayingState::getGameWorld() {
	return this->gameWorld;
}

void PlayingState::useMessageFromPrev(std::string message) {
	if (message == "restart")
		this->restart();
}

void PlayingState::processEvents() {
	if (runGame) {
		this->gameWorld->doStep();
		this->checkCollision();
		bool oob = this->checkOutOfBounds(this->playerOne);
		oob = oob || this->checkOutOfBounds(this->playerTwo);
		if (oob && !this->gameWon) {
			this->runGame = false;
			this->showLostGUI();
		}
	}
	this->draw();
}

void PlayingState::checkCollision() {
	if (this->gameWon)
		return;

	if (this->playerOne->collision() && this->playerTwo->collision()) {
		sf::Texture* tex1 = new sf::Texture();
		tex1->loadFromFile("assets/Object/Player1.jpg");
		this->playerOne->setTexture(tex1);
			
		sf::Texture* tex2 = new sf::Texture();
		tex2->loadFromFile("assets/Object/Player2.jpg");
		this->playerTwo->setTexture(tex2);

		this->showWonGUI();
		this->gameWon = true;
		this->gameWonSprite1->play();
		this->gameWonSprite2->play();
		this->sound.play();
	}

	for (Entity* e : this->getGameWorld()->getEntities()) {
		if (!e->isEntityLava())
			continue;

		if (e->collision() && this->playerOne->collision() || e->collision() && this->playerTwo->collision()) {
			this->runGame = false;
			this->showLostGUI();
		}
	}
}

bool PlayingState::checkOutOfBounds(CircleEntity* ce) {
	if (ce->getShape()->getPosition().x - ce->getRadius() > this->window->getSize().x)
		return true;

	if (ce->getShape()->getPosition().x + ce->getRadius() < 0.f)
		return true;

	if (ce->getShape()->getPosition().y - ce->getRadius() > this->window->getSize().y)
		return true;

	return false;
}

void PlayingState::clear(){
	this->gameWorld->clear();
	
	for (unsigned int i = 0; i < this->nextStates.size(); i++)
		delete this->nextStates[i];
	this->nextStates.clear();
}

void PlayingState::draw(){
	std::vector<NonDrawableSurface*> nds = this->gameWorld->getNonDrawableSurfaces();
	for (unsigned int i = 0; i < nds.size(); i++)
		this->window->draw(*nds[i]);

	std::vector<Entity*> ent = this->gameWorld->getEntities();
	for (unsigned int i = 0; i < ent.size(); i++) {
		if (dynamic_cast<SplineEntity*>(ent[i]) == nullptr) {
			this->window->draw(*ent[i]->getShape());
		} else {
			std::vector<sf::Shape*> shapes = static_cast<SplineEntity*>(ent[i])->getShapes();
			for (unsigned int j = 0; j < shapes.size(); j++)
				this->window->draw(*shapes[j]);
		}
	}

	if (this->gameWon) {
		this->gameWonSprite1->update(frameClock.restart());
		this->gameWonSprite1->setPosition(this->playerOne->getShape()->getPosition());
		this->gameWonSprite2->update(frameClock.getElapsedTime());
		this->gameWonSprite2->setPosition(this->playerTwo->getShape()->getPosition());
		this->window->draw(*this->gameWonSprite1);
		this->window->draw(*this->gameWonSprite2);
	}

	this->progressBar->setLength(this->splineLength);
	this->window->draw(*this->progressBar->getBackground());
	this->window->draw(*this->progressBar->getProgress());
}

void PlayingState::setSplineLength(float length) {
	this->splineLength = length;
}

Level* PlayingState::getLevel() {
	return this->level;
}

void PlayingState::run() {
	this->runGame = true;
}

void PlayingState::restart() {
	this->im = new PlayingInputManager(this, 30.f);
	this->splineLength = 0.0f;
	this->runGame = false;
	this->clear();
	this->generateLevel();
}

void PlayingState::showLostGUI() {
	std::vector<GameState*> vec;
	vec.push_back(new GameLostState(this->getWindow(), "Fatality!"));
	this->setNextStates(vec);
}

void PlayingState::showWonGUI() {
	std::vector<GameState*> vec;
	vec.push_back(new GameWonState(this->getWindow(), "Success!"));
	this->setNextStates(vec);
}
