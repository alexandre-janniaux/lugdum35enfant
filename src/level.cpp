#include <istream>
#include "jsoncpp-src-0.5.0/include/json/json.h"
#include "jsoncpp-src-0.5.0/include/json/value.h"
#include "level.hpp"

Level::Level (int id, sf::Vector2f cp, std::vector<Floor> floors) : m_id_floor(id), m_checkPoint(cp), m_floors(floors) {};

Floor::Floor (std::vector<Meuble*> meubles, std::vector<sf::FloatRect> murs, std::vector<FamilyMember> family_members, sf::Vector2f size) : m_meubles(meubles), m_family_members(family_members), m_murs(murs), m_size(size) {};

sf::FloatRect tof(Json::Value v)
{
    return sf::FloatRect(v["x"].asDouble(), v["y"].asDouble(),
            v["x"].asDouble(), v["y"].asDouble());
}

Level::Level(std::istream &is)
{
    Json::Value root;
    Json::Reader reader;
    if( !reader.parse(is, root, false) )
    {
        std::cout << "Error while reading level file.\n";
        return;
    }

    /* Parsing floors */
    Json::Value const floors = root["floors"];
    for (unsigned int i = 0 ; i < floors.size() ; i++)
        m_floors.push_back(Floor(floors[i]));

    /* Parsing the initial position */
    Json::Value const initPos = root["initialPos"];
    m_id_floor = initPos["f"].asInt();
    m_checkPoint.x = initPos["x"].asDouble();
    m_checkPoint.y = initPos["y"].asDouble();
}

Floor::Floor (Json::Value const floor):
    m_size(floor["size"]["x"].asDouble(), floor["size"]["y"].asDouble())
{
    /* Parsing Meubles */
    Json::Value const meubles = floor["meubles"];
    for (unsigned int i = 0 ; i < meubles.size() ; i++)
    {
        std::string str = meubles[i]["sprite"].asString();
        // TODO: ici, utiliser les resourcesManager
        if (m_txMeubles.find(str) == m_txMeubles.end())
        {
            sf::Texture texture;
            if (!texture.loadFromFile(str))
            {
                std::cout << "Error while reading sprite file.\n";
                return;
            }
            m_txMeubles[str] = texture;
        }
        sf::Sprite sprite(m_txMeubles[str]);

        sf::FloatRect hitBox(tof(meubles[i]["hitBox"]));

        /* Discrimination des types de meubles */
        str = meubles[i]["type"].asString();

        if (str == "tapis")
        {
            m_meubles.push_back(new Tapis(sprite, hitBox,
                        tof(meubles[i]["tapishitBox"])));
        }

        else if (str == "bruit")
        {
            float tmp = meubles[i]["bruitTemps"].asDouble();
            m_meubles.push_back(new MeubleBruit(sprite, hitBox,
                        sf::seconds(tmp)));
        }

        else if (str == "lit")
            m_meubles.push_back(new Lit(sprite, hitBox));

        else if (str == "interrupteur")
            m_meubles.push_back(new Interrupteur(sprite, hitBox,
                        meubles[i]["lumiere"].asInt()));

        else if (str == "cachette")
            m_meubles.push_back(new Cachette(sprite, hitBox));
    }

    /* Parser les murs */
    Json::Value murs = floor["murs"];
    for (unsigned int i = 0 ; i < murs.size() ; i++)
        m_murs.push_back(tof(murs[i]));

    /* Parser les family member */
    // TODO
}
