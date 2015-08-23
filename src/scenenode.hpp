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
        void detachParent();
        void attachParent(SceneNode*);
        const sf::Transform& getAbsoluteTransform() const;

    public:
        void compute() const;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void invalidate();

    private:
        std::vector<SceneNode*> m_children;
        SceneNode* m_parent;
        mutable sf::Transform m_absoluteTransform;
        mutable bool m_computed;
        int m_layer;
};
