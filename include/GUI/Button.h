#pragma once
#include <SFML\Graphics.hpp>
#include <functional>

class Button {
	public:
		Button(sf::Text* text);
		void select();
		void deselect();
		bool isSelected();
		void setOnClickEvent(std::function<void(std::string Level)> f);
		sf::Text* getText();

	public:
		virtual sf::FloatRect getLocalBounds();
		virtual bool contains(sf::Vector2f pos);
		virtual void onClick(std::string text);

	protected:
		bool selected = false;
		sf::Text* text;
		std::function<void(std::string text)> func;
};