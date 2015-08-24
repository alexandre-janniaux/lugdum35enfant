#include "hud.hpp"
#include <iostream>

Hud::Hud(sf::Font &font, TileHolder &tiles) : tab(TILE_TAB)
    , mFont(font)
    , mMainTab (font)
    , mTileTab (font, tiles)
    , mFurnitureTab (font)
    , mIATab (font)
    , mTabSelector (font)
{

}

void Hud::render(sf::RenderWindow &window)
{
    sf::RectangleShape background(sf::Vector2f(HUD_WIDTH, 600.0f));
    background.setFillColor(sf::Color(255, 190, 200));
    window.draw(background);
    mTabSelector.render(window, tab);

    mMainTab.render(window);
    if (tab == TILE_TAB)
        mTileTab.render(window);
    if (tab == FURNITURE_TAB)
        mFurnitureTab.render(window);
    if (tab == IA_TAB)
        mIATab.render(window);
}

void Hud::update(sf::Event &event, sf::RenderWindow &window, Level &lvl)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab)
        tab = !tab;

    mMainTab.update(event, window, lvl);
    mTabSelector.update(event, window, tab, lvl);
    if (tab == TILE_TAB)
        mTileTab.update(event, window, lvl);
    if (tab == FURNITURE_TAB)
        mFurnitureTab.update(event, window, lvl);
    if (tab == IA_TAB)
        mIATab.update(event, window, lvl);
}

