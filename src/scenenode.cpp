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

void SceneNode::compute() const//std::multimap<int,SceneNode*>& renderQueue,bool force)
{
    if (!m_computed)
    {
        if (m_parent != nullptr)
        {
            m_absoluteTransform = m_parent->getAbsoluteTransform() * getTransform();
        }
        else
            m_absoluteTransform = getTransform();

    }
    m_computed=true;
}

void SceneNode::invalidate()
{
    m_computed=false;
    for (auto& it : m_children)
    {
        it->invalidate();
    }
}

void SceneNode::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
}

const sf::Transform& SceneNode::getAbsoluteTransform() const
{
    compute();
    return m_absoluteTransform;
}
