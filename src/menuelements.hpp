#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include "resourcemanager.hpp"

class MenuElement
{
public:
    virtual void event(const sf::Event & event);
    virtual void render(sf::RenderTarget & target) const;
    virtual void update(sf::Time time);
private:
};


class Checkbox
{
public:
    Checkbox(bool state, std::function<void(bool)> callback);
    void event(const sf::Event & event);
    void render(sf::RenderTarget & target) const;
    void update(sf::Time time);
    
private:
    sf::Text m_label;
    bool m_state;
    std::function<void(bool)> m_callback;
};

class PushButton
{
public:
    PushButton(std::function<void()> callback);
    void event(const sf::Event & event);
    void render(sf::RenderTarget & target) const;
    void update(sf::Time time);
    
private:
    sf::Text m_label;
    std::function<void()> m_callback;
};

class MultiChoice
{
public:
    MultiChoice(int state, std::function<void(int)> callback);
    void event(const sf::Event & event);
    void render(sf::RenderTarget & target) const;
    void update(sf::Time time);  
    
private:
    std::vector<sf::Text> m_labels;
    int m_state;
    std::function<void(int)> m_callback;
};



/*
 * checkbox
 * liste
 * boutons
 * 
 */