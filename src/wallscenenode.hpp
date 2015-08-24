#ifndef HOUSESCENENODE_H_INCLUDED
#define HOUSESCENENODE_H_INCLUDED

#include "scenenode.hpp"
#include "entitypool.hpp"

#include <memory>

class GameContext;

class WallSceneNode
{
    public:
        typedef std::unique_ptr<WallSceneNode> uPtr;
        WallSceneNode(SceneNode& father, sf::FloatRect rect, GameContext& context);
        inline sf::Vector2f const& getSize() const {return m_size;};

		sf::FloatRect getRect();

    protected:
		Entity m_entity;
        sf::Vector2f m_size;
};


#endif // HOUSESCENENODE_H_INCLUDED
