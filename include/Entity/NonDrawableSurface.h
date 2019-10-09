#pragma once
#include <SFML\Graphics.hpp>

class NonDrawableSurface : public sf::RectangleShape {
	public:
		NonDrawableSurface(sf::Vector2f position, sf::Vector2f size);

	protected:
		sf::Texture* texture;
};