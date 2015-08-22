#include "menuelements.hpp"

Checkbox::Checkbox(bool state, std::function< void(bool) > callback) : m_state(state), m_callback(callback)
{

}

void Checkbox::event(const sf::Event& event)
{
//    if(sf::Event::Keypressed && 
}

void Checkbox::render(sf::RenderTarget& target) const
{

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

void MultiChoice::render(sf::RenderTarget& target) const
{

}
void MultiChoice::update(sf::Time time)
{

}

PushButton::PushButton(std::function< void() > callback) : m_callback(callback)
{

}


void PushButton::event(const sf::Event& event)
{

}
void PushButton::render(sf::RenderTarget& target) const
{

}
void PushButton::update(sf::Time time)
{

}
