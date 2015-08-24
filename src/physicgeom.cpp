#include "physicgeom.hpp"
#include <algorithm>

PhysicGeom::PhysicGeom(std::initializer_list< sf::Vector2f > points)
{
	m_points = points;
	m_isComputed = false;
}

std::size_t PhysicGeom::addPoint(const sf::Vector2f& point)
{
	m_points.push_back(point);
	m_isComputed = false;
}

void PhysicGeom::compute()
{
	if (m_isComputed) return;

	// TODO: Delaunay triangulation
}

bool PhysicGeom::contains(const sf::Vector2f& point) const
{
	if (count() < 3)
		return false;
}


std::size_t PhysicGeom::count() const
{
	return m_points.size();
}

const sf::Vector2f& PhysicGeom::getPoint(std::size_t id) const
{
	return m_points.at(id);
}

const PhysicGeom::PointList& PhysicGeom::getPoints() const
{
	return m_points;
}


void PhysicGeom::setPoint(std::size_t id, const sf::Vector2f& point)
{
	m_points.at(id) = point;
	m_isComputed = false;
}


