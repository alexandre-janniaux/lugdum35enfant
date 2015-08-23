LightRay::LightRay(sf::ConvexShape ray)
: m_ray(ray)
{

}

void draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    window.draw(m_ray);
}
