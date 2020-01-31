#include "MainMenueBackgroundState.h"
#include "PlayingInputManager.h"

MainMenueBackgroundState::MainMenueBackgroundState(sf::RenderWindow * window) : GameState(window) {
	this->gameWorld = new GameWorld(30.f, 1.f / 60.f);

	this->im = new PlayingInputManager(this, 30.f);
	this->cl = new ContactListener();
	this->gameWorld->getPhysWorld()->SetContactListener(this->cl);
	this->generateLevel();
}

void MainMenueBackgroundState::generateLevel() {
	sf::Vector2f windowSize = sf::Vector2f(window->getSize());
	sf::Vector2f boxOrigin = sf::Vector2f(windowSize.x / 2.f, windowSize.y);
	sf::Vector2f boxSize = sf::Vector2f(windowSize.x * 30.f, 100.f*30.f);

	sf::Vector2f leftBoxOrigin = boxOrigin;
	leftBoxOrigin.x = -120.f;

	sf::Vector2f rightBoxOrigin = boxOrigin;
	rightBoxOrigin.x = windowSize.x + 120.f;

	boxOrigin.y += 30.f;

	sf::Texture* tex = new sf::Texture();
	tex->loadFromFile("assets/Object/Player1sad.jpg");
	this->circle1 = this->gameWorld->addCircle(ConvSfToB2Vec(sf::Vector2f(windowSize.x / 6.f * 1.f, windowSize.y - 100.f), 30.f), 45.f);
	this->circle1->getBody()->SetUserData(this->circle1);
	this->circle1->setTexture(tex);

	sf::Texture* tex1 = new sf::Texture();
	tex1->loadFromFile("assets/Object/Player2sad.jpg");
	this->circle2 = this->gameWorld->addCircle(ConvSfToB2Vec(sf::Vector2f(windowSize.x / 6.f * 5.f, windowSize.y - 100.f), 30.f), 45.f);
	this->circle2->getBody()->SetUserData(this->circle2);
	this->circle2->setTexture(tex1);

	this->gameWorld->addBox(ConvSfToB2Vec(leftBoxOrigin, 30.f), ConvSfToB2Vec(boxSize, 30.f));
	this->gameWorld->addBox(ConvSfToB2Vec(rightBoxOrigin, 30.f), ConvSfToB2Vec(boxSize, 30.f));
	this->gameWorld->addBox(ConvSfToB2Vec(boxOrigin, 30.f), ConvSfToB2Vec(boxSize, 30.f));

	SplineEntity* spline1 = this->gameWorld->addSpline(ConvSfToB2Vec(sf::Vector2f(windowSize.x / 6.f * 1.f - 25.f, 100.f), 30.f), 5.f);
	spline1->addVertex(ConvSfToB2Vec(sf::Vector2f(windowSize.x / 6.f * 1.f - 100.f, 100.f), 30.f));
	this->gameWorld->swapObjectType(spline1);

	SplineEntity* spline2 = this->gameWorld->addSpline(ConvSfToB2Vec(sf::Vector2f(windowSize.x / 6.f * 5.f + 25.f, 100.f), 30.f), 5.f);
	spline2->addVertex(ConvSfToB2Vec(sf::Vector2f(windowSize.x / 6.f * 5.f + 100.f, 100.f), 30.f));
	this->gameWorld->swapObjectType(spline2);
}

GameWorld* MainMenueBackgroundState::getGameWorld() {
	return this->gameWorld;
}

void MainMenueBackgroundState::processEvents() {
	this->gameWorld->doStep();
	this->checkCollision();
	this->draw();
}

void MainMenueBackgroundState::checkCollision() {
	if (this->circle1->collision() && this->circle2->collision()) {
		sf::Texture* tex1 = new sf::Texture();
		tex1->loadFromFile("assets/Object/Player1.jpg");
		this->circle1->setTexture(tex1);
			
		sf::Texture* tex2 = new sf::Texture();
		tex2->loadFromFile("assets/Object/Player2.jpg");
		this->circle2->setTexture(tex2);
		return;
	}
}

void MainMenueBackgroundState::clear(){
	this->gameWorld->clear();
}

void MainMenueBackgroundState::draw(){
	std::vector<Entity*> ent = this->gameWorld->getEntities();
	for (unsigned int i = 0; i < ent.size(); i++) {
		if (dynamic_cast<SplineEntity*>(ent[i]) == nullptr) {
			this->window->draw(*ent[i]->getShape());
		}
		else {
			std::vector<sf::Shape*> shapes = static_cast<SplineEntity*>(ent[i])->getShapes();
			for (unsigned int j = 0; j < shapes.size(); j++)
				this->window->draw(*shapes[j]);
		}
	}
}
