#include "scene.hpp"

void Scene::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    std::multimap<int,SceneNode*> _renderQueue;
    m_sceneNode->compute(_renderQueue,false);

    for (auto& it : _renderQueue)
        target.draw(*it.second);
}
