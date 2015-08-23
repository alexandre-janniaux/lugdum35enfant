#include "menuelements.hpp"

MenuElement::MenuElement()
{
    auto fonts = FontManager::instance();
    sf::Font& myfont = fonts->get("menu_font.ttf");
    
    m_displayLabel.setFont(myfont);
}

MenuElement::~MenuElement()
{

}

void MenuElement::select()
{
    m_displayLabel.setStyle(sf::Text::Bold);
    m_displayLabel.setColor(sf::Color::Red);
    m_selected = true;
}

void MenuElement::unselect()
{
    m_displayLabel.setStyle(sf::Text::Regular);
    m_displayLabel.setColor(sf::Color::White);
    m_selected = false;
}

void MenuElement::setPosition(sf::Vector2f position)
{
    m_displayLabel.setPosition(position);
}

sf::FloatRect MenuElement::getRect()
{
    return m_displayLabel.getGlobalBounds();
}


Checkbox::Checkbox(std::function< void(bool) > callback, bool state, sf::String texte) : m_state(state), m_callback(callback)
{
    auto fonts = FontManager::instance();
    sf::Font& myfont = fonts->get("menu_font.ttf");
    
    m_displayLabel.setString(texte);
    
    auto textures = TextureManager::instance();
    sf::Texture& mytexture = textures->get("graphics/checkbox.png");
    
    m_checkboxSprite.setTexture(mytexture);
    
    state ? check() : uncheck();
}

void Checkbox::event(const sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
    {
	m_state = !m_state;
	m_state ? check() : uncheck();
	m_callback(m_state);
    }
    
    if(event.type == sf::Event::MouseButtonPressed)
    {
	if(m_displayLabel.getGlobalBounds().contains({(float)event.mouseButton.x, (float)event.mouseButton.y}))
	{
	    m_state = !m_state;
	    m_state ? check() : uncheck();
	    m_callback(m_state);
	}
    }
}

void Checkbox::render(sf::RenderTarget& target)
{
    target.draw(m_displayLabel);
    target.draw(m_checkboxSprite);
}

void Checkbox::update(sf::Time time)
{

}

void Checkbox::check()
{
    m_state = true;
    m_checkboxSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

void Checkbox::setPosition(sf::Vector2f position)
{
    m_checkboxSprite.setPosition(position + sf::Vector2f(-35, 5));
    m_displayLabel.setPosition(position);
}

void Checkbox::uncheck()
{
    m_state = false;
    m_checkboxSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
}

MultiChoice::MultiChoice(std::function< void(int) > callback, int state, std::vector<sf::String> entries) : m_state(state), m_callback(callback), m_labels(entries)
{
    m_stateNumber = entries.size();
    
    auto textures = TextureManager::instance();
    sf::Texture& mytexture = textures->get("graphics/multichoice.png");
    
    m_displayLabel.setString(entries[0]);
    
    m_leftSprite.setTexture(mytexture);
    m_leftSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    
    m_rightSprite.setTexture(mytexture);
    m_rightSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
}

MultiChoice::~MultiChoice()
{
    
}


void MultiChoice::setPosition(sf::Vector2f position)
{
    m_displayLabel.setPosition(position);
    
    updateSprites();
}

void MultiChoice::updateSprites()
{
    m_leftSprite.setPosition(m_displayLabel.getPosition() + sf::Vector2f(-40, 5));
    m_rightSprite.setPosition(m_displayLabel.getPosition() + sf::Vector2f(m_displayLabel.getLocalBounds().width, 0) + sf::Vector2f(8, 5));
}


void MultiChoice::selectPrevious()
{
    m_state = m_state - 1;
    
    while(m_state < 0)
	m_state += m_stateNumber;
    
    m_displayLabel.setString(m_labels.at(m_state));
    
    m_callback(m_state);
}

void MultiChoice::selectNext()
{
    m_state = (m_state + 1) % m_stateNumber;
    
    m_displayLabel.setString(m_labels.at(m_state));
    
    m_callback(m_state);
}


void MultiChoice::event(const sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
	selectNext();
    }
    
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
	selectPrevious();
    }
    
    if(event.type == sf::Event::MouseButtonPressed)
    {
	if(m_displayLabel.getGlobalBounds().contains({(float)event.mouseButton.x, (float)event.mouseButton.y}))
	{
	    selectNext();
	}
    }
}

void MultiChoice::render(sf::RenderTarget& target)
{
    updateSprites();
    
    target.draw(m_displayLabel);
    target.draw(m_leftSprite);
    target.draw(m_rightSprite);
}

void MultiChoice::update(sf::Time time)
{

}

PushButton::PushButton(std::function< void() > callback, sf::String texte) : m_callback(callback)
{
    auto fonts = FontManager::instance();
    sf::Font& myfont = fonts->get("menu_font.ttf");
    
    m_displayLabel.setString(texte);
}

PushButton::~PushButton()
{

}



void PushButton::event(const sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
	m_callback();
    
    
    if(event.type == sf::Event::MouseButtonPressed)
    {
	if(m_displayLabel.getGlobalBounds().contains({(float)event.mouseButton.x, (float)event.mouseButton.y}))
	{
	    m_callback();
	}
    }
}

void PushButton::render(sf::RenderTarget& target)
{
    target.draw(m_displayLabel);
}

void PushButton::update(sf::Time time)
{

}
