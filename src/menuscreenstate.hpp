#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "screenstate.hpp"
#include "sousmenu.hpp"
#include "menuelements.hpp"

class MenuScreenState : public ScreenState
{
public:
    MenuScreenState();
    virtual ~MenuScreenState()=default;

    void event(const sf::RenderTarget& target, const sf::Event& event);
    void render(sf::RenderTarget& target);
    void update(const sf::Time& time);


private:
    int m_menuSize;
    int m_selected;

    sf::View m_view;

    SousMenu m_sousmenu;
    
    sf::Texture m_background_texture;
    sf::Sprite m_background;
    
    sf::Music m_music;
};
