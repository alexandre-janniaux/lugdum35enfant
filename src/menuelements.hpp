#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include "resourcemanager.hpp"

class MenuElement
{
public:
    MenuElement();
    virtual ~MenuElement();
    virtual void setPosition(sf::Vector2f position);
    virtual void event(const sf::Event & event)=0;
    virtual void render(sf::RenderTarget& target)=0;
    virtual void update(sf::Time time)=0;
    
    void select();
    void unselect();
    
    sf::FloatRect getRect();
    
protected:
    sf::Text m_displayLabel;
    bool m_selected;
};


class Checkbox : public MenuElement
{
public:
    Checkbox(std::function<void(bool)> callback, bool state, sf::String texte);
    void event(const sf::Event & event);
    void render(sf::RenderTarget & target);
    void update(sf::Time time);
    void check();
    void uncheck();
    void setPosition(sf::Vector2f position) override;
    
private:
    sf::Sprite m_checkboxSprite;
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
    std::function<void()> m_callback;
};

class MultiChoice : public MenuElement
{
public:
    MultiChoice(std::function<void(int)> callback, int state, std::vector<sf::String> entries);
    virtual ~MultiChoice();
    void event(const sf::Event & event);
    void render(sf::RenderTarget & target);
    void update(sf::Time time);
    void setPosition(sf::Vector2f position);
    void selectPrevious();
    void selectNext();
    void updateSprites();
    bool cointainsMouse();
    
private:
    sf::Sprite m_leftSprite;
    sf::Sprite m_rightSprite;
    std::vector<sf::String> m_labels;
    int m_stateNumber;
    int m_state;
    std::function<void(int)> m_callback;
};
