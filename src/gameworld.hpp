#pragma once

#ifndef GAMEWORLD_H_INCLUDED
#define GAMEWORLD_H_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
// #include "familymember.hpp"
#include "meuble.hpp"
#include "wallscenenode.hpp"
#include "json/json.h"

struct GameContext
{
    GameContext(sf::RenderWindow & window, SceneNode & father);

    sf::RenderWindow & window;
    SceneNode& sceneNode;
};

class GameWorld
{
public:
    GameWorld(std::string const& fileName, sf::RenderWindow& win ,SceneNode& father);
    void getTileMap(Json::Value v, SceneNode& father);

//private:
    typedef std::unique_ptr<Meuble> M_ptr;
    typedef std::unique_ptr<Lampe> L_ptr;

    GameContext m_context;
    sf::Vector2f m_size;
    sf::Vector2f m_checkPoint;
    std::vector<L_ptr> m_lampes;
    std::vector<M_ptr> m_meubles;
    //std::vector<FamilyMember> m_family_members;
    std::vector<WallSceneNode> m_murs;
    std::vector<SpriteSceneNode> m_tiles;
};

#endif // GAMEWORLD_H_INCLUDED
