#pragma once

#include <SFML/Graphics.hpp>
#include "tilemap.hpp"
#include "level.hpp"

#define TILESELECTOR_HEIGHT 300.0f
#define TILESELECTOR_SPACE 2.0f
#define TILESELECTOR_MARGIN 10.0f

#define HUD_WIDTH 200.0f

class TileSelector
{
public :
    TileSelector(TileHolder &tiles);
    void update(sf::RenderWindow &window);
    void updateEvents(sf::Event event, sf::RenderWindow &window, Level &lvl);
    void render(sf::RenderWindow &window);
    void add(std::string filename);
    void rm(int id);
    void rmc();
    void dragScrollbar(sf::RenderWindow &window);
    void grabTile(float x, float y);
    int getSelectedTileID();

private :
    bool mDragging;
    int mSelected;
    float mLastDraggingPos;
    sf::RenderTexture mSurface;
    float mScroll;
    std::vector<int> mIDs;
    TileHolder &mTiles;
};



