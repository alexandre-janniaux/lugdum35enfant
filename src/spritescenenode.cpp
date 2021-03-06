#include "spritescenenode.hpp"
#include <iostream>

SpriteSceneNode::SpriteSceneNode(int layer): SceneNode(layer)
{

}


void SpriteSceneNode::setTexture(const sf::Texture& texture)
{
    m_sprite.setTexture(texture);
}

void SpriteSceneNode::setSprite(const sf::Sprite& sprite)
{
	m_sprite = sprite;
}

const sf::Sprite& SpriteSceneNode::getSprite() const
{
	return m_sprite;
}



void SpriteSceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getAbsoluteTransform();
    target.draw(m_sprite, states);

    //target.draw(sf::CircleShape(49), states);

}
