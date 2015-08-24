#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public :
    Button();
    Button(sf::Font *font, std::string text, sf::FloatRect rect);
    void render(sf::RenderWindow &window);
    bool containsMouse(sf::RenderWindow &window);
    bool visible;

private:
    sf::FloatRect mRect;
    std::string mText;
    sf::Font *mFont;
};

