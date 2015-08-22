#include "ScreenState.hpp"
#include "Level.hpp"
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
	Level level;
	std::vector<sf::RectangleShape> sprites;
	sf::Vector2f pos;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	unsigned char touching_walls[4];
	int advancement;
	void resetPos();
	void updateSprites();
	void updateView(sf::RenderTarget& target);

};
