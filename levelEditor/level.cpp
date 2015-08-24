#include "level.hpp"
#include "json.h"
#include <fstream>

Json::Value getPoint(sf::Vector2f point)
{
    Json::Value new_point;
    new_point["x"] = point.x;
    new_point["y"] = point.y;
    return new_point;
}

Json::Value getRect(sf::Vector2f rect[2])
{
    Json::Value new_rect;
    new_rect["x"] = rect[0].x;
    new_rect["y"] = rect[0].y;
    new_rect["w"] = rect[1].x - rect[0].x;
    new_rect["h"] = rect[1].y - rect[0].y;
    return new_rect;
}


void Level::save(std::string texte)
{
    Json::Value tout;
    
    tout["size"] = getPoint(mSize);
    tout["initialPos"] = getPoint(mStart);
    
    // Family
    Json::Value sous_family;
    for (auto ennemi: mEnemies)
    {
        Json::Value un_ennemi;
        un_ennemi["type"] = ennemi.mType;
        un_ennemi["pos"] = getPoint(ennemi.mPos);
        Json::Value reseau;
        for (auto point: ennemi.mPoints)
        {
            reseau.append(getPoint(point));
        }
        un_ennemi["reseau"] = reseau;
        sous_family.append(un_ennemi);
    }
    tout["family"] = sous_family;
    
    // Meubles
    Json::Value sous_meubles;
    Json::Value sous_lampes;
    for (auto meuble: mFurniture)
    {
        Json::Value un_meuble;
        Json::Value sprite;
        sprite["file"] = "furniture/" + meuble.m_nom_fichier;
        un_meuble["sprite"] = sprite;
        if (meuble.mType == "lampe")
        {
            Json::Value une_couleur;
            une_couleur["r"] = 200;
            une_couleur["g"] = 200;
            une_couleur["b"] = 200;
            un_meuble["color"] = une_couleur;
            un_meuble["position"] = getPoint(0.5f * (meuble.mHitbox[0] + meuble.mHitbox[1]));
            un_meuble["r"] = 100;
            un_meuble["angleStart"] = 0;
            un_meuble["angleEnd"] = 6.28;
            un_meuble["isOn"] = true;
            sous_lampes.append(un_meuble);
        }
        else
        {
            un_meuble["type"] = meuble.mType;
            un_meuble["hitBox"] = getRect(meuble.mHitbox);
            un_meuble["interactBox"] = getRect(meuble.mRugHitbox);
            if (meuble.mType == "interrupteur")
            {
                un_meuble["lumiere"] = meuble.mLight;
            }
            else if (meuble.mType == "bruit")
            {
                un_meuble["bruitTemps"] = meuble.mNoiseTime;
            }
            sous_meubles.append(un_meuble);
        }
    }
    tout["meubles"] = sous_meubles;
    tout["lampes"] = sous_lampes;
    
    // tilemap
    
    Json::Value sous_tilemap;
    sous_tilemap["size"] = getPoint(mSize);
    Json::Value sous_sous_tilemap;
    for (int y {0}; y < mTilemap.mSize.y; y++)
    {
        std::string text ("");
        for (int x {0}; x < mTilemap.mSize.x; x++)
        {
            text += (mTilemap.mMap[x][y] == 1) ? "m" : "s";
        }
        sous_sous_tilemap.append(text);
    }
    sous_tilemap["tilemap"].append(sous_sous_tilemap);
    Json::Value titleSet;
    
    Json::Value premier;
    premier["key"] = "m";
    Json::Value sprite_premier;
    sprite_premier["file"] = "wall/wallkakisheet.png";
    premier["sprite"] = sprite_premier;
    sprite_premier["isMur"] = true;
    
    Json::Value second;
    second["key"] = "s";
    Json::Value sprite_second;
    sprite_second["file"] = "flooring/floorwood1.png";
    second["sprite"] = sprite_second;
    sprite_second["isMur"] = false;
    
    titleSet.append(premier);
    titleSet.append(second);
    sous_tilemap["titleSet"] = titleSet;
    
    tout["tilemap"] = sous_tilemap;
    
    
    /*
     "murs":[{"x":0,"y":0,"w":100,"h":800},
     {"x":100,"y":0,"w":800,"h":100},
    */
    
    // Murs
    Json::Value sous_murs;
    for (int x {0}; x < mTilemap.mMap.size(); x++)
    {
        for (int y {0}; y < mTilemap.mMap[x].size(); y++)
        {
            if (mTilemap.mMap[x][y] == 1)
            {
                Json::Value unRect;
                unRect["x"] = x * 100;
                unRect["y"] = y * 100;
                unRect["w"] = 100;
                unRect["h"] = 100;
                sous_murs.append(unRect);
            }
        }
    }
    tout["murs"] = sous_murs;
    

    
    std::ofstream fichier (texte);
    Json::StyledWriter styledWriter;
    fichier << styledWriter.write(tout);
}







Level::Level(TileHolder &tiles, sf::View &view, sf::Font &font) : selectedTileID(0)
    , mView(view)
    , mFont(font)
    , mDragging(false)
    , mDraggingEnemy(false)
    , mTopLayer(0)
    , mTopEnemyLayer(0)
    , mSelectedLayer(0)
    , mSelectedEnemyLayer(0)
    , mHoveredLayer(0)
    , mHoveredEnemyLayer(0)
    , mZoom(0)
    , mState(BASE_STATE_TILES)
    , mSize (1500.0f, 1200.0f)
    , mStart (100.0f, 100.0f)
    , mTilemap (tiles)
{

}

bool Level::loadFromFile(std::string filename)
{
    //2do
}

bool Level::addFurniture(std::string filename)
{
    if (mState == BASE_STATE_FURNITURE) {
        Furniture newFur;
        if (!newFur.loadFromTextureFile(filename, mView.getCenter(), mTopLayer))
            return false;
        mFurniture.push_back(newFur);
        mSelectedLayer = mTopLayer;
        mTopLayer++;
        return true;
    }
}

void Level::addEnemy()
{
    if (mState == BASE_STATE_IA) {
        Enemy newEnemy(mView.getCenter(), mTopEnemyLayer);
        mEnemies.push_back(newEnemy);
        mSelectedEnemyLayer = mTopEnemyLayer;
        mTopEnemyLayer++;
    }
}

void Level::renderInfoBox(sf::RenderWindow &window, std::string str)
{
    sf::Text text;
    text.setString(str);
    text.setFont(mFont);
    text.setColor(sf::Color(0, 0, 0, 200));
    text.setCharacterSize(20);
    auto bounds = text.getLocalBounds();
    text.setOrigin(bounds.width/2, 0.0f);
    text.setPosition(500.0f, 10.0f);

    sf::RectangleShape rect(sf::Vector2f(bounds.width + 10, bounds.height + 10));
    rect.setOrigin(bounds.width/2 + 5, 0.0f);
    rect.setFillColor(sf::Color(255, 190, 200, 200));
    rect.setOutlineColor(sf::Color(0, 0, 0, 200));
    rect.setOutlineThickness(2.0f);
    rect.setPosition(500.0f, 10.0f);

    window.draw(rect);
    window.draw(text);
}

void Level::render(sf::RenderWindow &window)
{
    window.setView(mView);
    mTilemap.render(window, mState == BASE_STATE_TILES);

    for (auto &piece : mFurniture) {
        piece.render(window, mSelectedLayer, mHoveredLayer, mState == BASE_STATE_FURNITURE || mState == HITBOX_STATE || mState == RUG_HITBOX_STATE);
    }
    for (auto &enemy : mEnemies) {
        enemy.render(window, mSelectedEnemyLayer, mHoveredEnemyLayer, mState == BASE_STATE_IA || mState == POINTS_STATE);
    }

    window.setView(window.getDefaultView());
    if (mState == POINTS_STATE) {
        renderInfoBox(window, "You are editing points.\nClick to add/suppress points, and click on \"Edit points\" to quit this mode");
    } else if (mState == HITBOX_STATE || mState == RUG_HITBOX_STATE) {
        renderInfoBox(window, "You are editing hitbox.\nClick to add a first corner, then click to add a second corner");
    }
}

void Level::getHoveredLayer(sf::RenderWindow &window)
{
    int result = -1;
    for (auto &furniture : mFurniture) {
        if (furniture.hovered(window))
            result = furniture.getLayer();
    }
    mHoveredLayer = result;
    result = -1;
    for (auto &enemy : mEnemies) {
        if (enemy.hovered(window))
            result = enemy.getLayer();
    }
    mHoveredEnemyLayer = result;
}

void Level::updateEvents(sf::Event event, sf::RenderWindow &window)
{
    window.setView(mView);
    if (sf::Mouse::getPosition(window).x > 200) {
        if (mState == BASE_STATE_FURNITURE) {
            getHoveredLayer(window);
            if (event.type == sf::Event::MouseButtonPressed) {
                mSelectedLayer = mHoveredLayer;
                if (mHoveredLayer >= 0)
                    mDragging = true;
                    mDraggingStart = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            } else if (event.type == sf::Event::MouseButtonReleased || event.type == sf::Event::MouseLeft) {
                mDragging = false;
            }
        } else if (mState == BASE_STATE_IA) {
            getHoveredLayer(window);
            if (event.type == sf::Event::MouseButtonPressed) {
                mSelectedEnemyLayer = mHoveredEnemyLayer;
                if (mHoveredEnemyLayer >= 0)
                    mDraggingEnemy = true;
                    mDraggingStart = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            } else if (event.type == sf::Event::MouseButtonReleased || event.type == sf::Event::MouseLeft) {
                mDraggingEnemy = false;
            }
        } else if (mState == POINTS_STATE) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (mSelectedEnemyLayer >= 0) {
                    mEnemies[mSelectedEnemyLayer].addPoint(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                }
            }
        } else if (mState == HITBOX_STATE && mSelectedLayer >= 0) {
            if (mHitboxCorner == 0 && event.type == sf::Event::MouseButtonPressed) {
                mFurniture[mSelectedLayer].modifyHitbox(0, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                mHitboxCorner++;
            } else if (mHitboxCorner == 1 && event.type == sf::Event::MouseButtonPressed) {
                mFurniture[mSelectedLayer].modifyHitbox(1, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                setState(BASE_STATE_FURNITURE);
            } else if (mHitboxCorner == 1 && event.type == sf::Event::MouseMoved) {
                mFurniture[mSelectedLayer].modifyHitbox(1, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            }
        } else if (mState == RUG_HITBOX_STATE && mSelectedLayer >= 0) {
            if (mHitboxCorner == 0 && event.type == sf::Event::MouseButtonPressed) {
                mFurniture[mSelectedLayer].modifyRugHitbox(0, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                mHitboxCorner++;
            } else if (mHitboxCorner == 1 && event.type == sf::Event::MouseButtonPressed) {
                mFurniture[mSelectedLayer].modifyRugHitbox(1, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                setState(BASE_STATE_FURNITURE);
            } else if (mHitboxCorner == 1 && event.type == sf::Event::MouseMoved) {
                mFurniture[mSelectedLayer].modifyRugHitbox(1, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            }
        }
    }
    window.setView(window.getDefaultView());
}

void Level::update(sf::RenderWindow &window)
{
    window.setView(mView);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        mView.move(0.0f, -2.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        mView.move(0.0f, 2.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        mView.move(-2.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        mView.move(2.0f, 0.0f);

    if (mState == BASE_STATE_IA || mState == BASE_STATE_FURNITURE)
        drag(window);
    else if (mState == BASE_STATE_TILES)
        mTilemap.update(window, selectedTileID);
    window.setView(window.getDefaultView());
}

void Level::drag(sf::RenderWindow &window)
{
    if (mDragging) {
        for (auto &piece : mFurniture) {
            if (piece.getLayer() == mSelectedLayer)
                piece.drag(window.mapPixelToCoords(sf::Mouse::getPosition(window)) - mDraggingStart);
        }
        mDraggingStart = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    }

    if (mDraggingEnemy) {
        for (auto &enemy : mEnemies) {
            if (enemy.getLayer() == mSelectedEnemyLayer)
                enemy.drag(window.mapPixelToCoords(sf::Mouse::getPosition(window)) - mDraggingStart);
        }
        mDraggingStart = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    }
}

void Level::zoom(int dir)
{
    mZoom += dir;
    if (mZoom < -3)
        mZoom = -3;
    if (mZoom > 3)
        mZoom = 3;
    mView.setSize((4 - mZoom) * 150.0f, (4 - mZoom) * 150.0f);
}

void Level::setState(int state)
{
    if (state == BASE_STATE_FURNITURE || state == BASE_STATE_IA || state == BASE_STATE_TILES)
    {
        if (mState == BASE_STATE_FURNITURE || mState == BASE_STATE_IA || mState == BASE_STATE_TILES) {
            mSelectedLayer = -1;
            mSelectedEnemyLayer = -1;
        }
        mState = state;
    } else if (state == POINTS_STATE) {
        if (mSelectedEnemyLayer >= 0 && mState == BASE_STATE_IA)
            mState = state;
        else
            mState = BASE_STATE_IA;
    } else if (state == HITBOX_STATE || state == RUG_HITBOX_STATE) {
        if (mSelectedLayer >= 0 && mState == BASE_STATE_FURNITURE) {
            mState = state;
            mHitboxCorner = 0;
        }
    }
}

void Level::editFurnitureProperty(int property, std::string val)
{
    if (mSelectedLayer >= 0) {
        mFurniture[mSelectedLayer].editProperty(property, val);
    }
}

void Level::suppressFurniture()
{
    if (mSelectedLayer >= 0 && mState == BASE_STATE_FURNITURE) {
        mFurniture.erase(mFurniture.begin() + mSelectedLayer);
        mSelectedLayer = -1;
        mTopLayer--;
    }
}

void Level::suppressEnemy()
{
    if (mSelectedEnemyLayer >= 0 && mState == BASE_STATE_IA) {
        mEnemies.erase(mEnemies.begin() + mSelectedEnemyLayer);
        mSelectedEnemyLayer = -1;
        mTopEnemyLayer--;
    }
}
