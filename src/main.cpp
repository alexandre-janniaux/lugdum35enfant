#include "cpp_std_11.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

#include "gamescreenstate.hpp"
#include "menuscreenstate.hpp"
#include "screenstack.hpp"
#include "resourcemanager.hpp"
#include "scene.hpp"
#include "lamp.hpp"
/*
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
*/

void drawSegment(sf::RenderWindow& win,Segment seg)
{
    sf::ConvexShape sh(4);
    sh.setOutlineThickness(0);
    sh.setOutlineColor(sf::Color::Yellow);
    sh.setPoint(0,seg.p1);
    sh.setPoint(1,seg.p2);
    sh.setPoint(3,seg.p1+sf::Vector2f(1.f,1.f));
    sh.setPoint(2,seg.p2+sf::Vector2f(1.f,1.f));
    win.draw(sh);
}

int main(int argc, char** argv)
{
	sf::RenderWindow window;
	sf::String window_title = "Ludum Dare 35";
	sf::VideoMode window_mode (800,600);

	window.create(window_mode, window_title);
	window.setFramerateLimit(60);


	ScreenStack screenStack;
	screenStack.registerState(ScreenState::Menu, make_unique<MenuScreenState>());
//	screenStack.registerState(ScreenState::Game, make_unique<GameScreenState>());

//	screenStack.pushState(ScreenState::Game);
	screenStack.pushState(ScreenState::Menu);

	Scene scene;
	Lamp lamp(sf::Color::Yellow,200.f,0.f,2 * Math::PI);
	lamp.setPosition(sf::Vector2f(250.f,350.f));
	lamp.attachParent(&scene.getRootNode());

	sf::RectangleShape shape1(sf::Vector2f(18.f,18.f));
	shape1.setFillColor(sf::Color::Red);
	shape1.setPosition(sf::Vector2f(201.f,301.f));

	sf::RectangleShape shape2(sf::Vector2f(18.f,48.f));
	shape2.setFillColor(sf::Color::Red);
	shape2.setPosition(sf::Vector2f(301.f,381.f));

	std::vector<sf::Rect<float>> obs;
	obs.clear();
	obs.push_back(sf::Rect<float>(200.f,300.f,20.f,20.f));
	obs.push_back(sf::Rect<float>(300.f,380.f,20.f,50.f));
	lamp.computeLight(obs);
    std::cout << "ghjkl" << std::endl;
	sf::Event event;
	sf::Clock clock;

	sf::Vector2f pos = sf::Vector2f(250.f, 350.f);

	while (window.isOpen()) {
	    while (window.pollEvent(event)) {
	        if (event.type == sf::Event::Closed)
                window.close();
            else
				//menu_screen_state.event(window, event);
                screenStack.onEvent(window, event);
	    }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			pos += sf::Vector2f(0.f, -1.f);
			lamp.setPosition(pos);
			lamp.computeLight(obs);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			pos += sf::Vector2f(-1.f, 0.f);
			lamp.setPosition(pos);
			lamp.computeLight(obs);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			pos += sf::Vector2f(0.f, 1.f);
			lamp.setPosition(pos);
			lamp.computeLight(obs);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			pos += sf::Vector2f(1.f, 0.f);
			lamp.setPosition(pos);
			lamp.computeLight(obs);
		}
	    window.clear();
	    screenStack.onDraw(window);
		//menu_screen_state.render(window);
	    window.draw(scene);
        window.draw(shape1);
        window.draw(shape2); //pour dessiner les obstacles
        /*
        std::vector<Segment> segmentlist=lamp.rectangleToSegments(sf::Rect<float>(300.f,380.f,20.f,50.f));
        for (auto& it : segmentlist)
            drawSegment(window,it);
        */ //Pour dessiner les contours d'un rectangle
	    window.display();
		//screenStack.window_update(window);
		screenStack.onUpdate(clock.getElapsedTime());
		//menu_screen_state.update(clock.getElapsedTime());
        clock.restart();

	}
}
