#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <memory>
#include "scenenode.hpp"
#include <map>

class Scene : public sf::Drawable
{
    public:
        Scene();
        SceneNode* getRootNode();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        std::unique_ptr<SceneNode> m_sceneNode;
};

#endif // SCENE_HPP_INCLUDED
