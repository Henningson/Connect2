#pragma once
#include "GameState.h"
#include "GameWorld.h"
#include "SFMLDebugDraw.h"
#include "ContactListener.h"

class MainMenueBackgroundState : public GameState {
	public:
		MainMenueBackgroundState(sf::RenderWindow* window);
		GameWorld* getGameWorld();
		void processEvents() override;
		void generateLevel();
		void checkCollision();
		virtual void clear();
		virtual void draw();

	private:
		ContactListener* cl;
		GameWorld* gameWorld;
		bool drawGui;
		CircleEntity* circle1;
		CircleEntity* circle2;
};