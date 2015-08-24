#include "button.hpp"


Button::Button() : visible(false)
{

}

Button::Button(sf::Font *font, std::string text, sf::FloatRect rect) : visible(true)
    , mRect(rect)
    , mText(text)
    , mFont (font)
{

}

bool Button::containsMouse(sf::RenderWindow &window)
{
    auto pos = sf::Mouse::getPosition(window);
    return visible && mRect.left <= pos.x && pos.x <= mRect.left + mRect.width
            && mRect.top <= pos.y && pos.y <= mRect.top + mRect.height;
}

void Button::render(sf::RenderWindow &window)
{
    if (visible) {
        sf::RectangleShape bg(sf::Vector2f(mRect.width, mRect.height));
        if (containsMouse(window)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                bg.setFillColor(sf::Color(120, 120, 120));
            else
                bg.setFillColor(sf::Color(190, 190, 190));
        } else {
            bg.setFillColor(sf::Color(220, 220, 220));
        }
        bg.setOutlineColor(sf::Color::Black);
        bg.setOutlineThickness(2.0f);
        bg.setPosition(mRect.left, mRect.top);

        sf::Text text;
        text.setColor(sf::Color::Black);
        text.setString(mText);
        text.setFont(*mFont);
        text.setCharacterSize(20);
        auto bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2.0f, 0.0f);//bounds.height / 2.0f);
        text.setPosition(mRect.left + mRect.width / 2.0f, mRect.top);// + mRect.height / 2.0f);

        window.draw(bg);
        window.draw(text);
    }
}

