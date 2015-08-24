//
//  IA_astar_grille.cpp
//  Reseau
//
//  Created by Thibault Dardinier on 23/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "IA_astar_grille.hpp"

int whereIsPointInNoeuds(sf::Vector2f point, std::vector<Noeud> table)
{
    int k {0};
    bool continuer {true};
    while (continuer && k < table.size())
    {
        if (point == table[k].pos)
        {
            continuer = false;
        }
        k++;
    }
    if (continuer)
    {
        return -1;
    }
    else
    {
        return k - 1;
    }
}

std::vector<sf::Vector2f> AStarGrille(sf::Vector2f depart, sf::Vector2f arrivee, std::vector<sf::FloatRect> obstacles, sf::Vector2f taille, float pas)
{
    std::vector<int> closedList;
    std::list<int> openList;
    std::vector<Noeud> noeuds;

    // GROSSE DIFF : On créé les noeuds au fur et à mesure

    noeuds.push_back(Noeud (depart, -1, 0));
    // noeuds.push_back(Noeud (arrivee, -1, std::numeric_limits<float>::infinity()));

    openList.push_back(0);
    int id_min = -1;
    do
    {
        // On chope le meilleur noeud
        id_min = openList.front();
        float distance_heuri_min = std::numeric_limits<float>::infinity();
        for (int i: openList)
        {
            float distance_heuri = noeuds[i].distance + distance_entre(noeuds[i].pos, arrivee);
            if (distance_heuri < distance_heuri_min)
            {
                distance_heuri_min = distance_heuri;
                id_min = i;
            }
        }
        // On l'enlève
        openList.remove(id_min);
        closedList.push_back(id_min);
        
        
        // À modifier
        int taille_actuelle = noeuds.size();
        std::vector<Noeud> les_voisins {};
        Noeud myNode = noeuds[id_min];

        // À 1 case
        les_voisins.push_back(Noeud(myNode.pos + sf::Vector2f (pas, 0.), id_min, noeuds[id_min].distance + pas));
        les_voisins.push_back(Noeud(myNode.pos + sf::Vector2f (0., pas), id_min, noeuds[id_min].distance + pas));
        les_voisins.push_back(Noeud(myNode.pos + sf::Vector2f (-pas, 0.), id_min, noeuds[id_min].distance + pas));
        les_voisins.push_back(Noeud(myNode.pos + sf::Vector2f (0., -pas), id_min, noeuds[id_min].distance + pas));

        // En diago
        float r2 = 1.41421356237 * pas;
        les_voisins.push_back(Noeud(myNode.pos + sf::Vector2f (pas, pas), id_min, noeuds[id_min].distance + r2));
        les_voisins.push_back(Noeud(myNode.pos + sf::Vector2f (pas, -pas), id_min, noeuds[id_min].distance + r2));
        les_voisins.push_back(Noeud(myNode.pos + sf::Vector2f (-pas, pas), id_min, noeuds[id_min].distance + r2));
        les_voisins.push_back(Noeud(myNode.pos + sf::Vector2f (-pas, -pas), id_min, noeuds[id_min].distance + r2));
        
        for (Noeud x: les_voisins)
        {
            if (x.pos.x >= 0 && x.pos.x <= taille.x && x.pos.y >= 0 && x.pos.y <= taille.y && dansAucunObstacle(x.pos, obstacles))
            {
                int id = whereIsPointInNoeuds(x.pos, noeuds);
                if (id == -1)
                {
                    // Nouveau noeud
                    noeuds.push_back(x);
                    openList.push_back(taille_actuelle);
                    taille_actuelle++;
                }
                else
                {
                    if (!in<int>(id, closedList))
                    {
                        // On actualise
                        if (x.distance < noeuds[id].distance)
                        {
                            noeuds[id].distance = x.distance;
                            noeuds[id].parent = id_min;
                        }
                    }
                }
            }
        }
    } while (noeuds[id_min].pos != arrivee);

    std::vector<sf::Vector2f> chemin {arrivee};
    int actuel {id_min};
    while (noeuds[actuel].parent != -1)
    {
        actuel = noeuds[actuel].parent;
        chemin.push_back(noeuds[actuel].pos);
    }
    std::vector<sf::Vector2f> vrai_chemin (chemin.rbegin(), chemin.rend());
    return vrai_chemin;
}