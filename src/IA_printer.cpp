//
//  IA_printer.cpp
//  Reseau
//
//  Created by Thibault Dardinier on 23/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "IA_printer.hpp"

void printer(sf::Vector2f point)
{
    std::cout << "Point (" << point.x << "," << point.y << ")" << std::endl;
}

void printer(Segment mySegment)
{
    std::cout<<"Segment : ("<<mySegment.p1.x<<","<<mySegment.p1.y<<") à ("<<mySegment.p2.x<<","<<mySegment.p2.y<<")"<<std::endl;
};

void printer(std::list<sf::Vector2f> myList)
{
    std::cout << std::endl << "PRINTER (LIST) : " << myList.size() << std::endl;
    for (auto point:myList)
    {
        std::cout << " / (" << point.x << "," << point.y << ")";
    }
    std::cout << std::endl << std::endl;
}

void printer(std::vector<sf::Vector2f> myList)
{
    std::cout << "PRINTER (VECTOR) : " << myList.size() << std::endl;
    for (auto point:myList)
    {
        std::cout << " / (" << point.x << "," << point.y << ")";
    }
    std::cout << std::endl << std::endl;
}

void printer(std::vector<int> myList)
{
    std::cout << "PRINTER (VECTOR) : " << myList.size() << std::endl;
    for (auto point:myList)
    {
        std::cout << " / " << point;
    }
    std::cout << std::endl << std::endl;
}
