#include "Barrel.hpp"

Barrel::Barrel() : indestructible(false)
{
    collisionData.circle.center = Point(this->getPosition());
    collisionData.circle.radius = 24;
}

Barrel::Barrel(TextureManager& textureManager, bool topdown, float x, float y, bool indestructible) : destroyed(false)
{
    this->indestructible = indestructible;
    this->setPosition(x, y);
    this->setTexture(textureManager, topdown);

    collisionData.circle.center = Point(this->getPosition());
    collisionData.circle.radius = 24;
}

Barrel::~Barrel()
{

}

void Barrel::setTexture(TextureManager& textureManager, bool topdown)
{
    if(topdown) Object::setTexture(textureManager.getRef("barrelUp"), 48, 48);
    else        Object::setTexture(textureManager.getRef("barrelSide"), 44, 62);
}

void Barrel::handleInput()
{
}

void Barrel::update(float dt)
{

}

void Barrel::draw(sf::RenderWindow& window)
{
    if(!destroyed) window.draw(sprite);
}

bool Barrel::isDestroyed() const
{
    return destroyed;
}

void Barrel::destroy()
{
    destroyed = true;
}

void Barrel::change_direction(float const new_direction)
{
    float angle = direction - new_direction;
    sprite.rotate(angle);
    direction = new_direction;
}
