#ifndef SPRITESCENENODE_HPP_INCLUDED
#define SPRITESCENENODE_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include "scenenode.hpp"


class SpriteSceneNode : public SceneNode
{
    public:
        void setTexture(const sf::Texture& texture);

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::Sprite m_sprite;
};

#endif
