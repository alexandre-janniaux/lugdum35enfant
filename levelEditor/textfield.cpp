#include "textfield.hpp"

Textfield::Textfield() : visible(false)
{

}

Textfield::Textfield(const Textfield& other) : selected (false)
    , visible (other.visible)
    , mText (other.mText)
    , mRect (other.mRect)
    , mFont (other.mFont)
{
    mTex = new sf::RenderTexture();
    mTex->create(mRect.width, mRect.height);
}

Textfield::Textfield(sf::RenderTexture *tex, sf::Font *font, sf::FloatRect rect, std::string text) : selected (false)
    , visible (true)
    , mText (text)
    , mRect (rect)
    , mTex (tex)
    , mFont(font)
{
    mTex->create(rect.width, rect.height);
}

Textfield::~Textfield()
{
    delete mTex;
}

void Textfield::render(sf::RenderWindow &window)
{
    if (visible) {
        mTex->clear(sf::Color::White);
        sf::Text text;
        std::string str = mText;
        if (selected) {
            str += "_";
            text.setColor(sf::Color::Black);
        } else {
            text.setColor(sf::Color (150, 150, 150));
        }

        text.setFont(*mFont);
        text.setCharacterSize(20);
        text.setString(str);
        if (selected && text.getLocalBounds().width > mRect.width) {
            text.setOrigin(text.getLocalBounds().width, 0);
            text.setPosition(mRect.width, 0);
        } else {
            text.setPosition(0, 0);
        }
        mTex->draw(text);
        mTex->display();

        sf::Sprite sprite;
        sprite.setTexture(mTex->getTexture());
        sprite.setPosition(mRect.left, mRect.top);
        window.draw(sprite);
    }
}

std::string Textfield::getText()
{
    return mText;
}

bool Textfield::containsMouse(sf::RenderWindow &window)
{
    auto pos = sf::Mouse::getPosition(window);
    return visible && mRect.contains(pos.x, pos.y);/* mPos.x <= pos.x && pos.x <= mPos.x + TEXTFIELD_WIDTH
            && mPos.y <= pos.y && pos.y <= mPos.y + TEXTFIELD_HEIGHT;*/
}

void Textfield::update(sf::Event &event)
{
    if (visible && selected && event.type == sf::Event::TextEntered && event.text.unicode < 128) {
        if (event.text.unicode == 8)
            mText = mText.substr(0, mText.length() - 1);
        else
            mText += event.text.unicode;
    }
}
