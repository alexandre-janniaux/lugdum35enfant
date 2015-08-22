#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <memory>
#include "scenenode.hpp"
#include <map>

class Scene : public sf::Drawable
{
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        SceneNode* m_sceneNode;
};

#endif // SCENE_HPP_INCLUDED
