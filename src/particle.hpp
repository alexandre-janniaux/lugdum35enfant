#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "scenenode.hpp"

template<typename T>
struct Particle
{
    sf::Vector2f pos; // Position
    sf::Vector2f vel; // Velocity
    float lifetime;
    float lifetime_max;
    T node;
};

struct SmokeShape : public SceneNode
{
    sf::CircleShape m_Shape;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getAbsoluteTransform();
        target.draw(m_Shape);
    }
};


template<typename T>
class ParticleEmitter : public SceneNode
{
public:
    ParticleEmitter(T copy, SceneNode& node, int);
    //~ParticleEmitter();
    void setFrequency(float);
    void setNumberOfParticles(int);
    inline int getNumberOfParticles() { return m_particles.size(); }
    void update(sf::Time);
    void addParticle(int);
    void apply(Particle<T>*);
    void effect(Particle<T>*);
private:
    std::vector<Particle<T>*> m_particles;
    float m_Frequency;
    int m_NumberOfParticles;
    SceneNode& m_node;
};

template<typename T>
ParticleEmitter<T>::ParticleEmitter(T copy, SceneNode& node, int number)
: m_Frequency()
, m_NumberOfParticles(number)
, m_particles()
, m_node(node)
{
    for (int i=0; i<m_NumberOfParticles; i++)
    {
        float angle(rand());
        m_particles.push_back(new Particle<T> {m_node.getPosition(), sf::Vector2f (cos(angle),sin(angle)), 2.f, (1.f+(rand()%100)/100.f), T() });
        m_particles.back()->node.attachParent(&m_node);
    }
}

/*ParticleSystem::~ParticleSystem()
{
    for( int i = m_particles.begin(); i != m_particles.end(); i++ )
    {
        delete m_particles[i];
    }
}
*/

template<typename T>
void ParticleEmitter<T>::setFrequency(float frequency)
{
    m_Frequency = frequency;
}

template<typename T>
void ParticleEmitter<T>::setNumberOfParticles(int number)
{
    m_NumberOfParticles = number;
}

template<typename T>
void ParticleEmitter<T>::update(sf::Time time)
{
    for (int i=0;i<m_particles.size(); i++)
    {
        m_particles[i]->lifetime-=time.asSeconds();
        if (m_particles[i]->lifetime<0)
        {
            delete m_particles[i];
            m_particles[i] = nullptr;
            addParticle(i);
        }
        else
        {
            m_particles[i]->pos+=m_particles[i]->vel*time.asSeconds();
            m_particles[i]->node.setPosition(m_particles[i]->pos);
            apply(m_particles[i]);
            effect(m_particles[i]);
        }
    }
}


template<>
void ParticleEmitter<SmokeShape>::apply(Particle<SmokeShape>* particle)
{
    sf::Vector2f gravity(0,0.01);
    particle->vel+=gravity;
}

template<>
void ParticleEmitter<SmokeShape>::effect(Particle<SmokeShape>* particle)
{
    sf::Color color(255,255,255,255*particle->lifetime/particle->lifetime_max);
    particle->node.m_Shape.setFillColor(color);
}

template<typename T>
void ParticleEmitter<T>::effect(Particle<T>* particle)
{
}

template<typename T>
void ParticleEmitter<T>::addParticle(int num)
{
    float angle(rand());
    m_particles[num] = new Particle<T> {m_node.getPosition(), sf::Vector2f (cos(angle),sin(angle)), 2.f, 1.f+(rand()%100)/100.f, T() };
    m_particles[num]->node.attachParent(&m_node);
}

template<typename T>
void apply(Particle<T>* particle)
{
}



