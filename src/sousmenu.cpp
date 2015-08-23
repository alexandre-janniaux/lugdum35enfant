#include "sousmenu.hpp"

SousMenu::SousMenu() : m_menuSize(0), m_spaceBetweenElements(50), m_cursor(0), m_elements()
{

}

SousMenu::~SousMenu()
{
    for(auto elem : m_elements)
	delete elem;
}

void SousMenu::setPosition(sf::Vector2f position)
{
    m_position = position;
}

void SousMenu::event(sf::Event event)
{
    if(event.type == sf::Event::MouseMoved)
    {
	for(unsigned int i = 0; i < m_elements.size(); i++)
	{
	    if(m_elements[i]->getRect().contains({(float)event.mouseMove.x, (float)event.mouseMove.y}))
	    {
		m_elements[m_cursor]->unselect();
		m_elements[i]->select();
		m_cursor = i;
	    }
	}
    }
    
    if(!m_elements.empty())
	m_elements[m_cursor]->event(event);
    
    if(event.type == sf::Event::KeyPressed)
    {
	if(event.key.code == sf::Keyboard::Up)
	{
	    m_elements[m_cursor]->unselect();
	    
	    m_cursor = m_cursor - 1;
	    if(m_cursor < 0)
		m_cursor += m_menuSize;
	    
	    m_elements[m_cursor]->select();
	}
	if(event.key.code == sf::Keyboard::Down)
	{
	    m_elements[m_cursor]->unselect();
	    
	    m_cursor = (m_cursor + 1) % m_menuSize;
	    
	    m_elements[m_cursor]->select();
	}
    }
}


void SousMenu::addElement(MenuElement * element)
{
    element->setPosition(m_position + sf::Vector2f(0, m_menuSize * m_spaceBetweenElements));
    m_elements.push_back(element);
    
    m_menuSize++;
}

void SousMenu::setCursor(int cursor)
{
    m_cursor = cursor;
}

void SousMenu::render(sf::RenderTarget& target)
{
    for(auto el : m_elements)
    {
	el->render(target);
    }
}

void SousMenu::select(int number)
{
    m_elements[number % m_menuSize]->select();
    m_cursor = number % m_menuSize;
}
