#include "AnimatedSprite.h"

class AnimationManager {
public:
	AnimationManager();
	void addAnimatedSprite(AnimatedSprite* animatedSprite);
	void drawAnimations(sf::RenderTarget& target, sf::RenderStates states);

private:
	std::vector<AnimatedSprite*> sprites;
};