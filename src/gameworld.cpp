#include <fstream>
#include "gameworld.hpp"
#include "json/json.h"
#include "resourcemanager.hpp"

#define TILE_WIDTH 100
#define TILE_HEIGHT 100

namespace {

sf::Texture* toT(Json::Value v)
{
    auto tManager = TextureManager::instance();
    std::string str = v.get("file", "").asString();
    if (str.empty())
        return nullptr;
    else
#if __APPLE__
        return &tManager->get(str);
#else
        return &tManager->get("graphics/" + str);
#endif
}

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


GameWorld::GameWorld(GameContext& context, std::string const& fileName, SceneNode & father) : m_context(context)
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


    /* Parsing the initial position and size */
    m_size = toVect(root["size"]);
    m_checkPoint = toVect(root["initialPos"]);


    /* Parsing Lampes */
    Json::Value lampes = root["lampes"];
    for (unsigned int i = 0 ; i < lampes.size() ; i++)
    {
        Json::Value lampe = lampes[i];
        sf::Sprite sprite(toSprite(lampe["sprite"]));
        m_lampes.push_back(L_ptr (new Lampe(father, sprite, toVect(lampe["position"]), toC(lampe["color"]), toVect(lampe["position"]), lampe["r"].asDouble(), lampe["angleStart"].asDouble(), lampe["angleEnd"].asDouble(), lampe["isOn"].asBool())));
        m_lampesThibault.push_back(std::pair<sf::Vector2f, float>(toVect(lampe["position"]), lampe["r"].asDouble()));
    }
    m_interrupteurs.resize(m_lampesThibault.size());


    /* Parsing Meubles */
    Json::Value meubles = root["meubles"];
    for (unsigned int i = 0 ; i < meubles.size() ; i++)
    {
        Json::Value meuble = meubles[i];
        sf::Sprite sprite(toSprite(meuble["sprite"]));
        sf::FloatRect hitBox(toRect(meuble["hitBox"]));
        sf::FloatRect interactBox(toRect(meuble["interactBox"]));
        sf::Vector2f pos(toVect(meuble["hitBox"]));

        /* Discrimination des types de meubles */
        std::string str = meuble["type"].asString();

        if (str == "tapis")
        {
            m_meubles.push_back(M_ptr (new Tapis(sprite, pos, father, hitBox, interactBox)));
            m_cachettes.push_back(std::pair<sf::FloatRect, sf::FloatRect>(interactBox, hitBox));
        }

        else if (str == "bruit")
        {
            float tmp = meuble["bruitTemps"].asDouble();
            m_meubles.push_back(M_ptr (new MeubleBruit(sprite, pos, father ,hitBox, interactBox, sf::seconds(tmp))));
            m_obstacles.push_back(hitBox);
        }

        else if (str == "lit")
        {
            m_meubles.push_back(M_ptr (new Lit(sprite, pos, father, hitBox, interactBox)));
            m_obstacles.push_back(hitBox);
        }


        else if (str == "interrupteur")
        {
            m_meubles.push_back(M_ptr (new Interrupteur(sprite, pos, father, hitBox, interactBox, *m_lampes[meuble["lumiere"].asInt()])));
            m_obstacles.push_back(hitBox);
            m_interrupteurs[meuble["lumiere"].asInt()] = std::pair<sf::FloatRect, sf::FloatRect>(interactBox, hitBox); 
        }

        else if (str == "cachette")
        {
            auto interactBox = hitBox; // TODO TODO interactBox
            m_meubles.push_back(M_ptr (new Cachette(sprite, pos, father, hitBox, interactBox)));
            m_obstacles.push_back(hitBox);
            m_cachettes.push_back(std::pair<sf::FloatRect, sf::FloatRect>(interactBox, hitBox));
        }
    }

    /* Parser la Tilemap */

    Json::Value murs = root["murs"];
    for (unsigned int i = 0 ; i < murs.size() ; i++) 
    {
        m_murs.push_back(WallSceneNode(WallSceneNode(father, toRect(murs[i]))));
        m_obstacles.push_back(toRect(murs[i]));
    }
    
    getTileMap(root["tilemap"], father);

    /* Parser les family member */
    getFamilyMember(root["family"], father);
}

void GameWorld::getFamilyMember(Json::Value v, SceneNode& father)
{

    for (unsigned int i = 0 ; i < v.size() ; i++)
    {
        IA_Type t;
        std::string type = v[i]["type"].asString();
        if (type == "meuble")
            t = MEUBLE;
        else
            t = ZONE;

        Json::Value jreseau = v[i]["reseau"];
        std::vector<sf::Vector2f> reseau;
        for (i ; i < jreseau.size() ; i++)
            reseau.push_back(toVect(jreseau[i]));

        m_family.push_back(FamilyMember(m_size, m_obstacles, reseau, t, toVect(v[i]["pos"]), m_cachettes, m_lampesThibault, m_interrupteurs));
    }
}



void GameWorld::getTileMap(Json::Value v, SceneNode& father)
{
    sf::Vector2i size(v["size"]["x"].asInt(), v["size"]["y"].asInt());

    struct TileType
    {
        Json::Value v;
        bool isMur;
    };

    /* On charge les tiles */
    std::map<char, TileType> tileSet;
    Json::Value tiles = v["tileSet"];
    for (unsigned int i = 0 ; i < tiles.size() ; i++)
        tileSet[tiles[i]["key"].asString()[0]] = TileType {tiles[i]["sprite"], tiles[i]["isMur"].asBool()};


    /* On parse la tilemap */

    /* Commençons par juste stocker les tilesType */
    std::vector<std::vector<TileType>> firstTilemap;
    firstTilemap.resize(size.y);
    for (auto &it : firstTilemap)
        it.resize(size.x);
    Json::Value tilemap = v["tilemap"];
    if (size.y != tilemap.size())
    {
        std::cerr << "Pas le bon nombre de ligne dans la tilemap\n";
    }
    else
    {
        for (unsigned int i = 0 ; i < size.y ; i++)
        {
            std::string str = v["tilemap"][i].asString();
            if (size.x != str.size())
            {
                std::cerr << "Pas le bon nombre de colonnes dans la tilemap\n";
            }
            else
            {
                for (unsigned int j = 0 ; j < size.x ; j++)
                {
                    auto it = tileSet.find(str[j]);
                    if (it == tileSet.end())
                        firstTilemap[i][j] = TileType();
                    else
                        firstTilemap[i][j] = it->second;
                }
            }
        }
    }

    /* Maintenant on fait les sprites adaptés pour les murs */
    enum Flags {None = 0, Gauche = 1<<0, Bas = 1<<1, Droite = 1<<2};
    for (unsigned int i = 0 ; i < size.y ; i++)
    {
        for (unsigned int j = 0 ; j < size.x ; j++)
        {
            if (firstTilemap[i][j].isMur)
            {
                int flag = None;
                if (j > 0 && firstTilemap[i][j - 1].isMur)
                    flag |= Gauche;
                if (j < size.x - 1 && firstTilemap[i][j + 1].isMur)
                    flag |= Droite;
                if (i < size.y - 1 && firstTilemap[i + 1][j].isMur)
                    flag |= Bas;


                sf::Sprite sprite = toSprite(firstTilemap[i][j].v);
                sprite.setTextureRect(sf::IntRect(TILE_WIDTH*flag, 0, TILE_WIDTH, TILE_HEIGHT));
                m_tiles.push_back(SpriteSceneNode(father, sf::Vector2f(TILE_WIDTH * j, TILE_HEIGHT * i), 5, sprite));
            }
            else
                m_tiles.push_back(SpriteSceneNode(father, sf::Vector2f(TILE_WIDTH * j, TILE_HEIGHT * i), 5, toSprite(firstTilemap[i][j].v)));
        }
    }
}
