#pragma once
#include "elements.hpp"
#include "tilemap.hpp"
#include <string>
#include <fstream>

#define BASE_STATE_TILES -1
#define BASE_STATE_FURNITURE 0
#define BASE_STATE_IA 1
#define HITBOX_STATE 2
#define POINTS_STATE 3
#define RUG_HITBOX_STATE 4

class Level
{
public :
    Level(TileHolder &tiles, sf::View &view, sf::Font &font);
    void render(sf::RenderWindow &window);
    void renderInfoBox(sf::RenderWindow &window, std::string str);
    bool addFurniture(std::string filename);
    void addEnemy();
    void update(sf::RenderWindow &window);
    void updateEvents(sf::Event event, sf::RenderWindow &window);
    bool loadFromFile(std::string filename);
    void getHoveredLayer(sf::RenderWindow &window);
    void drag(sf::RenderWindow &window);
    void zoom(int dir);
    void setState(int state);
    void editFurnitureProperty(int property, std::string val);
    void suppressFurniture();
    void suppressEnemy();
    int selectedTileID;

private :
    sf::View &mView;
    sf::Font &mFont;
    bool mDragging, mDraggingEnemy;
    int mTopLayer, mTopEnemyLayer;
    int mSelectedLayer, mSelectedEnemyLayer;
    int mHoveredLayer, mHoveredEnemyLayer;
    int mZoom;
    int mState;
    int mHitboxCorner;
    sf::Vector2f mDraggingStart;
    sf::Vector2f mSize;
    sf::Vector2f mStart;
    std::vector<Furniture> mFurniture;
    std::vector<Enemy> mEnemies;
    Tilemap mTilemap;
};
