#include "menuscreenstate.hpp"
#include "messagebus.hpp"
#include "gamemessage.hpp"

MenuScreenState::MenuScreenState()
{
    m_sousmenu.setPosition(sf::Vector2f(50, 50));
    m_sousmenu.addElement(new PushButton([](){
		SendMessage(ScreenMessage::Clear());
		SendMessage(ScreenMessage::Push(ScreenState::Game));
	}, "Play"));
    m_sousmenu.addElement(new PushButton([](){}, "Levels"));
    m_sousmenu.addElement(new PushButton([](){
	MessageBus<QuitMessage>::getBus()->push(QuitMessage());
    }, "Quit"));
    m_sousmenu.addElement(new Checkbox([](bool){}, true, "Quit"));
    m_sousmenu.addElement(new MultiChoice([](int){}, 0, {"Test1", "Test2"}));
    
    m_sousmenu.select(0);
    
    m_view.reset(sf::FloatRect(0, 0, 800, 600));

    m_view.setSize(800, 600);
    m_background_texture.loadFromFile("background.png");

    m_background.setTexture(m_background_texture);
    m_background.setScale(800.0f / m_background.getLocalBounds().width,
			  600.0f / m_background.getLocalBounds().height);
  
    if (!m_music.openFromFile("Under_the_bed_-_menu.wav"))
	std::cout << "Can't load menu's music." << std::endl; // error
    m_music.setLoop(true);
    m_music.play();
}

void MenuScreenState::event(const sf::RenderTarget& target, const sf::Event& event)
{
    m_sousmenu.event(event);
}

void MenuScreenState::render(sf::RenderTarget& target)
{
    target.setView(m_view);

    target.draw(m_background);

    m_sousmenu.render(target);
}

void MenuScreenState::update(const sf::Time& time)
{

}
