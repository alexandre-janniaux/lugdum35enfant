#include "sousmenu.hpp"

void SousMenu::addElement(MenuElement * element)
{
    m_elements.push_back(element);
    m_menuSize++;
}

void SousMenu::setCursor(int cursor)
{
    m_cursor = cursor;
}
