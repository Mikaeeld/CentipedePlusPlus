#include "Bullet.h"
#include "SFML/Graphics.hpp"
#include "ResourcePath.h"

Bullet::Bullet()
{
	Texture_ptr normal(new sf::Texture());
	const string base = resourcePath() + "Sprites/Ship/";
	if (!normal->loadFromFile(base + "Bullet.png"))
		throw std::runtime_error("Cannot Load Bullet Image");

	originAtCenter_ = true;
	addKeyFrame(KeyFrame(0.0f, normal));
	setAnimateMode(AnimateMode::pause);
	this->dynamic_ = true;
}

void Bullet::tick(const sf::Time &time)
{

	auto elapsed = time.asSeconds();
	auto distance = VELOCITY * elapsed;
	move(distance);

	if (getPosition().y < MIN_Y)
	{
		toDelete_ = true;
	}
	if (getPosition().x < Ship::MIN_X)
	{
		setPosition(sf::Vector2f{Ship::MIN_X, getPosition().y});
	}
	if (getPosition().x > Ship::MAX_X)
	{
		setPosition(sf::Vector2f{Ship::MAX_X, getPosition().y});
	}
}

const sf::Vector2f Bullet::VELOCITY = sf::Vector2f{0.0f, -400.0f};

GameEntity::entityType Bullet::getType()
{
	return entityType::Bullet;
}

#include <iostream>

bool Bullet::handleCollision(entityType type, sf::FloatRect collisionRect, const shared_ptr<GameEntity> other)
{
	(void)other;
	(void)collisionRect;

	switch (type)
	{
	case entityType::Ship:
	case entityType::Explosion:
	{
		return false;
		break;
	}
	default:
	{
		this->toDelete_ = true;
		break;
	}
	}

	return true;
}