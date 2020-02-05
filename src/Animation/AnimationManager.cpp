#pragma once
#include "AnimationManager.h"

AnimationManager::AnimationManager() {}

void AnimationManager::drawAnimations(sf::RenderTarget& target, sf::RenderStates states) {
	for (AnimatedSprite* sprite : this->sprites) {
		//sprite->draw(target, states);
	}
}

void AnimationManager::addAnimatedSprite(AnimatedSprite* sprite) {
	this->sprites.push_back(sprite);
}