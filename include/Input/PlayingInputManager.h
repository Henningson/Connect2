#include "InputManager.h"
#include "Box2D\Box2D.h"
#include "SplineEntity.h"

class PlayingInputManager : public InputManager {
	public:
		PlayingInputManager(GameState* game, float scale);
		void processEvents() override;

	private:
		virtual void handlePlayerInput(sf::Mouse::Button button) override;
		virtual void handlePlayerInput(sf::Keyboard::Key key, bool keyPressed) override;
		void toggleDrag();
		void finalizeLine();
		float getCurrentLength();

	private:
		SplineEntity* spline;
		float length = 0.0f;
		float currentLength = 0.0f;
		float maxLength = 1000.f;
		float scale;
		bool dragging = false;
		bool denyDrawing = false;
		bool start = true;
		sf::Clock clock;
};