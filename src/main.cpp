#include "cpp_std_11.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include "gamescreenstate.hpp"
#include "menuscreenstate.hpp"
#include "screenstack.hpp"
#include "resourcemanager.hpp"
#include "messagebusproxy.hpp"
#include "gameworld.hpp" 
#include "scene.hpp" 


int main(int argc, char** argv)
{

	sf::RenderWindow window;
	sf::String window_title = "Ludum Dare 35";
	sf::VideoMode window_mode (800,600);


	window.create(window_mode, window_title);
	window.setFramerateLimit(60);

	
	ScreenStack screenStack;
	screenStack.registerState(ScreenState::Menu, make_unique<MenuScreenState>());
	screenStack.registerState(ScreenState::Game, make_unique<GameScreenState>());
	
	screenStack.pushState(ScreenState::Menu);
	sf::Event event;
	sf::Clock clock;

	MessageBusProxy<QuitMessage> quitMessageBus([&](const QuitMessage& message){
			window.close();
	});

	while (window.isOpen()) {
	    while (window.pollEvent(event)) {
	        if (event.type == sf::Event::Closed)
                window.close();
            else
                screenStack.onEvent(window, event);
        }

        window.clear();
        screenStack.onDraw(window);

        window.display();
        screenStack.onUpdate(clock.getElapsedTime());
        clock.restart();
		
		quitMessageBus.readAll();
	}
}

