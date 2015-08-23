#pragma once

#include <vector>

#include "menuelements.hpp"
#include "resourcemanager.hpp"

class SousMenu
{
public:
    SousMenu();
    ~SousMenu();
    void setPosition(sf::Vector2f position);
    void render(sf::RenderTarget& target);
    void event(sf::Event event);
    void addElement(MenuElement * element);
    void setCursor(int cursor);
    void select(int number);
    
private:
    sf::Vector2f m_position;
    int m_menuSize;
    int m_cursor;
    float m_spaceBetweenElements;
    std::vector< MenuElement* > m_elements;
};