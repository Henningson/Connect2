#pragma once
#include "GameState.h"
#include "GameWorld.h"
#include "SFMLDebugDraw.h"
#include "ContactListener.h"
#include "ProgressBar.h"
#include "Level.h"
#include <SFML\Audio.hpp>

class PlayingState : public GameState {
	public:
		PlayingState(sf::RenderWindow* window, bool drawGui, Level* level);
		GameWorld* getGameWorld();
		void processEvents() override;
		void generateLevel();
		void checkCollision();
		bool checkOutOfBounds(CircleEntity* ce);
		virtual void clear();
		virtual void draw();
		void setSplineLength(float length);
		Level* getLevel();
		void useMessageFromPrev(std::string message) override;
		void run();
		void restart();
		void showLostGUI();
		void showWonGUI();

	private:
		sf::Sound sound;
		sf::SoundBuffer buffer;
		GameWorld* gameWorld;
		bool drawGui;
		bool runGame = false;
		ContactListener* cl;
		SplineEntity* spline;
		CircleEntity* playerOne;
		CircleEntity* playerTwo;
		ProgressBar* progressBar;
		Level* level;
		float splineLength;
};