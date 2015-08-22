#ifndef SCENENODE_HPP_INCLUDED
#define SCENENODE_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <map>
#include <assert.h>

class Scene;

class SceneNode: public sf::Transformable, public sf::Drawable
{

    public:
        SceneNode(int layer=0);
        std::unique_ptr<SceneNode> detachParent();
        void attachParent(SceneNode*);
        void compute(std::multimap<int,SceneNode*>&,bool);

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        std::vector<std::unique_ptr<SceneNode> > m_children;
        SceneNode* m_parent;
        sf::Transform m_absoluteTransform;
        bool m_computed;
        int m_layer;
};

#endif // SCENENODE_HPP_INCLUDED
