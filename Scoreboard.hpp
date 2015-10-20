#ifndef SCOREBOARD_HPP_INCLUDED
#define SCOREBOARD_HPP_INCLUDED

#include "Core/GameState.hpp"
#include "Core/Label.hpp"
#include "Core/FontManager.hpp"
#include "Core/TextureManager.hpp"
#include "Core/Str.hpp"
#include <map>
#include <vector>
#include <iostream>

class Scoreboard : public GameState {
private:
    FontManager fontManager;
    TextureManager textureManager;
    std::vector<Label> labels;
    sf::Sprite background;

    void addLabel(sf::Font& font, sf::String text, sf::Color color, unsigned int size, sf::Vector2f pos);
    void checkAndAdd(sf::Font& font, sf::String field, sf::Vector2f& pos, float addToX, std::map<sf::String, int>& data, sf::String nameField, bool needNameField);

public:
    Scoreboard(Game* game, std::map<sf::String, std::map<sf::String, int>> scores, std::map<sf::String, sf::Color> colors);
    virtual ~Scoreboard();

    virtual void handleInput();
    virtual void update(float dt);
    virtual void draw();
};

#endif // SCOREBOARD_HPP_INCLUDED
