#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "ScreenState.hpp"

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

    sf::Font m_font;
    std::vector< sf::Text > m_menus;

    sf::Texture m_background_texture;
    sf::Sprite m_background;
    
    sf::Music m_music;
};
