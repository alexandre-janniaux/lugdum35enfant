#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class PlainText
{
public :
    PlainText() = default;
    PlainText(sf::Font *font, std::string text, sf::Vector2f position);
    void render(sf::RenderWindow &window);

private :
    std::string mText;
    sf::Vector2f mPos;
    sf::Font *mFont;
};
