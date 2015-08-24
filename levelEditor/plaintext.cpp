#include "plaintext.hpp"

PlainText::PlainText(sf::Font *font, std::string text, sf::Vector2f pos) : mText(text)
    , mPos(pos)
    , mFont(font)
{

}

void PlainText::render(sf::RenderWindow &window)
{
    sf::Text text;
    text.setFont(*mFont);
    text.setCharacterSize(20);
    text.setPosition(mPos);
    text.setColor(sf::Color::Black);
    text.setString(mText);
    window.draw(text);
}
