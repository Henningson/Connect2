#include "Game.h"
#include <SFML\Audio.hpp>

int main() {
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("assets/Sounds/intro.wav"))
		return -1;

	sf::Sound sound;
	sound.setBuffer(buffer);

	Game game(1600, 900, "Connect 2", false);
	sound.play();
	game.run();
	return 0;
}
