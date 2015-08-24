#include <fstream>
#include "gameworld.hpp"
#include "json/json.h"
#include "resourcemanager.hpp"

namespace {

sf::Sprite toSprite(Json::Value v)
{
    auto tManager = TextureManager::instance();
    std::string str = v.get("file", "").asString();
    if (str.empty())
        return sf::Sprite();
    else
#if __APPLE__
        return sf::Sprite(tManager->get(str));
#else
        return sf::Sprite(tManager->get("graphics/" + str));
#endif
}

sf::Vector2f toVect(Json::Value v)
{
    return sf::Vector2f(v["x"].asDouble(), v["y"].asDouble());
}

sf::FloatRect toRect(Json::Value v)
{
    return sf::FloatRect(v["x"].asDouble(), v["y"].asDouble(),
            v["w"].asDouble(), v["h"].asDouble());
}

sf::Color toC(Json::Value v)
{
    if (v == Json::Value::null)
        return sf::Color::White;
    else
        return sf::Color(v["r"].asInt(), v["g"].asInt(), v["b"].asInt(), v.get("a", 255).asInt());
}

} // end namespace

GameContext::GameContext(sf::RenderWindow& win, SceneNode& father) :
    window(win), sceneNode(father)
{}


GameWorld::GameWorld(std::string const& fileName, sf::RenderWindow & window, SceneNode & father) :
    m_context(window, father)
{
    std::ifstream file(fileName.c_str());
    if (!file)
    {
        std::cerr << "Error: can't open file " << fileName << std::endl;
        return;
    }

    Json::Value root;
    Json::Reader reader;
    if( !reader.parse(file, root, false) )
    {
        std::cout << "Error while reading level file:\n" << reader.getFormattedErrorMessages();
        return;
    }

    std::cerr << 0 << std::endl;

    /* Parsing the initial position and size */
    m_size = toVect(root["size"]);
    m_checkPoint = toVect(root["initialPos"]);

    std::cerr << 2 << std::endl;

    /* Parsing Lampes */
    Json::Value lampes = root["lampes"];
    for (unsigned int i = 0 ; i < lampes.size() ; i++)
    {
        Json::Value lampe = lampes[i];
        sf::Sprite sprite(toSprite(lampe["sprite"]));
        m_lampes.push_back(L_ptr (new Lampe(father, sprite, toVect(lampe["position"]), toC(lampe["color"]), toVect(lampe["position"]), lampe["r"].asDouble(), lampe["angleStart"].asDouble(), lampe["angleEnd"].asDouble(), lampe["isOn"].asBool())));
    }

    std::cerr << 3 << std::endl;

    /* Parsing Meubles */
    Json::Value meubles = root["meubles"];
    for (unsigned int i = 0 ; i < meubles.size() ; i++)
    {
        Json::Value meuble = meubles[i];
        sf::Sprite sprite(toSprite(meuble["sprite"]));
        sf::FloatRect hitBox(toRect(meuble["hitBox"]));
        sf::Vector2f pos(toVect(meuble["hitBox"]));

        /* Discrimination des types de meubles */
        std::string str = meuble["type"].asString();

        if (str == "tapis")
        {
            m_meubles.push_back(M_ptr (new Tapis(sprite, pos, father, hitBox,
                        toRect(meuble["tapishitBox"]))));
        }

        else if (str == "bruit")
        {
            float tmp = meuble["bruitTemps"].asDouble();
            m_meubles.push_back(M_ptr (new MeubleBruit(sprite, pos, father ,hitBox, sf::seconds(tmp))));
        }

        else if (str == "lit")
            m_meubles.push_back(M_ptr (new Lit(sprite, pos, father, hitBox)));

        else if (str == "interrupteur")
            m_meubles.push_back(M_ptr (new Interrupteur(sprite, pos, father, hitBox, *m_lampes[meuble["lumiere"].asInt()])));

        else if (str == "cachette")
            m_meubles.push_back(M_ptr (new Cachette(sprite, pos, father, hitBox)));
    }

    std::cerr << 4 << std::endl;

    /* Parser les murs */
    Json::Value murs = root["murs"];
    for (unsigned int i = 0 ; i < murs.size() ; i++) 
        m_murs.push_back(WallSceneNode::uPtr(new WallSceneNode(father, toRect(murs[i]))));

    std::cerr << 5 << std::endl;

    /* Parser les family member */
    // TODO
}
