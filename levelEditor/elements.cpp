#include "elements.hpp"

bool Furniture::loadFromTextureFile(std::string filename, sf::Vector2f pos, int layer)
{
    if (!mTex.loadFromFile(filename))
        return false;

    mType = "unknown";
    mLight = 0;
    mNoiseTime = 0.0f;
    mPos = pos;
    mHitbox[0] = sf::Vector2f(pos.x, pos.y);
    mHitbox[1] = sf::Vector2f(pos.x + mTex.getSize().x, pos.y + mTex.getSize().y);
    mRugHitbox[0] = sf::Vector2f(pos.x, pos.y);
    mRugHitbox[1] = sf::Vector2f(pos.x, pos.y);
    mLayer = layer;
    return true;
}

void Furniture::render(sf::RenderWindow &window, int selectedLayer, int hoveredLayer, bool furnitureTab)
{
    sf::Sprite sprite;
    sprite.setTexture(mTex);
    sprite.setPosition(mPos);
    if (furnitureTab) {
        if (selectedLayer == mLayer) {
            sprite.setColor(sf::Color (255, 180, 200));
            window.draw(sprite);
            renderRugHitbox(window);
            renderHitbox(window);
        }
        else if (hoveredLayer == mLayer) {
            sprite.setColor(sf::Color (255, 210, 230));
            window.draw(sprite);
        } else {
            window.draw(sprite);
        }
    } else {
        sprite.setColor(sf::Color(255, 255, 255, 100));
        window.draw(sprite);
    }
}

void Furniture::renderHitbox(sf::RenderWindow &window)
{
    sf::RectangleShape hitbox(sf::Vector2f(std::abs(mHitbox[0].x - mHitbox[1].x), std::abs(mHitbox[0].y - mHitbox[1].y)));
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Magenta);
    hitbox.setOutlineThickness(5.0f);
    hitbox.setPosition(std::min(mHitbox[0].x, mHitbox[1].x), std::min(mHitbox[0].y, mHitbox[1].y));
    window.draw(hitbox);
}

void Furniture::renderRugHitbox(sf::RenderWindow &window)
{
    if (mRugHitbox[0].x != mRugHitbox[0].y)
    {
        sf::RectangleShape hitbox(sf::Vector2f(std::abs(mRugHitbox[0].x - mRugHitbox[1].x), std::abs(mRugHitbox[0].y - mRugHitbox[1].y)));
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Green);
        hitbox.setOutlineThickness(5.0f);
        hitbox.setPosition(std::min(mRugHitbox[0].x, mRugHitbox[1].x), std::min(mRugHitbox[0].y, mRugHitbox[1].y));
        window.draw(hitbox);
    }
}

int Furniture::getLayer()
{
    return mLayer;
}

bool Furniture::hovered(sf::RenderWindow &window)
{
    auto mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return mPos.x <= mouse.x && mouse.x <= mPos.x + mTex.getSize().x
        && mPos.y <= mouse.y && mouse.y <= mPos.y + mTex.getSize().y;
}

void Furniture::drag(sf::Vector2f mv)
{
    mPos += mv;
    mHitbox[0] += mv;
    mHitbox[1] += mv;
    mRugHitbox[0] += mv;
    mRugHitbox[1] += mv;
}

void Furniture::modifyHitbox(int corner, sf::Vector2f pos)
{
    mHitbox[corner] = pos;
    if (corner == 0)
        modifyHitbox(1, pos);
}

void Furniture::modifyRugHitbox(int corner, sf::Vector2f pos)
{
    mRugHitbox[corner] = pos;
    if (corner == 0)
        modifyRugHitbox(1, pos);
}

void Furniture::editProperty(int property, std::string value)
{
    if (property == 0)
        mType = value;
    else if (property == 1) {
        std::stringstream ss;
        ss << value;
        ss >> mNoiseTime;
    } else if (property == 2) {
        std::stringstream ss;
        ss << value;
        ss >> mLight;
    }
}

Enemy::Enemy(sf::Vector2f pos, int layer) : mType("unknown")
    , mPos(pos)
    , mLayer(layer)
{

}

void Enemy::render(sf::RenderWindow &window, int selectedLayer, int hoveredLayer, bool IATab)
{
    sf::CircleShape enemy (10);
    enemy.setOrigin(10.0f, 10.0f);
    enemy.setOutlineThickness(2.0f);
    enemy.setPosition(mPos);

    if (IATab) {
        enemy.setOutlineColor(sf::Color::White);
        if (mLayer == selectedLayer) {
            enemy.setFillColor(sf::Color::Black);
            renderPoints(window);
        }
        else if (mLayer == hoveredLayer)
            enemy.setFillColor(sf::Color(100, 100, 100));
        else
            enemy.setFillColor(sf::Color(150, 150, 150));
    } else {
        enemy.setOutlineColor(sf::Color(255, 255, 255, 150));
        enemy.setFillColor(sf::Color(150, 150, 150, 150));
    }
    window.draw(enemy);
}

void Enemy::renderPoints(sf::RenderWindow &window)
{
    sf::Vertex sline[2];
    for (auto &point : mPoints) {
        sline[0] = sf::Vertex(mPos);
        sline[0].color = sf::Color::Magenta;
        sline[1] = sf::Vertex(point);
        sline[1].color = sf::Color::Magenta;
        window.draw(sline, 2, sf::Lines);
        sf::CircleShape spoint (10);
        spoint.setOrigin(10.0f, 10.0f);
        spoint.setPosition(point);
        spoint.setFillColor(sf::Color::Magenta);
        window.draw(spoint);
    }
}

bool Enemy::hovered(sf::RenderWindow &window)
{
    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return (mouse.x - mPos.x)*(mouse.x - mPos.x) + (mouse.y - mPos.y)*(mouse.y - mPos.y) <= 144.0f;
}

int Enemy::getLayer()
{
    return mLayer;;
}

void Enemy::drag(sf::Vector2f mv)
{
    mPos += mv;
}

void Enemy::addPoint(sf::Vector2f point)
{
    bool suppressing = false;
    for (unsigned int i = 0; i < mPoints.size(); i++) {
        if ((point.x - mPoints[i].x)*(point.x - mPoints[i].x) + (point.y - mPoints[i].y)*(point.y - mPoints[i].y) <= 100.0f) {
            suppressing = true;
            mPoints.erase(mPoints.begin() + i);
        }
    }
    if (!suppressing) {
        mPoints.push_back(point);
    }
}

