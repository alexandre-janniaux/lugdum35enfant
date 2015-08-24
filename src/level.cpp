#include <istream>
#include "jsoncpp-src-0.5.0/include/json/json.h"
#include "jsoncpp-src-0.5.0/include/json/value.h"
#include "level.hpp"
#include "resourcemanager.hpp"

Level::Level (int id, sf::Vector2f cp, std::vector<Floor> floors) : m_id_floor(id), m_checkPoint(cp), m_floors(floors) {};

Floor::Floor (std::vector<Meuble*> meubles, std::vector<sf::FloatRect> murs, std::vector<FamilyMember> family_members, sf::Vector2f size) : m_meubles(meubles), m_family_members(family_members), m_murs(murs), m_size(size) {};

sf::Vector2f toVect(Json::Value v)
{
    return sf::Vector2f(v["x"].asDouble(), v["y"].asDouble());
}

sf::FloatRect toRect(Json::Value v)
{
    return sf::FloatRect(v["x"].asDouble(), v["y"].asDouble(),
            v["x"].asDouble(), v["y"].asDouble());
}

sf::Color toC(Json::Value v)
{
    if (v == Json::Value::null)
        return sf::Color::White;
    else
        return sf::Color(v["r"].asInt(), v["g"].asInt(), v["b"].asInt(), v.get("a", 255).asInt());
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
    /* initialisation du resourceManager */
    auto tManager = TextureManager::instance();

    /* Parsing Lampes */
    Json::Value lampes = floor["lampes"];
    for (unsigned int i = 0 ; i < lampes.size() ; i++)
    {
        Json::Value lampe = lampes[i];
        sf::Sprite sprite(tManager->get(lampe["sprite"].asString()));
        m_lampes.push_back(Lampe(sprite, toC(lampe["color"]), toVect(lampe["position"]), lampe["r"].asDouble(), lampe["angleStart"].asDouble(), lampe["angleEnd"].asDouble(), lampe["isOn"].asBool()));
    }

    /* Parsing Meubles */
    Json::Value const meubles = floor["meubles"];
    for (unsigned int i = 0 ; i < meubles.size() ; i++)
    {
        sf::Sprite sprite(tManager->get(meubles[i]["sprite"].asString()));

        sf::FloatRect hitBox(toRect(meubles[i]["hitBox"]));

        /* Discrimination des types de meubles */
        std::string str = meubles[i]["type"].asString();

        if (str == "tapis")
        {
            m_meubles.push_back(new Tapis(sprite, hitBox,
                        toRect(meubles[i]["tapishitBox"])));
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
        m_murs.push_back(toRect(murs[i]));

    /* Parser les family member */
    // TODO
}
