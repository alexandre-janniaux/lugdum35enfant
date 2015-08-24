#include "wallscenenode.hpp"


void WallSceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape m_shape(m_size);
    m_shape.setFillColor(sf::Color::White);
    states.transform *= getAbsoluteTransform();
    target.draw(m_shape, states);
}

sf::FloatRect WallSceneNode::getRect()
{
    return sf::FloatRect(getPosition(), getSize());
}