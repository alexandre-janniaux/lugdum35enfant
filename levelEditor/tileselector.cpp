#include "tileselector.hpp"


TileSelector::TileSelector(TileHolder &tiles) : mDragging(false)
    , mSelected(0)
    , mScroll (0.0f)
    , mIDs (0)
    , mTiles(tiles)
{
    add("default-tile.png");
    add("default-tile2.png");
    mSurface.create(HUD_WIDTH, TILESELECTOR_HEIGHT);
}

void TileSelector::add(std::string(filename))
{
    int id = mTiles.freeID();
    if (mTiles.add(filename, id)) {
        mIDs.push_back(id);;
    }
}

void TileSelector::rm(int id)
{
    if (id != 0) {
        mIDs.erase(mIDs.begin() + id);
        if (mIDs.size() <= mSelected)
            mSelected = mIDs.size() - 1;
        mScroll = std::max(0.0f, std::min(mScroll, (TILE_SIZE + TILESELECTOR_SPACE) * (static_cast<int>(mIDs.size()) / 4 + 1) - TILESELECTOR_HEIGHT + 2 * TILESELECTOR_MARGIN));
    }
}

void TileSelector::rmc()
{
    rm(mSelected);
}

void TileSelector::render(sf::RenderWindow &window)
{
    mSurface.clear(sf::Color::Transparent);
    float scrollbarSize = 0.0f;
    float scrollbarOrigin = 0.0f;
    if (mIDs.size() > 4) {
        scrollbarSize = std::min(TILESELECTOR_HEIGHT * TILESELECTOR_HEIGHT / ((static_cast<int>(mIDs.size()) / 4 + 1) * TILE_SIZE), TILESELECTOR_HEIGHT);
        scrollbarOrigin = TILESELECTOR_HEIGHT / ((static_cast<int>(mIDs.size()) / 4 + 1) * TILE_SIZE) * mScroll;
    } else {
        scrollbarSize = TILESELECTOR_HEIGHT;
        scrollbarOrigin = 0;
    }

    sf::Sprite sprite;
    for (unsigned int i=0; i < mIDs.size(); i++) {
        sprite.setTexture(mTiles.get(mIDs[i]));
        sprite.setPosition((i % 4) * (TILE_SIZE + TILESELECTOR_SPACE) + TILESELECTOR_MARGIN, (i / 4) * (TILE_SIZE + TILESELECTOR_SPACE) + TILESELECTOR_MARGIN - mScroll);
        mSurface.draw(sprite);
    }

    sf::RectangleShape selection (sf::Vector2f(TILE_SIZE, TILE_SIZE));
    selection.setPosition((mSelected % 4) * (TILE_SIZE + TILESELECTOR_SPACE) + TILESELECTOR_MARGIN, (mSelected / 4) * (TILE_SIZE + TILESELECTOR_SPACE) + TILESELECTOR_MARGIN  - mScroll);
    selection.setFillColor(sf::Color::Transparent);
    selection.setOutlineColor(sf::Color::Magenta);
    selection.setOutlineThickness(2.0f);
    mSurface.draw(selection);

    sf::RectangleShape scrollBar(sf::Vector2f(5.0f, scrollbarSize));
    scrollBar.setFillColor(sf::Color(100.0f, 100.0f, 100.0f));
    scrollBar.setPosition(HUD_WIDTH - 8.0f, scrollbarOrigin);
    mSurface.draw(scrollBar);

    mSurface.display();
    sf::Sprite sprite2;
    sprite2.setTexture(mSurface.getTexture());
    sprite2.setPosition(0.0f, 600.0f - TILESELECTOR_HEIGHT);
    window.draw(sprite2);
}

void TileSelector::updateEvents(sf::Event event, sf::RenderWindow &window, Level &lvl)
{
    auto mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)) - sf::Vector2f(0.0f, 600.0f - TILESELECTOR_HEIGHT);
    if (event.type == sf::Event::MouseButtonPressed) {
        if (mouse.x > HUD_WIDTH - 10.0f && mouse.x < HUD_WIDTH
        && mouse.y > 0.0f && mouse.y < TILESELECTOR_HEIGHT) {
            mDragging = true;
            mLastDraggingPos = mouse.y;
        } else if (mouse.x > TILESELECTOR_MARGIN && mouse.x < TILESELECTOR_MARGIN + 4 * (TILE_SIZE + TILESELECTOR_SPACE)
                   && mouse.y > 0.0f && mouse.y < TILESELECTOR_HEIGHT) {
            grabTile(mouse.x - TILESELECTOR_MARGIN, mouse.y - TILESELECTOR_MARGIN + mScroll);
            lvl.selectedTileID = mIDs[mSelected];
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        mDragging = false;
    } else if (mouse.x > HUD_WIDTH || mouse.x < 0.0f || mouse.y > TILESELECTOR_HEIGHT || mouse.y < 0.0f) {
        mDragging = false;
    }
}

void TileSelector::update(sf::RenderWindow &window)
{
    dragScrollbar(window);
}

void TileSelector::grabTile(float x, float y)
{
    int n = static_cast<int>(x / (TILE_SIZE + TILESELECTOR_SPACE)) + static_cast<int>(y / (TILE_SIZE + TILESELECTOR_SPACE)) * 4;
    if (n >= 0 && n < mIDs.size())
        mSelected = n;
}


void TileSelector::dragScrollbar(sf::RenderWindow &window)
{
    auto mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)) - sf::Vector2f(0.0f, 600.0f - TILESELECTOR_HEIGHT);
    if (mDragging) {
        mScroll += (mouse.y - mLastDraggingPos) / TILESELECTOR_HEIGHT * ((static_cast<int>(mIDs.size()) / 4 + 1) * TILE_SIZE);
        mLastDraggingPos = mouse.y;
        mScroll = std::max(0.0f, std::min(mScroll, (TILE_SIZE + TILESELECTOR_SPACE) * (static_cast<int>(mIDs.size()) / 4 + 1) - TILESELECTOR_HEIGHT + 2 * TILESELECTOR_MARGIN));
    }
}

int TileSelector::getSelectedTileID()
{
    return mIDs[mSelected];
}
