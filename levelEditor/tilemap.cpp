#include "tilemap.hpp"

TileHolder::TileHolder() : mFree(0)
{

}

bool TileHolder::add(std::string filename, int id)
{
    sf::Texture tex;
    if (!tex.loadFromFile(filename))
        return false;
    if(id >= mFree)
        mFree = id + 1;
    mTiles.insert(std::pair<int, sf::Texture>(id, tex));
    return true;
}

sf::Texture& TileHolder::get(int id)
{
    return mTiles[id];
}

void TileHolder::rm(int id)
{
    mTiles.erase(id);
}

int TileHolder::freeID()
{
    return mFree;
}

Tilemap::Tilemap(TileHolder &tiles) : mSize(30, 20)
    , mTiles(tiles)
{
    std::vector<int> column (20, 0);
    mMap = std::vector<std::vector<int>> (30, column);
}

void Tilemap::render(sf::RenderWindow &window, bool tileTab)
{
    sf::Sprite sprite;
    for (unsigned int x = 0; x < mSize.x; x++) {
        for (unsigned int y = 0; y < mSize.y; y++) {
            sprite.setTexture(mTiles.get(mMap[x][y]));
            sprite.setPosition(sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE));
            window.draw(sprite);
        }
    }
    if (tileTab) {
        sf::RectangleShape selection (sf::Vector2f(TILE_SIZE, TILE_SIZE));
        selection.setFillColor(sf::Color::Transparent);
        selection.setOutlineColor(sf::Color::Magenta);
        selection.setOutlineThickness(2.0f);
        sf::Vector2f mouse = (window.mapPixelToCoords(sf::Mouse::getPosition(window))) / TILE_SIZE;
        selection.setPosition(sf::Vector2f(floor(mouse.x) * TILE_SIZE, floor(mouse.y) * TILE_SIZE));
        window.draw(selection);
    }
}

void Tilemap::update(sf::RenderWindow &window, int selectedTileID)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)) / TILE_SIZE;
        sf::Vector2i tile (static_cast<int>(mouse.x), static_cast<int>(mouse.y));
        if (tile.x >= 0 && tile.x < mSize.x && tile.y >= 0 && tile.y < mSize.y)
            mMap[tile.x][tile.y] = selectedTileID;
    }
}
