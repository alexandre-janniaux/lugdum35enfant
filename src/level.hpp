#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
// #include "familymember.hpp"
#include "meuble.hpp"

class FamilyMember
{
    
};

class Floor
{
public:
    Floor (std::vector<Meuble*> meubles, std::vector<sf::FloatRect> murs, std::vector<FamilyMember> family_members, sf::Vector2f size);
    Floor (Json::Value floor);
    void update();

// private:
    std::vector<Meuble*> m_meubles;
    std::vector<FamilyMember> m_family_members;
    std::vector<sf::FloatRect> m_murs;
    sf::Vector2f m_size;
    std::map<std::string, sf::Texture> m_txMeubles;
};

class Level
{
public:
    void update();
    Level (int id, sf::Vector2f cp, std::vector<Floor> floors);
    Level(std::istream &is);
private:
    int m_id_floor;
    sf::Vector2f m_checkPoint;
    std::vector<Floor> m_floors;
};




#endif // LEVEL_H_INCLUDED
