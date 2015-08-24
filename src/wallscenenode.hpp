#ifndef HOUSESCENENODE_H_INCLUDED
#define HOUSESCENENODE_H_INCLUDED

#include "scenenode.hpp"
#include <memory>

class WallSceneNode : public SceneNode
{
    public:
        typedef std::unique_ptr<WallSceneNode> uPtr;
        inline WallSceneNode(SceneNode& father, sf::FloatRect rect) : SceneNode(father, sf::Vector2f(rect.left, rect.top), 5), m_size(rect.width, rect.height) {};
        inline sf::Vector2f const& getSize() const {return m_size;};

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        sf::Vector2f m_size;
};


#endif // HOUSESCENENODE_H_INCLUDED
