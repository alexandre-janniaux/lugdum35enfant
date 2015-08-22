#include "MenuScreenState.hpp"

MenuScreenState::MenuScreenState()
{
    m_selected = 0;

    m_menuSize = 5;

    m_font.loadFromFile("menu_font.ttf");

    m_view.reset(sf::FloatRect(0, 0, 800, 600));

    m_view.setSize(800, 600);

    m_menus.resize(m_menuSize);

    for(unsigned int i = 0; i < m_menus.size(); i++)
    {
        m_menus[i].setFont(m_font);
        m_menus[i].setColor(sf::Color::White);
    }

    float space = 40;
    sf::Vector2f offset(50, 50);

    m_menus[0].setString("NEW GAME");
    m_menus[0].setPosition(offset.x, offset.y);

    m_menus[1].setString("LEVEL");
    m_menus[1].setPosition(offset.x, offset.y + space);

    m_menus[2].setString("CREDITS");
    m_menus[2].setPosition(offset.x, offset.y + 2 * space);

    m_menus[3].setString("QUITTER");
    m_menus[3].setPosition(offset.x, offset.y + 3 * space);

    m_background_texture.loadFromFile("background.jpg");

    m_background.setTexture(m_background_texture);
}

void MenuScreenState::event(const sf::RenderTarget& target, const sf::Event& event)
{
    if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
    {
        m_selected = (m_selected - 1);

        while(m_selected < 0)
            m_selected += m_menuSize;
    }
    else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
    {
        m_selected = (m_selected + 1) % m_menuSize;
    }
    else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Return))
    {
        switch(m_selected)
        {
        case 0:
            // NOUVELLE PARTIE
            break;
        case 1:
            // LEVELS
            break;
        case 2:
            // CREDITS
            break;
        case 3:
            // QUITTER
            break;
        case 4:
            // RIEN
            break;
        default:
            break;
        }
    }
}

void MenuScreenState::render(sf::RenderTarget& target)
{
    for(unsigned int i = 0; i < m_menus.size(); i++)
    {
        if((int)i == m_selected)
            m_menus[i].setStyle(sf::Text::Bold);
        else
            m_menus[i].setStyle(sf::Text::Regular);
    }

    target.setView(m_view);

    target.draw(m_background);

    for(auto &element : m_menus)
        target.draw(element);
}

void MenuScreenState::update(const sf::Time& time)
{

}
