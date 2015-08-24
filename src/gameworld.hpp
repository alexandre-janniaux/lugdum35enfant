#pragma once

#ifndef GAMEWORLD_H_INCLUDED
#define GAMEWORLD_H_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
#include "IA_familymember.hpp"
#include "meuble.hpp"
#include "wallscenenode.hpp"
#include "json/json.h"

class EntityScene;
class EntityPool;
class PhysicInstance;


struct GameContext
{
    //GameContext(sf::RenderWindow & window, SceneNode & father);

    sf::RenderWindow* window;
    EntityScene* scene;
	EntityPool* entityPool;
	PhysicInstance* physic;

};

class GameWorld
{
public:
    GameWorld(GameContext& context, std::string const& fileName, SceneNode& father);
    void getTileMap(Json::Value v, SceneNode& father);
    void getFamilyMember(Json::Value v, SceneNode& father);

//private:
    typedef std::unique_ptr<Meuble> M_ptr;
    typedef std::unique_ptr<Lampe> L_ptr;

    GameContext& m_context;
    sf::Vector2f m_size;
    sf::Vector2f m_checkPoint;
    std::vector<L_ptr> m_lampes;
    std::vector<M_ptr> m_meubles;
    std::vector<WallSceneNode> m_murs;
    std::vector<SpriteSceneNode> m_tiles;
    std::vector<FamilyMember> m_family;

    std::vector<sf::FloatRect> m_obstacles;
    std::vector<std::pair<sf::FloatRect, sf::FloatRect>> m_cachettes;
    std::vector<std::pair<sf::Vector2f, float>> m_lampesThibault;
    std::vector<std::pair<sf::FloatRect, sf::FloatRect>> m_interrupteurs;
};

#endif // GAMEWORLD_H_INCLUDED
