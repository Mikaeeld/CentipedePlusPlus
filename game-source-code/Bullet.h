#pragma once
#include "GameEntity.h"
#include "SFML/Graphics.hpp"
#include "Ship.h"

using Texture_ptr = shared_ptr<sf::Texture>;

class Bullet : public GameEntity
{
public:
	Bullet();

	void tick(const sf::Time &time);
	constexpr static const float MIN_Y = -7.0f;

	static const sf::Vector2f VELOCITY;

	bool handleCollision(entityType type, sf::FloatRect collisionRect, const shared_ptr<GameEntity> other);
	entityType getType();

private:
};