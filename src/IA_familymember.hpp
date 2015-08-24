#pragma once

//
//  IA_familymember.h
//  Reseau
//
//  Created by Thibault Dardinier on 24/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "IA_exemple.hpp"

enum IA_Mode {NORMAL, BRUIT, LUMIERE, RETOUR};
enum IA_Type {ZONE, MEUBLE};

class FamilyMember
{
public:
    void update(sf::Vector2f pos, bool lumiere); // On agit si on a dépassé
    void bruitEntendu(sf::Vector2f pos);
    void lumiereEteinte(sf::Vector2f point);
    FamilyMember(sf::Vector2f taille, std::vector<sf::FloatRect> &obstacles, std::vector<sf::Vector2f> reseau, IA_Type type, sf::Vector2f pos, std::vector<std::pair<sf::FloatRect, sf::FloatRect>> &cachettes, std::vector<std::pair<sf::Vector2f, float>> &lampes, std::vector<std::pair<sf::FloatRect, sf::FloatRect>> &interrupteurs);
//private:
    const float m_delta = 2.;
    const float m_norme_vitesse = 5.;
    const float m_pas = 10.;
    
    // CONSTANTES
    sf::Vector2f m_taille;
    std::vector<sf::FloatRect> &m_obstacles;
    std::vector<sf::Vector2f> m_reseau;
    std::vector<sf::Vector2f> m_chemin_global;
    IA_Type m_type; // 1 : IA meuble, 2 : IA zone
    std::vector<std::pair<sf::Vector2f, float>> &m_lampes;
    std::vector<std::pair<sf::FloatRect, sf::FloatRect>> &m_interrupteurs;

    sf::Vector2f m_vit;
    sf::Vector2f m_pos;
    bool m_is_enlighted;
    
    sf::Vector2f m_point_cible; // PETIT point cible
    int m_id_point_actuel; // Pour se repérer dans le chemin, speciale ou global
    IA_Mode m_mode_actuel; // 1 : Mode normal, 2 : Mode bruit, 3 : Mode vers lumière, 4 : Mode retour
    std::vector<sf::Vector2f> m_chemin_special;
    sf::Vector2f m_cible; // Mode finit après ce point cible, donc pas pour normal
    // m_cible => utilisé avec traj speciale, et traj normale (meuble, point strat)
    
    sf::Vector2f normaliser(sf::Vector2f ancien_point);
    sf::Vector2f point_centre(sf::FloatRect hb_int, sf::FloatRect hb_ext, std::vector<sf::FloatRect> obstacles);
    std::vector<sf::Vector2f> normalise_reseau(std::vector<sf::Vector2f> reseau);
    void agir();
    void allerAuPoint(sf::Vector2f pos);
    void lancerTrajetSpecial(sf::Vector2f point, IA_Mode mode);
    void retour();
    void rentrerDansLeRang();
    std::vector<sf::Vector2f> creer_reseau_meuble(std::vector<std::pair<sf::FloatRect,sf::FloatRect>> cachettes, std::vector<sf::FloatRect> obstacles);
    
    void setVitesse(sf::Vector2f vit)
    {
        m_vit = vit;
        if (!m_is_enlighted)
        {
            m_vit *= 0.5f; // Vitesse divisée par 2 dans l'ombre
        }
        //SendMessage(SetEntitySpeedMessage(m_entity, vit));
    }
    
    void rotater()
    {
        //SendMessage(SetEntityRotationMessage(m_entity, rot));
        std::cout << "ROTATION";
    }
    
    void interagir()
    {
        
    }
};