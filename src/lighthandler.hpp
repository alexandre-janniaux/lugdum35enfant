#pragma once
#include <SFML/Graphics.hpp>
#include "lamp.hpp"
#include <vector>


class LightHandler
{
    public:
        void computeLights();

    private:
        std::vector<Lamp*> m_lamps;
        std::vector<sf::Rect<float>> m_obstacles;
};
