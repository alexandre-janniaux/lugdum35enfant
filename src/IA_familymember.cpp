//
//  IA_familymember.cpp
//  Reseau
//
//  Created by Thibault Dardinier on 24/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "IA_familymember.hpp"

void log(std::string texte)
{
    std::cout << std::endl;
    std::cout << "IA FamilyMember : " << texte << std::endl;
}

sf::Vector2f FamilyMember::point_centre(sf::FloatRect hb_int, sf::FloatRect hb_ext, std::vector<sf::FloatRect> obstacles)
{
    log("Point_centre");
    std::vector<sf::Vector2f> points_candidats;
    sf::Vector2f A (hb_ext.left + (hb_ext.width / 2), hb_ext.top);
    sf::Vector2f D (hb_ext.left, hb_ext.top + hb_ext.height / 2);
    sf::Vector2f C (hb_ext.left + (hb_ext.width / 2), hb_ext.top + hb_ext.height);
    sf::Vector2f B (hb_ext.left + hb_ext.width, hb_ext.top + (hb_ext.height / 2));
    
    sf::Vector2f a (hb_int.left + (hb_int.width / 2), hb_int.top);
    sf::Vector2f d (hb_int.left, hb_int.top + hb_int.height / 2);
    sf::Vector2f c (hb_int.left + (hb_int.width / 2), hb_int.top + hb_int.height);
    sf::Vector2f b (hb_int.left + hb_int.width, hb_int.top + (hb_int.height / 2));
    
    points_candidats.push_back(0.5f * (a + A));
    points_candidats.push_back(0.5f * (b + B));
    points_candidats.push_back(0.5f * (c + C));
    points_candidats.push_back(0.5f * (d + D));
    
    for (auto point: points_candidats)
    {
        auto new_point = normaliser(point);
        if (dansAucunObstacle(new_point, obstacles) && new_point.x >= 0 && new_point.x <= m_taille.x && new_point.y >= 0 && new_point.y <= m_taille.y)
        {
            return new_point;
        };
    }
    std::cout << "ERREUR DANS POINT CENTRE FAMILY MEMBER";
    log("Point_centre : fin");
    return sf::Vector2f (-1, -1);
}

std::vector<sf::Vector2f> FamilyMember::normalise_reseau(std::vector<sf::Vector2f> reseau)
{
    log("Normalise_reseau");
    std::vector<sf::Vector2f> new_reseau {};
    for (auto point: reseau)
    {
        new_reseau.push_back(normaliser(point));
    }
    log("Normalise_reseau : fin");
    return new_reseau;
}

std::vector<sf::Vector2f> FamilyMember::creer_reseau_meuble(std::vector<std::pair<sf::FloatRect,sf::FloatRect>> cachettes, std::vector<sf::FloatRect> obstacles)
{
    log("Creer_reseau_meuble");
    std::vector<sf::Vector2f> reseau {};
    for (auto meuble: cachettes)
    {
        auto point = point_centre(meuble.first, meuble.second, obstacles);
        printer(point);
        if (point != sf::Vector2f(-1, -1))
        {
            reseau.push_back(point);
        }
    }
    log("Creer_reseau_meuble : fin");
    return normalise_reseau(reseau);
}

FamilyMember::FamilyMember(sf::Vector2f taille, std::vector<sf::FloatRect> &obstacles, std::vector<sf::Vector2f> reseau, IA_Type type, sf::Vector2f pos, std::vector<std::pair<sf::FloatRect, sf::FloatRect>> &cachettes, std::vector<std::pair<sf::Vector2f, float>> &lampes, std::vector<std::pair<sf::FloatRect, sf::FloatRect>> &interrupteurs):
m_interrupteurs(interrupteurs),
m_obstacles(obstacles),
m_lampes(lampes)
{
    log("Creation");
    std::cout << "Taille de cachettes" << cachettes.size();
    // CONSTANTES
    m_taille = taille;
    if (type == ZONE)
    {
        m_reseau = normalise_reseau(reseau);
    }
    else if (type == MEUBLE)
    {
        std::cout << "Bef";
        m_reseau = creer_reseau_meuble(cachettes, obstacles);
        printer(m_reseau);
        std::cout << "After";
    }
    m_chemin_global = generateRonde(sf::FloatRect (0, 0, taille.x, taille.y), obstacles, m_reseau, m_pas);
    m_type = type;

    m_vit = sf::Vector2f (0, 0);
    m_pos = pos;
    m_is_enlighted = true;

    m_point_cible = pos;    
    retour();
    log("Creation fin");
}


void FamilyMember::update(sf::Vector2f pos, bool lumiere)
{
    log("Update");
    m_pos = pos;
    m_is_enlighted = lumiere;
    sf::Vector2f vecteur = m_pos - m_point_cible;
    if (vecteur.x * m_vit.x + vecteur.y * m_vit.y >= 0)
    {
        log("OK");
        agir();
    }
    log("Update : fin");
}

void FamilyMember::allerAuPoint(sf::Vector2f pos)
{
    log("Aller au point");
    
    
     if (distance_entre(pos, m_pos) > m_delta)
    {
        sf::Vector2f vitesse = pos - m_pos;
        vitesse = vitesse / (vitesse.x * vitesse.x + vitesse.y * vitesse.y); // Vitesse normée
        vitesse *= m_norme_vitesse;
        setVitesse(vitesse);
        m_point_cible = pos;
    }

    /*
    m_pos = pos;
    m_point_cible = pos;
    printer(pos);
    */
    log("Aller au point : fin");
}

// Adapte au pas
sf::Vector2f FamilyMember::normaliser(sf::Vector2f ancien_point)
{
    log("Normaliser");
    int ent_x = ancien_point.x / m_pas;
    int ent_y = ancien_point.y / m_pas;
    log("Normaliser : fin");
    return sf::Vector2f (ent_x * m_pas, ent_y * m_pas);
}

void FamilyMember::lancerTrajetSpecial(sf::Vector2f point, IA_Mode mode)
{
    log("Lancer trajet special");
    m_mode_actuel = mode;
    m_cible = point;
    m_id_point_actuel = 0;
    sf::Vector2f depart = normaliser(m_pos);
    sf::Vector2f arrivee = normaliser(point);
    m_chemin_special = AStarGrille(depart, arrivee, m_obstacles, m_taille, m_pas);
    log("Lancer trajet special : fin");
}

void FamilyMember::retour()
{
    log("Retour");
    sf::Vector2f best_point = m_reseau[0];
    for (auto point: m_reseau)
    {
        if (distance_entre(m_pos, point) < distance_entre(m_pos, best_point))
        {
            best_point = point;
        }
    }
    lancerTrajetSpecial(best_point, RETOUR);
    log("Retour : fin");
}

void FamilyMember::bruitEntendu(sf::Vector2f pos)
{
    log("Bruit entendu");
    if (distance_entre(m_pos, pos) > m_delta)
    {
        lancerTrajetSpecial(pos, BRUIT);
    }
    else
    {
        rotater();
    }
    log("Bruit entendu : fin");
}

void FamilyMember::lumiereEteinte(sf::Vector2f point)
{
 //   std::vector<std::pair<sf::Vector2f, float>> &m_lampes;
   // std::vector<std::pair<sf::Vector2f, sf::Vector2f>> &m_interrupteurs;
    
    log("Lumière éteinte");

    int id {-1};
    for (int k {0}; k < m_lampes.size(); k++)
    {
        if (distance_entre(point, m_lampes[k].first) < m_lampes[k].second)
        {
            id = k;
        }
    }
    if (id != -1)
    {
        auto pos = point_centre(m_interrupteurs[id].first, m_interrupteurs[id].second, m_obstacles);
        lancerTrajetSpecial(pos, LUMIERE);
    }
    
    log("Lumière éteinte : fin");
}

void FamilyMember::rentrerDansLeRang()
{
    log("Rentrer dans le rang");
    m_mode_actuel = NORMAL;
    int id_best {0};
    for (int k {1}; k < m_chemin_global.size(); k++)
    {
        if (distance_entre(m_pos, m_chemin_global[k]) < distance_entre(m_pos, m_chemin_global[id_best]))
        {
            id_best = k;
        }
    }
    std::cout << "AU FINAL : " << distance_entre(m_pos, m_chemin_global[id_best]) << " et " << distance_entre(m_pos, m_chemin_global[0]);
    printer(m_pos);
    m_id_point_actuel = id_best;
    log(std::to_string(id_best));
    log("Rentrer dans le rang : fin");
}

void FamilyMember::agir()
{
    log("Agir");
    if (m_mode_actuel != NORMAL)
    {
        log("Pas normal");
        if (m_id_point_actuel + 1 < m_chemin_special.size())
        {
            printer(m_chemin_special);
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
                log("HEIN HEIN");
                rentrerDansLeRang();
            }
        }
    }
    else
    {
        log("WHAT ?!");
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
            log(std::to_string(id));
            m_cible = m_reseau[id];
        }
        // Continuer !
        if (m_id_point_actuel + 1 < m_chemin_global.size()) {
            m_id_point_actuel++;
        }
        else
        {
            m_id_point_actuel = 0;
        }
        log("m_id_point_actuel" + std::to_string(m_id_point_actuel));
        allerAuPoint(m_chemin_global[m_id_point_actuel]);
    }
    log("Agir : fin");
}