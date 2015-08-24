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
    FamilyMember(sf::Vector2f taille, std::vector<sf::FloatRect> obstacles, std::vector<sf::Vector2f> reseau, IA_Type type, sf::Vector2f pos);
private:
    const float m_delta = 2.;
    const float m_norme_vitesse = 5.;
    const float m_pas = 10.;
    
    const sf::Vector2f m_taille;
    const std::vector<sf::FloatRect> m_obstacles;
    const std::vector<sf::Vector2f> m_reseau;
    const std::vector<sf::Vector2f> m_chemin_global;
    const IA_Type m_type; // 1 : IA meuble, 2 : IA zone

    sf::Vector2f m_vit;
    sf::Vector2f m_pos;
    bool m_is_enlighted;
    
    sf::Vector2f m_point_cible; // PETIT point cible
    int m_id_point_actuel; // Pour se repérer dans le chemin, speciale ou global
    IA_Mode m_mode_actuel; // 1 : Mode normal, 2 : Mode bruit, 3 : Mode vers lumière, 4 : Mode retour
    std::vector<sf::Vector2f> m_chemin_special;
    sf::Vector2f m_cible; // Mode finit après ce point cible
    // m_cible => utilisé avec traj speciale, et traj normale (meuble, point strat)
    
    sf::Vector2f normaliser(sf::Vector2f ancien_point);
    void agir();
    void allerAuPoint(sf::Vector2f pos);
    void lancerTrajetSpecial(sf::Vector2f point, IA_Mode mode);
    void retour();
    
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
    }
    
    void interagir()
    {
        
    }
};