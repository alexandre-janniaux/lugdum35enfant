//
//  IA_trouver_reseau.cpp
//  Reseau
//
//  Created by Thibault Dardinier on 23/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "IA_trouver_reseau.hpp"

std::vector<sf::Vector2f> trouverReseau(sf::FloatRect carte, std::vector<sf::FloatRect> obstacles, int pas)
{    
    // On se déplace sur les cases (5,5)
    int init = 0;
    
    std::vector<sf::Vector2f> reseau;
    std::list<sf::Vector2f> pas_couvert = {};
    std::list<sf::Vector2f> couvert_pas_reseau = {};

    // Toute la carte
    for (int x {init}; x < carte.width; x += pas)
    {
        for (int y {init}; y < carte.height; y += pas)
        {
            pas_couvert.push_back(sf::Vector2f (x, y));
        }
    }
    
    pas_couvert.remove_if([obstacles](sf::Vector2f point){return !dansAucunObstacle(point, obstacles);});
    
    // On vire les obstacles
    /*for (sf::FloatRect rect: obstacles)
    {
        pas_couvert.remove_if([rect](sf::Vector2f point){ return contientPlus(rect, point);}); // remove tous les obstacles
    }
    */
    
    bool debut {true};
    
    
    // Tant que tout pas couvert => on en ajoute un nouveau
    while ((!pas_couvert.empty() || debut) && (reseau.size() < 20))
    {
        std::list<sf::Vector2f>* monPointeur = &couvert_pas_reseau;
        if (debut)
        {
            monPointeur = &pas_couvert;
            debut = false;
        }
        // On sélectionne le meilleur
        
        int nb_new_max = 0;
        int distance_min_carre = -1;
        sf::Vector2f point_max = monPointeur->front();
        for (sf::Vector2f point_candidat: *monPointeur)
        {
            int nb_new = 0;
            for (auto point_pas_couvert: pas_couvert)
            {
                if (isVisible(point_candidat, point_pas_couvert, obstacles))
                {
                    nb_new++;
                }
            }
            if (nb_new > nb_new_max)
            {
                nb_new_max = nb_new;
                point_max = point_candidat;
                int d = std::numeric_limits<int>::max();
                for (auto point: reseau)
                {
                    if (isVisible(point, point_candidat, obstacles))
                    {
                        sf::Vector2f diff = point - point_candidat;
                        int norme = diff.x * diff.x + diff.y * diff.y;
                        d = std::min(d, norme);
                    }
                }
                distance_min_carre = d;
            }
            else if (nb_new == nb_new_max)
            {
                int d = std::numeric_limits<int>::max();
                for (auto point: reseau)
                {
                    if (isVisible(point, point_candidat, obstacles) && point != point_candidat)
                    {
                        sf::Vector2f diff = point - point_candidat;
                        int norme = diff.x * diff.x + diff.y * diff.y;
                        if (norme != 0)
                        {
                            d = std::min(d, norme);
                        }
                    }
                }
                if (d > distance_min_carre)
                {
                    nb_new_max = nb_new;
                    point_max = point_candidat;
                    distance_min_carre = d;
                }
            }
        }
        
        // Le meilleur a été sélectionné
        reseau.push_back(point_max);
        monPointeur->remove(point_max);
        
        // On ajoute les couverts
        for (sf::Vector2f point: pas_couvert)
        {
            if (isVisible(point_max, point, obstacles))
            {
                //pas_couvert.remove(point);
                couvert_pas_reseau.push_back(point);
            }
        }
        
        // On enlève les couverts
        pas_couvert.remove_if([obstacles, point_max](sf::Vector2f point){ return isVisible(point_max, point, obstacles);});
    }
    
    std::cout << "FINI ?";
    
    
    //pas_couvert.remove_if([](int n){ return n > 10; }); // remove all elements greater than 10
    //pas_couvert.remove(3);
    return reseau;
};
