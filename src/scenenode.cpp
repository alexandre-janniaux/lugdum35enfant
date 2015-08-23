#include "scenenode.hpp"

SceneNode::SceneNode(int layer)
: m_children()
, m_parent()
, m_absoluteTransform()
, m_computed(false)
, m_layer(0)
{

}

void SceneNode::attachParent(SceneNode* ptrParent)
{
    m_parent = ptrParent;
    ptrParent->m_children.push_back(detachParent());
}

SceneNode* SceneNode::detachParent()
{
    auto _found = std::find_if(m_parent->m_children.begin(), m_parent->m_children.end(), [&] (SceneNode* p) -> bool { return p == this; });

    assert(_found != m_parent->m_children.end());

    SceneNode* _pointer = *_found;
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

const sf::Transform& SceneNode::getAbsoluteTransform() const {
    return m_absoluteTransform;
}
