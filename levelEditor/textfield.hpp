#pragma once

#include <SFML/Graphics.hpp>

class Textfield
{
public :
    Textfield();
    Textfield(const Textfield& other);
    Textfield(sf::RenderTexture *tex, sf::Font *font, sf::FloatRect position, std::string text);
    ~Textfield();
    void render(sf::RenderWindow &window);
    void update(sf::Event &event);
    std::string getText();
    bool containsMouse(sf::RenderWindow &window);
    bool selected; //yell at me
    bool visible; //again. i like that.

private :
    std::string mText;
    sf::FloatRect mRect;
    sf::RenderTexture *mTex;
    sf::Font *mFont;
};

