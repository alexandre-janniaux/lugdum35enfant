#include "scene.hpp"
#include "cpp_std_11.hpp"
#include <iostream>

Scene::Scene() {
    m_sceneNode = std::move(make_unique<SceneNode>(0));
}

void Scene::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    std::multimap<int,SceneNode const*> _renderQueue;
    getRenderQueue(getRootNode(), _renderQueue);

    for (auto& it : _renderQueue)
        target.draw(*it.second, states);
}

SceneNode& Scene::getRootNode() const
{
    return *m_sceneNode.get();
}

void getRenderQueue(SceneNode const& sn, std::multimap<int, SceneNode const*>& queue)
{
    queue.insert(std::pair<int,SceneNode const*>(sn.getLayer(), &sn));
    std::vector<SceneNode*> const &children = sn.getChildren();
    for (auto& it : children)
        getRenderQueue(*it, queue);
}
