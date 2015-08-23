#include "particle.hpp"
#include "scene.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>
int main()
{
    SmokeShape shape_ref;
    shape_ref.m_Shape.setRadius(10.f);

    Scene scene;

    sf::Text text;
    text.setPosition({50.f,90.f});

    ParticleEmitter<SmokeShape> p(shape_ref, scene.getRootNode());
    p.setFrequency(60);
    p.setNumberOfParticles(60);
    p.setNumberOfParticlesMax(100);
    p.setPosition({400.f, 300.f});
    sf::RenderWindow window({800,600}, "toto");

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }
        std::ostringstream stream;
        stream << p.getNumberOfParticles();
        text.setString("Particules : " + stream.str());

        p.update(clock.getElapsedTime());
        clock.restart();
        window.clear(sf::Color::Cyan);
        window.draw(scene);
        window.draw(text);
        window.display();
    }

    return 0;
}


//#include "cpp_std_11.hpp"
//
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include "gamescreenstate.hpp"
//#include "menuscreenstate.hpp"
//#include "screenstack.hpp"
//#include "resourcemanager.hpp"
//
//
//int main(int argc, char** argv)
//{
//	sf::RenderWindow window;
//	sf::String window_title = "Ludum Dare 35";
//	sf::VideoMode window_mode (800,600);
//
//	window.create(window_mode, window_title);
//	window.setFramerateLimit(60);
//
//
//	ScreenStack screenStack;
//	screenStack.registerState(ScreenState::Menu, make_unique<MenuScreenState>());
////	screenStack.registerState(ScreenState::Game, make_unique<GameScreenState>());
//
////	screenStack.pushState(ScreenState::Game);
//	screenStack.pushState(ScreenState::Menu);
//	sf::Event event;
//	sf::Clock clock;
//
//	while (window.isOpen()) {
//	    while (window.pollEvent(event)) {
//	        if (event.type == sf::Event::Closed)
//                window.close();
//            else
//				//menu_screen_state.event(window, event);
//                screenStack.onEvent(window, event);
//	    }
//
//	    window.clear();
//	    screenStack.onDraw(window);
//		//menu_screen_state.render(window);
//	    window.display();
//		//screenStack.window_update(window);
//		screenStack.onUpdate(clock.getElapsedTime());
//		//menu_screen_state.update(clock.getElapsedTime());
//        clock.restart();
//
//	}
//}
