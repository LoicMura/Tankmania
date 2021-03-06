#include "Map.hpp"
using std::cout;
using std::endl;

Map::Map(Loader<sf::Texture>& tM) : textureLoader(tM)
{

}

Map::~Map()
{

}

void Map::create()
{
    //Generate borders
    for(uint x(0); x < map_width; x++) for(uint y(0); y < map_height; y++)
    {
        uint iterator(x * map_width + y);

        tiles[iterator].setTexture(textureLoader.getRef("grass"));
        tiles[iterator].setPosition(x * 128, y * 128);
    }

    uint limite_x(map_width * 128 / 48),
         limite_y(map_height * 128 / 48);

    for(uint x(0); x < limite_x; x++)
    {
        borders.push_back(Barrel(textureLoader, true, 24 + x * 48, 24, true));
        borders.back().change_direction(rand() % 360);
        borders.push_back(Barrel(textureLoader, true, 24 + x * 48, limite_y * 48 - 24, true));
        borders.back().change_direction(rand() % 360);
    }

    for(uint y(1); y < limite_y - 1; y++)
    {

        borders.push_back(Barrel(textureLoader, true, 24, 24 + y * 48, true));
        borders.back().change_direction(rand() % 360);
        borders.push_back(Barrel(textureLoader, true, limite_x * 48 - 24, 24 + y * 48, true));
        borders.back().change_direction(rand() % 360);
    }

    uint width((map_width - 2) * 128),
         height((map_height - 2) * 128);

    //Generate puddle of oil
    for(uint a(0); a < (uint)(10 + rand() % 20); a++) this->create_puddleOfOil(128 + rand() % width , 128 + rand() % height);

    //Generate barrels
    for(uint a(0); a < (uint)(60 + rand() % 20); a++) this->create_barrel(128 + rand() % width, 128 + rand() % height);

    //Generate forest
    for(uint a(0); a < (uint)(10 + rand() % 10); a++) this->create_forest(128 + rand() % width, 128 + rand() % height, 1 + rand() % 20);

    this->create_scheme();
}

void Map::draw_below(sf::RenderWindow& window)
{
    for(auto& tile : tiles) if(CollisionManager::isVisible(tile.getGlobalBounds(), window.getView())) window.draw(tile);
    for(auto& puddleOfOil : puddleOfOils) if(CollisionManager::isVisible(puddleOfOil.oil.getGlobalBounds(), window.getView())) window.draw(puddleOfOil.oil);
    for(auto& puddleOfOil : puddleOfOils) puddleOfOil.barrel.draw(window);
    for(auto& barrel : borders) barrel.draw(window);
    for(auto& barrel : barrels) barrel.draw(window);
}

void Map::draw_above(sf::RenderWindow& window)
{
    for(auto& tree : forest) tree.draw(window);
}

bool Map::handle_collision(Object& object, float dt)
{
    for(auto& barrel : borders)           if(!barrel.isDestroyed())             if(CollisionManager::collide(object, barrel, dt))             return true;
    for(auto& barrel : barrels)           if(!barrel.isDestroyed())             if(CollisionManager::collide(object, barrel, dt))             return true;
    for(auto& puddleOfOil : puddleOfOils) if(!puddleOfOil.barrel.isDestroyed()) if(CollisionManager::collide(object, puddleOfOil.barrel, dt)) return true;

    return false;
}

void Map::create_scheme()
{
    int a(64);
    AABB node;
    node.w = a;
    node.h = a;
    for(int x(0); x < 128 * 30 / a; x++) for(int y(0); y < 128 * 30 / a; y++)
    {
        bool obstacle(false);
        node.x = x * a;
        node.y = y * a;
        for(auto& barrel : borders)           if(!barrel.isDestroyed())             if(CollisionManager::AABB_and_AABB(node, barrel.getCollisionData(0).aabb))             obstacle = true;
        for(auto& barrel : barrels)           if(!barrel.isDestroyed())             if(CollisionManager::AABB_and_AABB(node, barrel.getCollisionData(0).aabb))             obstacle = true;
        for(auto& puddleOfOil : puddleOfOils) if(!puddleOfOil.barrel.isDestroyed()) if(CollisionManager::AABB_and_AABB(node, puddleOfOil.barrel.getCollisionData(0).aabb)) obstacle = true;

        Pathfinding::graph[std::pair<int, int>(x, y)] = Square(obstacle, 1);
    }

    int b(0);
    for(auto& i : Pathfinding::graph) if(i.second.obstacle) b++;
}

void Map::create_puddleOfOil(float x, float y)
{
    puddleOfOils.push_back(PuddleOfOil());
    PuddleOfOil& puddleOfOil = puddleOfOils.back();

    puddleOfOil.oil.setTexture(textureLoader.getRef("oil"));
    puddleOfOil.oil.setOrigin(45, 45);
    puddleOfOil.oil.setPosition(x, y);

    if(rand() % 2 == 1) puddleOfOil.barrel.setTexture(textureLoader, true);
    else                puddleOfOil.barrel.setTexture(textureLoader, false);

    puddleOfOil.barrel.change_direction(rand() % 360);

    int a(48);
    puddleOfOil.barrel.setPosition(x + (float)(rand() % a - a / 2), y + (float)(rand() % a - a / 2));
}

void Map::create_barrel(float x, float y)
{
    barrels.push_back(Barrel(textureLoader, rand() % 2, x, y));
    barrels.back().change_direction(rand() % 360);
}

void Map::create_forest(float x, float y, uint number_of_tree)
{
    uint margin = number_of_tree * 75,
         width((map_width - 1) * 128),
         height((map_height - 1) * 128);

    for(uint a(0); a < number_of_tree; a++)
    {
        //Nouvelle position
        float new_x((int)x + (rand() % margin + 50)),
              new_y((int)y + (rand() % margin + 50));

        //Ne sort pas de la carte
        new_x = (int)new_x % width;
        new_y = (int)new_y % height;

        if(new_x < 128) new_x += 128;
        if(new_y < 128) new_y += 128;

        forest.push_back(Tree(textureLoader, new_x, new_y));
    }
}
