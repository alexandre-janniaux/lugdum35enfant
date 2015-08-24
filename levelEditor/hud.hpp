#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "level.hpp"
#include "tilemap.hpp"
#include "hudtab.hpp"

#define TILE_TAB 0
#define FURNITURE_TAB 1
#define IA_TAB 2

class Hud
{
public :
    Hud(sf::Font &font, TileHolder &tiles);
    void render(sf::RenderWindow &window);
    void update(sf::Event &event, sf::RenderWindow &window, Level &lvl);
    int tab; // <3

private :
    sf::Font &mFont;
    MainTab mMainTab;
    TileTab mTileTab;
    FurnitureTab mFurnitureTab;
    IATab mIATab;
    TabSelector mTabSelector;
};
