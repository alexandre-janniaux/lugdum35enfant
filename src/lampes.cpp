#include "lampes.hpp"
#include "gameworld.hpp"

Lampe::Lampe(sf::Sprite& sprite, sf::Vector2f pos, sf::Color color, sf::Vector2f origin, float r, float angleStart, float angleEnd, bool on, GameContext& context) :
     /*m_sn(father, pos, 100, sprite),*/ m_color(color), m_origin(origin), m_rayon(r), m_angleStart(angleStart), m_angleEnd(angleEnd), m_isOn(on)
{}

bool Lampe::isLighting(sf::Vector2f point) const
{
    sf::Vector2f d = point - m_origin;
    return m_isOn && (d.x * d.x + d.y * d.y <= m_rayon * m_rayon);
}

void Lampe::switcher()
{
    m_isOn = !m_isOn;
}
