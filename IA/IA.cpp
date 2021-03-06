#include "IA.hpp"

IA::IA(App& app, float x, float y, sf::String const name, int const _team, std::map<sf::String, Tank*>& _tanks) : Tank(app, x, y, name, _team),
    follow(this), shoot(this), think(this), tanks(_tanks)
{

}

IA::~IA()
{

}

void IA::handleInput()
{
    if(this->isDestroyed()) return;
    if(collision)
    {
        moving.stop();
        collision = false;
    }

    if(affected)
    {
        shoot.stop();
        affected = false;
    }

    think.update();
    follow.update();
    moving.update(this);
    shoot.update();

    this->regulate_velocity();
    this->calculate_MotionVector();
}

void IA::update(float dt)
{
    Tank::update(dt);
}
