#include "spritescenenode.hpp"

void SpriteSceneNode::setTexture(const sf::Texture& texture)
{
    m_sprite.setTexture(texture);
}

void SpriteSceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}
