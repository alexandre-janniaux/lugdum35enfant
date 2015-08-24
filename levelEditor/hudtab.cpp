#include "hudtab.hpp"
#ifdef __APPLE__
#include "ResourcePath.hpp"
#endif

HudTab::HudTab(sf::Font &font) : mFont(font)
    , mTextfields (0)
    , mButtons (0)
    , mPlainTexts (0)
{

}

void HudTab::addTextfield(sf::FloatRect rect, std::string text)
{
    sf::RenderTexture *tex = new sf::RenderTexture();
    mTextfields.push_back(Textfield (tex, &mFont, rect, text));
}

void HudTab::addButton(sf::FloatRect rect, std::string text)
{
    mButtons.push_back(Button (&mFont, text, rect));
}

void HudTab::addText(sf::Vector2f pos, std::string text)
{
    mPlainTexts.push_back(PlainText (&mFont, text, pos));
}

void HudTab::render(sf::RenderWindow &window)
{
    for (auto &textfield : mTextfields) {
        textfield.render(window);
    }
    for (auto &button : mButtons) {
        button.render(window);
    }
    for (auto &text : mPlainTexts) {
        text.render(window);
    }
}

void HudTab::update(sf::Event &event, sf::RenderWindow &window)
{

}

MainTab::MainTab(sf::Font &font) : HudTab(font)
{
    addTextfield(sf::FloatRect (5.0f, 5.0f, 125.0f, 25.0f), "test.lvl");
    addButton(sf::FloatRect(144.0f, 7.0f, 21.0f, 21.0f), "+");
    addButton(sf::FloatRect(174.0f, 7.0f, 21.0f, 21.0f), "-");
    addButton(sf::FloatRect(5.0f, 35.0f, 90.0f, 25.0f), "load file");
    addButton(sf::FloatRect(105.0f, 35.0f, 90.0f, 25.0f), "save file");
}

void MainTab::update(sf::Event &event, sf::RenderWindow &window, Level &lvl)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        for (auto &textfield : mTextfields) {
            textfield.selected = textfield.containsMouse(window);
        }
        if (mButtons[0].containsMouse(window))
            lvl.zoom(1);
        if (mButtons[1].containsMouse(window))
            lvl.zoom(-1);
        if (mButtons[3].containsMouse(window))
            lvl.save(mTextfields[0].getText());
    } else if (event.type == sf::Event::TextEntered) {
        for (auto &textfield : mTextfields) {
            textfield.update(event);
        }
    }
}

TileTab::TileTab(sf::Font &font, TileHolder& tiles) : HudTab(font)
    , mTileSelector (tiles)
{
    addTextfield(sf::FloatRect(5.0f, 120.0f, 190.0f, 25.0f), "default-tile.png");
    addButton(sf::FloatRect(10.0f, 155.0f, 180.0f, 25.0f), "create new tile");
    addButton(sf::FloatRect(10.0f, 190.0f, 85.0f, 45.0f), "remove\ncurrent");
    addButton(sf::FloatRect(105.0f, 190.0f, 85.0f, 45.0f), "   set   \nwalkable");
}

void TileTab::render(sf::RenderWindow &window)
{
    for (auto &textfield : mTextfields) {
        textfield.render(window);
    }
    for (auto &button : mButtons) {
        button.render(window);
    }
    mTileSelector.render(window);
}

void TileTab::update(sf::Event &event, sf::RenderWindow &window, Level &lvl)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        for (auto &textfield : mTextfields) {
            textfield.selected = textfield.containsMouse(window);
        }
        if (mButtons[0].containsMouse(window))
            mTileSelector.add(mTextfields[0].getText());
        else if (mButtons[1].containsMouse(window))
            mTileSelector.rmc();
    } else if (event.type == sf::Event::TextEntered) {
        for (auto &textfield : mTextfields) {
            textfield.update(event);
        }
    }
    mTileSelector.updateEvents(event, window, lvl);
    mTileSelector.update(window);
}

FurnitureTab::FurnitureTab(sf::Font &font) : HudTab(font)
{
    addTextfield(sf::FloatRect (5.0f, 130.0f, 150.0f, 25.0f), "test.jpg");
    addButton(sf::FloatRect(165.0f, 132.0f, 30.0f, 21.0f), "add");
    addButton(sf::FloatRect(10.0f, 160.0f, 180.0f, 25.0f), "edit hitbox");
    addButton(sf::FloatRect(10.0f, 190.0f, 180.0f, 25.0f), "edit rug hitbox");
    addButton(sf::FloatRect(10.0f, 220.0f, 180.0f, 25.0f), "remove furniture");

    addText(sf::Vector2f(10.0f, 280.0f), "furniture type");
    addTextfield(sf::FloatRect (5.0f, 310.0f, 150.0f, 25.0f), "tapis");
    addButton(sf::FloatRect(165.0f, 312.0f, 30.0f, 21.0f), "ok");

    addText(sf::Vector2f(10.0f, 340.0f), "sound time");
    addTextfield(sf::FloatRect (5.0f, 370.0f, 150.0f, 25.0f), "18");
    addButton(sf::FloatRect(165.0f, 372.0f, 30.0f, 21.0f), "ok");

    addText(sf::Vector2f(10.0f, 400.0f), "light id");
    addTextfield(sf::FloatRect (5.0f, 430.0f, 150.0f, 25.0f), "0");
    addButton(sf::FloatRect(165.0f, 432.0f, 30.0f, 21.0f), "ok");
}

void FurnitureTab::update(sf::Event &event, sf::RenderWindow &window, Level &lvl)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        for (auto &textfield : mTextfields) {
            textfield.selected = textfield.containsMouse(window);
        }
        if (mButtons[0].containsMouse(window))
            lvl.addFurniture(mTextfields[0].getText());
        if (mButtons[1].containsMouse(window))
            lvl.setState(HITBOX_STATE);
        if (mButtons[2].containsMouse(window))
            lvl.setState(RUG_HITBOX_STATE);
        if (mButtons[3].containsMouse(window))
            lvl.suppressFurniture();
        if (mButtons[4].containsMouse(window))
            lvl.editFurnitureProperty(0, mTextfields[1].getText());
        if (mButtons[5].containsMouse(window))
            lvl.editFurnitureProperty(1, mTextfields[2].getText());
        if (mButtons[6].containsMouse(window))
            lvl.editFurnitureProperty(2, mTextfields[3].getText());
    } else if (event.type == sf::Event::TextEntered) {
        for (auto &textfield : mTextfields) {
            textfield.update(event);
        }
    }
}

IATab::IATab(sf::Font &font) : HudTab(font)
{
    addButton(sf::FloatRect(10.0f, 160.0f, 180.0f, 25.0f), "add AI");
    addButton(sf::FloatRect(10.0f, 190.0f, 180.0f, 25.0f), "edit points");
    addButton(sf::FloatRect(10.0f, 220.0f, 180.0f, 25.0f), "remove AI");
}

void IATab::update(sf::Event &event, sf::RenderWindow &window, Level &lvl)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        for (auto &textfield : mTextfields) {
            textfield.selected = textfield.containsMouse(window);
        }
        if (mButtons[0].containsMouse(window))
            lvl.addEnemy();
        if (mButtons[1].containsMouse(window))
            lvl.setState(POINTS_STATE);
        if (mButtons[2].containsMouse(window))
            lvl.suppressEnemy();
    } else if (event.type == sf::Event::TextEntered) {
        for (auto &textfield : mTextfields) {
            textfield.update(event);
        }
    }
}

TabSelector::TabSelector(sf::Font &font) : mFont(font)
    , mTex ()
{
#ifdef __APPLE__
    if (!mTex.loadFromFile(resourcePath() + "tabs.png"))
        std::cerr << "Cannot load tab image" << std::endl;
#else
    if (!mTex.loadFromFile("tabs.png"))
        std::cerr << "Cannot load tab image" << std::endl;
#endif
}

void TabSelector::render(sf::RenderWindow &window, int tab)
{
    sf::Sprite sprite;
    sprite.setTexture(mTex);
    sprite.setTextureRect(sf::IntRect(0, 25 * tab, 200, 25));
    sprite.setPosition(0.0f, 70.0f);
    window.draw(sprite);

    sf::Text text;
    text.setFont(mFont);
    text.setCharacterSize(20);
    text.setColor(sf::Color::Black);

    text.setString("Tilemap");
    text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
    text.setPosition(38.0f, 76.0f);
    window.draw(text);

    text.setString("Furniture");
    text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
    text.setPosition(112.0f, 76.0f);
    window.draw(text);

    text.setString("IA");
    text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
    text.setPosition(170.0f, 76.0f);
    window.draw(text);
}

void TabSelector::update(sf::Event &event, sf::RenderWindow &window, int &tab, Level &lvl)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.y >= 70.0f && event.mouseButton.y <= 95.0f) {
            if (event.mouseButton.x >= 0.0f && event.mouseButton.x <= 75.0f) {
                tab = 0;
                lvl.setState(BASE_STATE_TILES);
            }
            else if (event.mouseButton.x >= 75.0f && event.mouseButton.x <= 140.0f) {
                tab = 1;
                lvl.setState(BASE_STATE_FURNITURE);
            }
            else if (event.mouseButton.x >= 140.0f && event.mouseButton.x <= 200.0f) {
                tab = 2;
                lvl.setState(BASE_STATE_IA);
            }
        }
    }
}
