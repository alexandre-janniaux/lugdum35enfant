#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <sstream>

class Furniture
{
public :
    bool loadFromTextureFile(std::string filename, sf::Vector2f pos, int layer);
    void render(sf::RenderWindow &window, int selectedLayer, int hoveredLayer, bool furnitureTab);
    void renderHitbox(sf::RenderWindow &window);
    void renderRugHitbox(sf::RenderWindow &window);
    void modifyHitbox(int corner, sf::Vector2f pos);
    void modifyRugHitbox(int corner, sf::Vector2f pos);
    bool hovered(sf::RenderWindow &window);
    int getLayer();
    void drag(sf::Vector2f mv);
    void editProperty(int property, std::string value);

private :
    sf::Texture mTex;
    std::string mType;
    sf::Vector2f mPos;
    sf::Vector2f mHitbox[2];
    sf::Vector2f mRugHitbox[2];
    float mNoiseTime;
    int mLight;
    int mLayer;
};

class Enemy
{
public :
    Enemy(sf::Vector2f pos, int layer);
    void render(sf::RenderWindow &window, int selectedLayer, int hoveredLayer, bool IATab);
    void renderPoints(sf::RenderWindow &window);
    bool hovered(sf::RenderWindow &woindow);
    int getLayer();
    void drag(sf::Vector2f mv);
    void addPoint(sf::Vector2f point);

private :
    std::vector<sf::Vector2f> mPoints;
    std::string mType;
    sf::Vector2f mPos;
    int mLayer;
};
