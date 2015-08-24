//
//  IA_familymember.cpp
//  Reseau
//
//  Created by Thibault Dardinier on 24/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "IA_familymember.hpp"

FamilyMember::FamilyMember(sf::Vector2f taille, std::vector<sf::FloatRect> obstacles, std::vector<sf::Vector2f> reseau, IA_Type type, sf::Vector2f pos):m_taille(taille),m_obstacles(obstacles), m_reseau(reseau), m_type(type), m_chemin_global(generateRonde(sf::FloatRect (0, 0, taille.x, taille.y), obstacles, reseau, m_pas))
{
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

void FamilyMember::agir()
{
    if (m_mode_actuel == LUMIERE)
    {
        if (m_id_point_actuel >= m_chemin_special.size())
        {
            interagir(); // On a trouvé l'interrupteur, en théorie
            retour(); // On revient dans la boucle
        }
        else
        {
            m_id_point_actuel++;
            m_point_cible = m_chemin_special[m_id_point_actuel];
            allerAuPoint(m_point_cible);
        }
    }
    else if (m_mode_actuel == BRUIT)
    {
        if (m_id_point_actuel >= m_chemin_special.size())
        {
            rotater(); // On a trouvé la source du bruit
            retour(); // On revient dans la boucle
        }
        else
        {
            m_id_point_actuel++;
            m_point_cible = m_chemin_special[m_id_point_actuel];
            allerAuPoint(m_point_cible);
        }
    }
    else if (m_mode_actuel == RETOUR)
    {
        if (m_id_point_actuel >= m_chemin_special.size())
        {
            rotater(); // On a trouvé la source du bruit
            retour(); // On revient dans la boucle
        }
        else
        {
            m_id_point_actuel++;
            m_point_cible = m_chemin_special[m_id_point_actuel];
            allerAuPoint(m_point_cible);
        }
    }
    else if (m_mode_actuel == NORMAL)
    {
        
    }
}