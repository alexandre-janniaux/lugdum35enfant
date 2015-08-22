#include "scenenode.hpp"

void SceneNode::attachParent(SceneNode* ptrParent)
{
    m_parent = ptrParent;
    ptrParent->m_children.push_back(detachParent());
}

std::unique_ptr<SceneNode> SceneNode::detachParent()
{
    auto _found = std::find_if(m_parent->m_children.begin(), m_parent->m_children.end(), [&] (std::unique_ptr<SceneNode>& p) -> bool { return p.get() == this; });

    assert(_found != m_parent->m_children.end());

    std::unique_ptr<SceneNode> _pointer = std::move(*_found);
    m_children.erase(_found);
    m_parent = nullptr;
    return _pointer;
};

void SceneNode::compute(std::multimap<int,SceneNode*>& renderQueue,bool force)
{
    if (!m_computed || force) {
        m_absoluteTransform = (m_parent == nullptr) ? getTransform() : m_parent->m_absoluteTransform * getTransform();
    }

    for (auto& it : m_children) {
        it->compute(renderQueue,!m_computed || force);
    }

    m_computed = true;
    renderQueue.insert(std::pair<int,SceneNode*>(m_layer,this));
}

void SceneNode::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
}

void Scene::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    std::multimap<int,SceneNode*> _renderQueue;
    m_sceneNode->compute(_renderQueue,false);

    for (auto& it : _renderQueue)
        target.draw(*it.second);
}
