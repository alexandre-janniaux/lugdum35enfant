#pragma once
#include "scenenode.hpp"


class LightRay : public SceneNode
{
    public:
        LightRay(sf::ConvexShape);
        void draw(sf::RenderTarget&, sf::RenderStates) const override;
    private:
        sf::ConvexShape m_ray;
};
