#include <iostream>
#include "scenenode.hpp"

/* SceneNode::SceneNode(SceneNode s) :
: m_children(s.m_children)
, m_parent(s.m_parent)
, m_transform(s.m_transform)
, m_absoluteTransform(s.m_absoluteTransform)
, m_layer(s.m_layer)
, m_computed(s.m_computed)
{}
*/

SceneNode::SceneNode(int layer)
: m_children()
, m_parent()
, m_transform()
, m_absoluteTransform()
, m_layer(layer)
, m_computed(false)
{
}

SceneNode::SceneNode(SceneNode & parent, int layer)
: m_children()
, m_parent()
, m_transform()
, m_absoluteTransform()
, m_layer(layer)
, m_computed(false)
{
    attachParent(parent);
}

SceneNode::~SceneNode()
{
    detachParent();
}

void SceneNode::attachParent(SceneNode& ptrParent)
{
    ptrParent.m_children.push_back(this);
    if(m_parent)
        detachParent();
    m_parent = &ptrParent;
    invalidate();
}

void SceneNode::detachParent()
{
    if (!m_parent)
        return;

    auto _found = std::find_if(m_parent->m_children.begin(), m_parent->m_children.end(), [&] (SceneNode* p) -> bool { return p == this; });

    assert(_found != m_parent->m_children.end());

//    SceneNode* _pointer = *_found;
    m_parent->m_children.erase(_found);
    m_parent = nullptr;

    invalidate();
};


const sf::Transform& SceneNode::getAbsoluteTransform() const
{
    compute();
    return m_absoluteTransform;
}

sf::Vector2f SceneNode::getAbsolutePosition() const
{
	return getAbsoluteTransform().transformPoint(sf::Vector2f(0,0));
}


const sf::Transform& SceneNode::getTransform() const
{
    return m_transform.getTransform();
}

const sf::Vector2f& SceneNode::getPosition() const
{
    return m_transform.getPosition();
}

int SceneNode::getLayer() const
{
    return m_layer;
}

std::vector<SceneNode*> const& SceneNode::getChildren() const
{
    return m_children;
}

void SceneNode::setLayer(int layer)
{
    m_layer = layer;
}


void SceneNode::setPosition(sf::Vector2f const& pos)
{
    m_transform.setPosition(pos);
    invalidate();
}

void SceneNode::setAbsolutePosition(const sf::Vector2f& pos)
{
	m_transform.setPosition(getAbsoluteTransform().getInverse().transformPoint(pos));
}

void SceneNode::move(sf::Vector2f const& mv)
{
    m_transform.move(mv);
    invalidate();
}

void SceneNode::compute() const
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

void SceneNode::invalidate() const
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

