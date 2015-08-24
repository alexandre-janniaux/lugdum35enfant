#include <SFML/Graphics.hpp>
#include "level.hpp"
#include "hud.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "cute editor");
    sf::View levelView (sf::FloatRect(0.0f, 0.0f, 600.0f, 600.0f));
    levelView.setViewport(sf::FloatRect(0.25f, 0.0f, 0.75f, 1.0f));
    TileHolder tiles;

    sf::Font myFont;
    myFont.loadFromFile("font.ttf");
    Level myLevel(tiles, levelView, myFont);
    Hud myHud(myFont, tiles);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            myHud.update(event, window, myLevel);
            myLevel.updateEvents(event, window);
        }
        myLevel.update(window);

        window.clear();
        myLevel.render(window);
        myHud.render(window);
        window.display();
    }

    return EXIT_SUCCESS;
}
