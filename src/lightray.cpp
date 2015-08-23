#include "lightray.hpp"

LightRay::LightRay(sf::ConvexShape ray)
: m_ray(ray)
{

}

void LightRay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_ray);
}
