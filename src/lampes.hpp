#ifndef LAMPES_H_INCLUDED
#define LAMPES_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "spritescenenode.hpp"

// TODO Utiliser sceneNode
/* classe pour les lampes. */

class Lampe
{
public:
    Lampe(SceneNode &father, sf::Sprite& sprite, sf::Color color, sf::Vector2f origin, float r, float angleStart, float angleEnd, bool on);
    bool isLighting(sf::Vector2f point) const;
    void switcher();
private:
    SpriteSceneNode m_sn;
    sf::Color m_color;
    sf::Vector2f m_origin;
    float m_rayon;
    float m_angleStart, m_angleEnd;
    bool m_isOn;
};

#endif // LAMPES_H_INCLUDED
