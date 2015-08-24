#include "scene.hpp"
#include "cpp_std_11.hpp"
#include <iostream>

Scene::Scene() {
    m_sceneNode = make_unique<SceneNode>();
}

void Scene::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    std::multimap<int,const SceneNode*> _renderQueue;
    getRenderQueue(getRootNode(), _renderQueue);
    m_sceneNode->getAbsoluteTransform();
    for (auto& it : _renderQueue)
    {
        target.draw(*(it.second));
    }
}

SceneNode& Scene::getRootNode() const
{
    return *m_sceneNode.get();
}

void Scene::getRenderQueue(SceneNode const& sn, std::multimap<int, SceneNode const*>& queue) const
{
    queue.emplace(sn.getLayer(), &sn);
    std::vector<SceneNode*> const &children = sn.getChildren();
    if (children.empty()) return;
    for (auto& it : children)
    {
        if (!it) assert(false);
        getRenderQueue(*it, queue);
    }
}
