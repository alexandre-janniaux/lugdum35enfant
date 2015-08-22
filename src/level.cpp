#include "level.hpp"

Level::Level (int id, sf::Vector2f cp, std::vector<Floor> floors) : m_id_floor(id), m_checkPoint(cp), m_floors(floors) {};

Floor::Floor (std::vector<Meuble*> meubles, std::vector<sf::FloatRect> murs, std::vector<FamilyMember> family_members, sf::Vector2f size) : m_meubles(meubles), m_family_members(family_members), m_murs(murs), m_size(size) {};
