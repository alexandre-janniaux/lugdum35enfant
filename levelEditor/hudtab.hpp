#pragma once

#include <iostream>
#include "textfield.hpp"
#include "button.hpp"
#include "tileselector.hpp"
#include "plaintext.hpp"
#include "level.hpp"

class HudTab
{
public :
    HudTab(sf::Font &font);
    virtual void render(sf::RenderWindow &window);
    virtual void update(sf::Event &event, sf::RenderWindow &window);
    void addTextfield(sf::FloatRect rect, std::string text);
    void addButton(sf::FloatRect rect, std::string text);
    void addText(sf::Vector2f pos, std::string text);

protected :
    sf::Font &mFont;
    std::vector<Textfield> mTextfields;
    std::vector<Button> mButtons;
    std::vector<PlainText> mPlainTexts;
};

class MainTab : public HudTab
{
public :
    MainTab(sf::Font &font);
    void update(sf::Event &event, sf::RenderWindow &window, Level &lvl);
};

class TileTab : public HudTab
{
public :
    TileTab(sf::Font &font, TileHolder &tiles);
    void render(sf::RenderWindow &window) override;
    void update(sf::Event &event, sf::RenderWindow &window, Level &lvl);

private :
    TileSelector mTileSelector;
};

class FurnitureTab : public HudTab
{
public :
    FurnitureTab(sf::Font &font);
    void update(sf::Event &event, sf::RenderWindow &window, Level &lvl);
};

class IATab : public HudTab
{
public :
    IATab(sf::Font &font);
    void update(sf::Event &event, sf::RenderWindow &window, Level &lvl);
};

class TabSelector
{
public :
    TabSelector(sf::Font &font);
    void render(sf::RenderWindow &window, int tab);
    void update(sf::Event &event, sf::RenderWindow &window, int &tab, Level &lvl);

private :
    sf::Font &mFont;
    sf::Texture mTex;
};
