#include "scene.hpp"
#include "cpp_std_11.hpp"

Scene::Scene() {
    m_sceneNode = make_unique<SceneNode>();
}

void Scene::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    std::multimap<int,SceneNode*> _renderQueue;
    m_sceneNode->compute();

    for (auto& it : _renderQueue)
        target.draw(*it.second);
}

SceneNode* Scene::getRootNode() {
    return m_sceneNode.get();
}
