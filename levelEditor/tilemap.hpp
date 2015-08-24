#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

#define TILE_SIZE 40.0f

class TileHolder
{
public :
    TileHolder();
    bool add(std::string filename, int id);
    void rm(int id);
    int freeID();
    sf::Texture& get(int id);

    std::map<int, sf::Texture> mTiles;
    int mFree;
};

class Tilemap
{
public :
    Tilemap(TileHolder &tiles);
    void render(sf::RenderWindow &window, bool tileTab);
    void update(sf::RenderWindow &window, int selectedTileID);

    sf::Vector2u mSize;
    std::vector<std::vector<int>> mMap;
    TileHolder &mTiles;
};
