#ifndef GAMEMODE_HPP_INCLUDED
#define GAMEMODE_HPP_INCLUDED

#include "../Core/GameState.hpp"
#include "../Human.hpp"
#include "../IA/IA.hpp"
#include "../Map.hpp"
#include "../App.hpp"
#include "../Scoreboard.hpp"
#include <SFML/Audio.hpp>

struct KillData {
    sf::String killer,
                victim;
    int team_killer;
};

class GameMode : public GameState
{
protected:
    std::map<sf::String, std::map<sf::String, int>> scores;

    sf::View view;
    void adapt_view_to_window();

    App app;
    void load_textures();

    Map map;
    std::map<sf::String, Tank*> tanks;

    std::stack<KillData> kills;

    sf::String mainPlayer; //Char contr�l� par le joueur
    //Centre la view sur ce char
    sf::String tankToFollow;
    void scrolling();

    void limit_dt(float& dt);
    void handleCollision(Tank* tank, float dt);
    void align_player_barrel();
    sf::Vector2f generate_pos();

    virtual bool isFinished() = 0;

    sf::Sprite cursor;
    sf::Time waitedTime;
    bool updateWaitedTime(float dt);

    sf::Music theme;
    void loadMusicTheme(std::string const& file);

public:
    GameMode(Game* game);
    virtual ~GameMode();

    virtual void handleInput();
    virtual void update(float dt) = 0;
    virtual void draw();
    void finish();
};

#endif // GAMEMODE_HPP_INCLUDED
