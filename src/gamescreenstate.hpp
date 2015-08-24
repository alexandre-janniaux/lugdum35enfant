#pragma once

#include "screenstate.hpp"
#include "scene.hpp"
#include "physicinstance.hpp"
#include "collisionsolver.hpp"

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GameScreenState : public ScreenState {
    public:

    //GameScreenState()=default;
	GameScreenState();
    virtual ~GameScreenState()=default;

    void event(const sf::RenderTarget& target, const sf::Event& event) override;
    void render(sf::RenderTarget& target) override;
    void update(const sf::Time& time) override;
    void window_update(const sf::RenderWindow& window) override;

	private:
	sf::View m_view;
	Scene m_scene;
	CollisionSolver m_collisionSolver;
	PhysicInstance m_physicInstance;


	void updateView(sf::RenderTarget& target);
	void onCollision(PhysicBody& b1, PhysicBody& b2);
};
