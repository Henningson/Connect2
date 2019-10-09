#include <SFML\Graphics.hpp>

class ProgressBar {
	public:
		ProgressBar(sf::Vector2f pos, sf::Vector2f size, float maxLength);
		void setLength(float length);
		sf::Shape* getBackground();
		sf::Shape* getProgress();

	private:
		sf::Shape* background;
		sf::Shape* progress;
		sf::Shape* outline;
		float maxLength;
};