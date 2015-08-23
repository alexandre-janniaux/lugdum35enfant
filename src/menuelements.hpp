#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include "resourcemanager.hpp"

class MenuElement
{
public:
    MenuElement();
    virtual ~MenuElement();
    void setPosition(sf::Vector2f position);
    virtual void event(const sf::Event & event)=0;
    virtual void render(sf::RenderTarget& target)=0;
    virtual void update(sf::Time time)=0;
    
    void select();
    void unselect();
    
protected:
    sf::Text* m_displayLabel;
    bool m_selected;
    sf::Vector2f m_position;
};


class Checkbox : public MenuElement
{
public:
    Checkbox(std::function<void(bool)> callback, bool state, sf::String texte);
    void event(const sf::Event & event);
    void render(sf::RenderTarget & target);
    void update(sf::Time time);
    
private:
    sf::Text m_label;
    sf::Sprite m_checkbox;
    bool m_state;
    std::function<void(bool)> m_callback;
};

class PushButton : public MenuElement
{
public:
    PushButton(std::function<void()> callback, sf::String texte);
    virtual ~PushButton();
    void event(const sf::Event & event);
    void render(sf::RenderTarget & target);
    void update(sf::Time time);
    
private:
    sf::Text m_label;
    std::function<void()> m_callback;
};

class MultiChoice : public MenuElement
{
public:
    MultiChoice(int state, std::function<void(int)> callback);
    void event(const sf::Event & event);
    void render(sf::RenderTarget & target);
    void update(sf::Time time);  
    
private:
    std::vector<sf::Text> m_labels;
    int m_state;
    std::function<void(int)> m_callback;
};
