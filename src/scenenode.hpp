#pragma once

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
        SceneNode* detachParent();
        void attachParent(SceneNode*);
        void compute(std::multimap<int,SceneNode*>&,bool);

        const sf::Transform& getAbsoluteTransform() const;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        std::vector<SceneNode*> m_children;
        SceneNode* m_parent;
        sf::Transform m_absoluteTransform;
        bool m_computed;
        int m_layer;
};
