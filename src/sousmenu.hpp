#pragma once

#include <vector>

#include "menuelements.hpp"

class SousMenu
{
public:
    void addElement(MenuElement * element);
    void setCursor(int cursor);
    
private:
    int m_menuSize;
    int m_cursor;
    std::vector< MenuElement* > m_elements;
};