#pragma once
#include <SFML\Graphics.hpp>
#include <functional>
#include "Button.h"

class ImageButton : public Button {
	public:
		ImageButton(sf::Shape* shape, sf::Text* text);
		bool contains(sf::Vector2f pos) override;
		void setPosition(sf::Vector2f pos);
		void setSize(sf::Vector2f size);

	private:
		bool selected = false;
		std::function<void()> func;
		sf::Shape* shape;
		sf::Shape* background;
};