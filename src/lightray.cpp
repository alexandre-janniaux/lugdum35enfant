#include "lightray.hpp"

LightRay::LightRay(sf::ConvexShape ray)
: m_ray(ray)
{
    m_ray.setOutlineThickness(1);
}

void LightRay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_ray);
}
