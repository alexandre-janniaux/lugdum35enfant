//
//  IA_exemple.cpp
//  Reseau
//
//  Created by Thibault Dardinier on 24/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "IA_exemple.hpp"
#include "IA_familymember.hpp"

void ligner(sf::Vector2f point_a, sf::Vector2f point_b, sf::RenderWindow &window)
{
    sf::Vertex line[] =
    {
        sf::Vertex(point_a),
        sf::Vertex(point_b)
    };
    window.draw(line, 3, sf::Lines);
}

void IA_exemple(GameWorld &gw)
{
    std::cout << "HELLO WORLD!" << std::endl;
    
    /*int hauteur = 400;
    int largeur = 400;
    sf::FloatRect carte (0, 0, largeur, hauteur);
    std::vector<sf::FloatRect> obstacles {};
    
    obstacles.push_back(sf::FloatRect (100, 0, 10, 190));
    obstacles.push_back(sf::FloatRect (100, 210, 10, 190));
    
    obstacles.push_back(sf::FloatRect (100, 100, 90, 10));
    obstacles.push_back(sf::FloatRect (210, 100, 90, 10));
    
    obstacles.push_back(sf::FloatRect (300, 0, 10, 290));
    obstacles.push_back(sf::FloatRect (300, 310, 10, 90));
    
    obstacles.push_back(sf::FloatRect (20, 20, 30, 30));
    obstacles.push_back(sf::FloatRect (30, 300, 30, 30));
    obstacles.push_back(sf::FloatRect (150, 30, 100, 50));
    obstacles.push_back(sf::FloatRect (150, 250, 100, 100));
    obstacles.push_back(sf::FloatRect (330, 20, 40, 100));
    
    //obstacles.push_back(sf::FloatRect(190, 50, 20, 300));
    
    Mesure les perfs
     // Pas = sqrt(hauteur * largeur / 2500) pour temps <= 1 s
     using namespace std::chrono;
     milliseconds time0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
     std::vector<sf::Vector2f> reseau = trouverReseau(carte, obstacles, 10);
     milliseconds time1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
     std::vector<sf::Vector2f> reseau2 = trouverReseau(carte, obstacles, 20);
     milliseconds time2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
     std::cout << "Premier : " << (time1 - time0).count() << ", deuxième : " << (time2 - time1).count() << std::endl;
     */
    
    std::vector<sf::FloatRect> obstacles {};

    sf::FloatRect carte (sf::FloatRect(0, 0, gw.m_size.x - 200, gw.m_size.y - 100));
    for (auto &meuble: gw.m_meubles)
    {
        if (meuble->isObstacle())
        {
            obstacles.push_back(meuble->m_hitBox);
        }
    }
    for (auto &mur: gw.m_murs)
    {
        obstacles.push_back(mur->getRect());
    }
    
    float pas = 10;
    std::vector<sf::Vector2f> reseau {};
    
    /*
    reseau.push_back(sf::Vector2f (100, 50));
    reseau.push_back(sf::Vector2f (400, 50));
    reseau.push_back(sf::Vector2f (150, 400));
    reseau.push_back(sf::Vector2f (200, 700));
    reseau.push_back(sf::Vector2f (650, 350));
     */
     
    //reseau.push_back(sf::Vector2f (100, 100));
    //reseau.push_back(sf::Vector2f (700, 100));
    
    /*
    reseau.push_back(sf::Vector2f (64,49));
    reseau.push_back(sf::Vector2f (67,260));
    reseau.push_back(sf::Vector2f (266,211));
    reseau.push_back(sf::Vector2f (437,100));
    reseau.push_back(sf::Vector2f (78,328));
    reseau.push_back(sf::Vector2f (66,558));
    reseau.push_back(sf::Vector2f (362,558));
    reseau.push_back(sf::Vector2f (387,405));
    reseau.push_back(sf::Vector2f (637,496));
    reseau.push_back(sf::Vector2f (621,326));
    reseau.push_back(sf::Vector2f (682,135));
    reseau.push_back(sf::Vector2f (528,161));
     
    for (int k {0}; k < reseau.size(); k++)
    {
        auto point = reseau[k];
        int x = point.x / 10;
        int y = point.y / 10;
        reseau[k] = sf::Vector2f (x * 10, y * 10);
    }
    printer(reseau);
     */
    std::vector<std::pair<sf::FloatRect, sf::FloatRect>> cachettes {};
    
    float offset = 25.;
    for (auto &meuble: gw.m_meubles)
    {
        std::pair<sf::FloatRect, sf::FloatRect> cachette;
        sf::FloatRect hb_ext (meuble->m_hitBox.left - offset, meuble->m_hitBox.top - offset, meuble->m_hitBox.width + 2 * offset, meuble->m_hitBox.height + 2 * offset);
        cachette = std::make_pair(meuble->m_hitBox, hb_ext);
        cachettes.push_back(cachette);
    }
    auto lampes = std::vector<std::pair<sf::Vector2f, float>> {};
    auto interrupteurs = std::vector<std::pair<sf::Vector2f, sf::Vector2f>> {};
    
    FamilyMember papa (sf::Vector2f (carte.width, carte.height), obstacles, std::vector<sf::Vector2f> {}, MEUBLE, sf::Vector2f (100, 100), cachettes, lampes, interrupteurs);

    
    reseau = papa.creer_reseau_meuble(cachettes, obstacles);
    printer(reseau);
    //reseau = trouverReseau(carte, obstacles, 50);
    //printer(AStar(0, 1, reseau, obstacles));
    
    
    // On tente un AStar différent
    /*
     float pas = 20;
     std::vector<sf::Vector2f> grille {};
     sf::Vector2f depart (0, 0);
     sf::Vector2f arrivee (340, 0);
     grille.push_back(depart);
     grille.push_back(arrivee);
     for (int x {0}; x < largeur; x += pas)
     {
     for (int y {0}; y < hauteur; y += pas)
     {
     if ((x != depart.x || y != depart.y) && (x != arrivee.x || y != arrivee.y) && dansAucunObstacle(sf::Vector2f (x, y), obstacles))
     {
     grille.push_back(sf::Vector2f (x, y));
     }
     }
     }
     
     
     using namespace std::chrono;
     milliseconds time0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
     auto chemin = (AStar(0, 1, grille, obstacles));
     milliseconds time1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
     auto chemin2 = AStarGrille(sf::Vector2f (0, 0), sf::Vector2f (340, 0), obstacles, sf::Vector2f (largeur, hauteur), 10.);
     milliseconds time2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
     std::cout << "Premier : " << (time1 - time0).count() << ", deuxième : " << (time2 - time1).count() << std::endl;
     
     auto commerce = getOrdreCommerce(0, reseau, obstacles);
     */
    using namespace std::chrono;
    milliseconds time0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    
    auto chemin_global = generateRonde(carte, obstacles, reseau, pas);
    milliseconds time1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    std::cout << "Exécution : " << ((float) (time1 - time0).count()) / 1000. << std::endl;
    std::cout << "Taille : " << chemin_global.size() << std::endl;
    
    
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(carte.width, carte.height), "SFML window");
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                //window.close();
                std::cout << std::rand();
            }
            
            if (event.type == sf::Event::MouseButtonPressed)
            {
                //window.close();
                std::cout << "reseau.push_back(sf::Vector2f (" << event.mouseButton.x << "," << event.mouseButton.y << "));" << std::endl;
            }
        }
        
        // Clear screen
        window.clear();
        
        // Trace la map
        for (auto obstacle: obstacles)
        {
            sf::RectangleShape rectangle(sf::Vector2f(obstacle.width, obstacle.height));
            rectangle.setPosition(obstacle.left, obstacle.top);
            rectangle.setFillColor(sf::Color::Red);
            window.draw(rectangle);
        }
        
        /*
         // Trace le chemin
         for (int k {0}; k + 1 < chemin.size(); k++)
         {
         ligner(grille[chemin[k]], grille[chemin[k+1]], window);
         }
         */
        
        
        /*
         // Trace le chemin 2
         for (int k {0}; k + 1 < chemin2.size(); k++)
         {
         ligner(chemin2[k], chemin2[k+1], window);
         }
         */
        
        /*
         // Trace le réseau
         // Liens
         for (auto point_a: reseau)
         {
         for (auto point_b: reseau)
         {
         if (isVisible(point_a, point_b, obstacles))
         {
         ligner(point_a, point_b, window);
         }
         }
         }
         */
        
        // Trace le chemin global
        for (int k {0}; k + 1 < chemin_global.size(); k++)
        {
            ligner(chemin_global[k], chemin_global[k+1], window);
        }
        
        for (int k {0}; k < reseau.size(); k++)
        {
            /*
             // Texte
             sf::Text text;
             sf::Font font;
             font.loadFromFile(resourcePath() + "sansation.ttf");
             text.setFont(font); // font est un sf::Font
             text.setString(std::to_string(k));
             text.setCharacterSize(20);
             text.setColor(sf::Color::Yellow);
             text.setPosition(reseau[k]);
             window.draw(text);
             */
            
            // Rond
            sf::CircleShape rond(5);
            rond.setOrigin(5, 5);
            rond.setPosition(reseau[k]);
            window.draw(rond);
        }
        // Update the window
        window.display();
    }
}