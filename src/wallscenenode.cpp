#include "wallscenenode.hpp"

#include "gameworld.hpp"

WallSceneNode::WallSceneNode(SceneNode& father, sf::FloatRect rect, GameContext& context) : SceneNode(father, sf::Vector2f(rect.left, rect.top), 5), m_size(rect.width, rect.height) {

	m_entity = context->entityPool->createEntity();
	auto node = context->scene->bindEntity(m_entity);
	auto body = context->physic->bindEntity(m_entity);
	body->setNode(node);
	body->setHitbox(hitBox);

	node->setAbsolutePosition(pos);

}

void WallSceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

sf::FloatRect WallSceneNode::getRect()
{
    //return sf::FloatRect(getPosition(), getSize());
}
