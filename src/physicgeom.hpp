#pragma once

#include <memory>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <array>

using Triangle = std::array<sf::Vector2f, 3>;


class PhysicGeom
{
	using PointList = std::vector<sf::Vector2f>;
	
	public:
		PhysicGeom()=default;
		PhysicGeom(std::initializer_list<sf::Vector2f> points);

		std::size_t addPoint(const sf::Vector2f& point);
		void removePoint(std::size_t id);

		const sf::Vector2f& getPoint(std::size_t id) const;
		void setPoint(std::size_t id, const sf::Vector2f& point);

		const PointList& getPoints() const;

		std::size_t count();

		void compute();

		bool contains(const sf::Vector2f& point) const;

		using Ptr = std::unique_ptr<PhysicGeom>;
	private:


		bool m_isComputed;

		std::vector<sf::Vector2f> m_points;
		std::vector<Triangle> m_backedTriangle;



};
