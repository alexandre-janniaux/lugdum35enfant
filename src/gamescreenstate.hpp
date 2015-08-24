#pragma once

#include "screenstate.hpp"
#include "entityscene.hpp"
#include "entitypool.hpp"
#include "physicinstance.hpp"
#include "collisionsolver.hpp"
#include "gameworld.hpp"
#include "hero.hpp"

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GameScreenState : public ScreenState {
    public:

    //GameScreenState()=default;
	GameScreenState(sf::RenderWindow* window=nullptr);
    virtual ~GameScreenState()=default;

    void event(const sf::RenderTarget& target, const sf::Event& event) override;
    void render(sf::RenderTarget& target) override;
    void update(const sf::Time& time) override;
    void window_update(const sf::RenderWindow& window) override;

	private:
	sf::View m_view;
	EntityScene m_scene;
	CollisionSolver m_collisionSolver;
	PhysicInstance m_physicInstance;
	EntityPool m_entityPool;

	GameContext m_context;

	std::unique_ptr<GameWorld> m_world;

	Hero* m_hero;

	void updateView(sf::RenderTarget& target);
	void onCollision(PhysicBody& b1, PhysicBody& b2);
};
