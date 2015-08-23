#include "menuelements.hpp"

MenuElement::MenuElement()
{

}

MenuElement::~MenuElement()
{

}

void MenuElement::select()
{
    m_displayLabel->setStyle(sf::Text::Bold);
    m_selected = true;
}

void MenuElement::unselect()
{
    m_displayLabel->setStyle(sf::Text::Regular);
    m_selected = false;
}

void MenuElement::setPosition(sf::Vector2f position)
{
    m_displayLabel->setPosition(position);
    m_position = position;
}



Checkbox::Checkbox(std::function< void(bool) > callback, bool state, sf::String texte) : m_state(state), m_callback(callback)
{
    auto fonts = FontManager::instance();
    sf::Font& myfont = fonts->get("menu_font.ttf");
    
    m_label.setFont(myfont);
    m_label.setString(texte);
    
    m_displayLabel = &m_label;
}

void Checkbox::event(const sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
    {
	m_state = !m_state;
	m_callback(m_state);
    }
}

void Checkbox::render(sf::RenderTarget& target)
{
    target.draw(m_label);
}

void Checkbox::update(sf::Time time)
{

}

MultiChoice::MultiChoice(int state, std::function< void(int) > callback) : m_state(state), m_callback(callback)
{

}


void MultiChoice::event(const sf::Event& event)
{

}

void MultiChoice::render(sf::RenderTarget& target)
{

}
void MultiChoice::update(sf::Time time)
{

}

PushButton::PushButton(std::function< void() > callback, sf::String texte) : m_callback(callback)
{
    auto fonts = FontManager::instance();
    sf::Font& myfont = fonts->get("menu_font.ttf");
    
    m_label.setFont(myfont);
    m_label.setString(texte);
    
    m_displayLabel = &m_label;
}

PushButton::~PushButton()
{

}



void PushButton::event(const sf::Event& event)
{
    if(m_selected && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
	m_callback();
}

void PushButton::render(sf::RenderTarget& target)
{
    target.draw(m_label);
}

void PushButton::update(sf::Time time)
{

}
