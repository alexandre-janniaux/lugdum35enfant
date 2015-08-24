#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <map>
#include <assert.h>

class Scene;

class SceneNode: public sf::Drawable
{
    public:

        SceneNode(int layer = 0);
        SceneNode(SceneNode & parent, int layer = 0);
        ~SceneNode();
        void detachParent();
        void attachParent(SceneNode&);
        const sf::Transform& getAbsoluteTransform() const;
		sf::Vector2f getAbsolutePosition() const;
        const sf::Transform& getTransform() const;
        const sf::Vector2f& getPosition() const;
        int getLayer() const;
        std::vector<SceneNode*> const& getChildren() const;
        void setLayer(int layer);
        void setPosition(sf::Vector2f const& pos);
		void setAbsolutePosition(sf::Vector2f const& pos);
        void move(sf::Vector2f const& mv);

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void compute() const;
        void invalidate() const;

    private:
        std::vector<SceneNode*> m_children;
        SceneNode* m_parent;
        sf::Transformable m_transform;
        mutable sf::Transform m_absoluteTransform;
        int m_layer;
        mutable bool m_computed;
};
