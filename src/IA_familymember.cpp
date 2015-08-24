//
//  IA_familymember.cpp
//  Reseau
//
//  Created by Thibault Dardinier on 24/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "IA_familymember.hpp"

std::vector<sf::Vector2f> FamilyMember::normalise_reseau(std::vector<sf::Vector2f> reseau)
{
    std::vector<sf::Vector2f> new_reseau {};
    for (auto point: reseau)
    {
        new_reseau.push_back(normaliser(point));
    }
    return new_reseau;
}

std::vector<sf::Vector2f> FamilyMember::creer_reseau_meuble(std::pair<sf::Vector2f,sf::Vector2f> cachettes, std::vector<sf::FloatRect> obstacles)
{
    std::vector<sf::Vector2f> reseau {};
    
    
    
    // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
    // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
    // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
    
    
    
    return reseau;
}

FamilyMember::FamilyMember(sf::Vector2f taille, std::vector<sf::FloatRect> obstacles, std::vector<sf::Vector2f> reseau, IA_Type type, sf::Vector2f pos, std::pair<sf::Vector2f, sf::Vector2f> cachettes, std::pair<sf::Vector2f, float> lampes, std::pair<sf::Vector2f, sf::Vector2f> interrupteurs)
{
    // CONSTANTES
    m_taille = taille;
    m_obstacles = obstacles;
    if (type == ZONE)
    {
        m_reseau = normalise_reseau(reseau);
    }
    else if (type == ZONE)
    {
        m_reseau = creer_reseau_meuble(cachettes, obstacles);
    }
    m_chemin_global = generateRonde(sf::FloatRect (0, 0, taille.x, taille.y), obstacles, reseau, m_pas);
    m_type = type;
    m_lampes = lampes;
    m_interrupteurs = interrupteurs;

    m_vit = sf::Vector2f (0, 0);
    m_pos = pos;
    m_is_enlighted = true;

    m_point_cible = pos;    
    retour();
}


void FamilyMember::update(sf::Vector2f pos, bool lumiere)
{
    m_pos = pos;
    m_is_enlighted = lumiere;
    sf::Vector2f vecteur = m_pos - m_point_cible;
    if (vecteur.x * m_vit.x + vecteur.y * m_vit.y >= 0)
    {
        agir();
    }
}

void FamilyMember::allerAuPoint(sf::Vector2f pos)
{
    if (distance_entre(pos, m_pos) > m_delta)
    {
        sf::Vector2f vitesse = pos - m_pos;
        vitesse = vitesse / (vitesse.x * vitesse.x + vitesse.y * vitesse.y); // Vitesse normée
        vitesse *= m_norme_vitesse;
        setVitesse(vitesse);
        m_point_cible = pos;
    }
}

// Adapte au pas
sf::Vector2f FamilyMember::normaliser(sf::Vector2f ancien_point)
{
    int ent_x = ancien_point.x / m_pas;
    int ent_y = ancien_point.y / m_pas;
    return sf::Vector2f (ent_x * m_pas, ent_y * m_pas);
}

void FamilyMember::lancerTrajetSpecial(sf::Vector2f point, IA_Mode mode)
{
    m_mode_actuel = mode;
    m_cible = point;
    m_id_point_actuel = 0;
    sf::Vector2f depart = normaliser(m_pos);
    sf::Vector2f arrivee = normaliser(point);
    m_chemin_special = AStarGrille(depart, arrivee, m_obstacles, m_taille, m_pas);
}

void FamilyMember::retour()
{
    sf::Vector2f best_point = m_reseau[0];
    for (auto point: m_reseau)
    {
        if (distance_entre(m_pos, point) < distance_entre(m_pos, best_point))
        {
            best_point = point;
        }
    }
    lancerTrajetSpecial(best_point, RETOUR);
}

void FamilyMember::bruitEntendu(sf::Vector2f pos)
{
    if (distance_entre(m_pos, pos) > m_delta)
    {
        lancerTrajetSpecial(pos, BRUIT);
    }
    else
    {
        rotater();
    }
}

void FamilyMember::lumiereEteinte()
{
    
    
    
    // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
    // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
    // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
    
    
    
}

void FamilyMember::rentrerDansLeRang()
{
    m_mode_actuel = NORMAL;
    int id_best {1};
    for (int k {1}; k < m_chemin_special.size(); k++)
    {
        if (distance_entre(m_pos, m_chemin_special[k]) < distance_entre(m_pos, m_chemin_special[id_best]))
        {
            id_best = k;
        }
    }
    m_id_point_actuel = id_best - 1;
    allerAuPoint(m_chemin_special[id_best]);
}

void FamilyMember::agir()
{
    if (m_mode_actuel != NORMAL)
    {
        if (m_id_point_actuel < m_chemin_special.size())
        {
            m_id_point_actuel++;
            allerAuPoint(m_chemin_special[m_id_point_actuel]);
        }
        else
        {
            if (m_mode_actuel == LUMIERE)
            {
                interagir(); // On a trouvé l'interrupteur, en théorie
                retour(); // On revient dans la boucle
            }
            else if (m_mode_actuel == BRUIT)
            {
                rotater(); // On a trouvé la source du bruit
                retour(); // On revient dans la boucle
            }
            else if (m_mode_actuel == RETOUR)
            {
                rentrerDansLeRang();
            }
        }
    }
    else
    {
        // On est sur m_point_cible
        
        // Erreur ?
        if (distance_entre(m_pos, m_point_cible) > m_delta)
        {
            std::cout << "ERREUR : mauvaise réalité" << std::endl;
        }
        
        if (in(m_point_cible, m_reseau))
        {
            if (m_type == ZONE)
            {
                rotater();
            }
            else if (m_type == MEUBLE)
            {
                interagir();
            }
            int id {0};
            for (int k {0}; k < m_reseau.size(); k++)
            {
                if (m_point_cible == m_reseau[k])
                {
                    id = k;
                }
            }
            if (id == m_reseau.size() - 1)
            {
                id = 0;
            }
            else
            {
                id++;
            }
            m_point_cible = m_reseau[id];
        }
        else
        {
            // Continuer !
            
            
            // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
            // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
            // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
            
            
        }
    }
}