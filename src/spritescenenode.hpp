#ifndef SPRITESCENENODE_HPP_INCLUDED
#define SPRITESCENENODE_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include "scenenode.hpp"



class SpriteSceneNode : public SceneNode
{
    public:
		SpriteSceneNode(int layer=0);
        inline SpriteSceneNode(SceneNode& father, sf::Vector2f pos, int layer, sf::Sprite const& sprite) :
            SceneNode(father, pos, layer), m_sprite(sprite) {}
        void setTexture(const sf::Texture& texture);
		void setSprite(const sf::Sprite& sprite);
		const sf::Sprite& getSprite() const;
		void setVisible(bool);

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::Sprite m_sprite;
        bool m_visible;
};

#endif
