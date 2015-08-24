#include "wallscenenode.hpp"
#include "entityscene.hpp"
#include "physicinstance.hpp"
#include "gameworld.hpp"

WallSceneNode::WallSceneNode(SceneNode& father, sf::FloatRect rect, GameContext& context) :  m_size(rect.width, rect.height) {

	m_entity = context.entityPool->createEntity();
	auto node = context.scene->bindEntity(m_entity);
	auto body = context.physic->bindEntity(m_entity);
	body->setNode(node);
	//body->setHitbox(hitBox);

	//node->setAbsolutePosition(pos);

}

sf::FloatRect WallSceneNode::getRect()
{
    //return sf::FloatRect(getPosition(), getSize());
}
