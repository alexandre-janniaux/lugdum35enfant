#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <vector>
// #include "familymember.hpp"
#include "meuble.hpp"

class FamilyMember
{
    
};

class Floor
{
public:
    void update();
    Floor (std::vector<Meuble*> meubles, std::vector<sf::FloatRect> murs, std::vector<FamilyMember> family_members, sf::Vector2f size);
// private:
    std::vector<Meuble*> m_meubles;
    std::vector<sf::FloatRect> m_murs;
    std::vector<FamilyMember> m_family_members;
    sf::Vector2f m_size;
};

class Level
{
public:
    void update();
    Level (int id, sf::Vector2f cp, std::vector<Floor> floors);
private:
    int m_id_floor;
    sf::Vector2f m_checkPoint;
    std::vector<Floor> m_floors;
};




#endif // LEVEL_H_INCLUDED
