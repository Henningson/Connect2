#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

template <typename T>
// template function to convert sfml vectors to box2d vectors
inline b2Vec2 ConvSfToB2Vec(const sf::Vector2<T>& sfVec, float PPM) {
	return { sfVec.x / PPM, sfVec.y / PPM };
}

// box2d vectors to sfml vectors (float)
inline sf::Vector2f ConvB2VecToSff(const b2Vec2& b2Vec, float PPM) {
	return { b2Vec.x * PPM, b2Vec.y * PPM };
}

// box2d vectors to sfml vectors (integer)
inline sf::Vector2i ConvB2VecToSfi(const b2Vec2& b2Vec, float PPM){
	return { static_cast<int>(b2Vec.x * PPM), static_cast<int>(b2Vec.y * PPM) };
}