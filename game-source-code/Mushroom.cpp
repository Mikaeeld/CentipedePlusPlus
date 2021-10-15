#include "Mushroom.h"
#include "SFML/Graphics.hpp"

Mushroom::Mushroom()
{
    Texture_ptr normal(new sf::Texture());
    Texture_ptr break1(new sf::Texture());
    Texture_ptr break2(new sf::Texture());
    Texture_ptr break3(new sf::Texture());

    this->originAtCenter_ = false;

	const string base = "Sprites/Mushroom/";

    if (!normal->loadFromFile(base + "Mushroom1.png"))
        throw std::runtime_error("Cannot Load Ship Image");

    if (!break1->loadFromFile(base + "Mushroom2.png"))
        throw std::runtime_error("Cannot Load Ship Image");

    if (!break2->loadFromFile(base + "Mushroom3.png"))
        throw std::runtime_error("Cannot Load Ship Image");

    if (!break3->loadFromFile(base + "Mushroom4.png"))
        throw std::runtime_error("Cannot Load Ship Image");

        this->setPeriod(3.0);
        this->setAnimateMode(AnimateMode::loop);
        this->addKeyFrame(KeyFrame(0.0, normal));  
        this->addKeyFrame(KeyFrame(25.0, break1));  
        this->addKeyFrame(KeyFrame(50.0, break2));  
        this->addKeyFrame(KeyFrame(75.0, break3));  
}

GameEntity::entityType Mushroom::getType() {
    return GameEntity::entityType::Mushroom;
}