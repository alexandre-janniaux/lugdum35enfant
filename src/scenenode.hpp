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
        SceneNode();
        std::unique_ptr<SceneNode> detachParent();
        void attachParent(SceneNode*);
        void compute(std::multimap<int,SceneNode*>&,bool);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        std::vector<std::unique_ptr<SceneNode> > m_children;
        SceneNode* m_parent;
        sf::Transform m_absoluteTransform;
        bool m_computed;
        int m_layer;
};

class Scene : public sf::Drawable
{
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        SceneNode* m_sceneNode;
};

#endif // SCENENODE_HPP_INCLUDED
