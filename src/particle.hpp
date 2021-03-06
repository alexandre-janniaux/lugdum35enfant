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
        target.draw(m_Shape, states);
    }
};


template<typename T>
class ParticleEmitter : public SceneNode
{
public:
    ParticleEmitter(T copy, SceneNode& node, int);
    void setFrequency(float);
    void setNumberOfParticles(int);
    inline int getNumberOfParticles() { return m_particles.size(); }
    void update(sf::Time);
    void addParticle(int);
    void apply(Particle<T>*);
    void effect(Particle<T>*);
    void setEmission(bool);
private:
    std::vector<Particle<T>*> m_particles;
    float m_Frequency;
    int m_NumberOfParticles;
    SceneNode& m_node;
    bool m_activate;
};

template<typename T>
ParticleEmitter<T>::ParticleEmitter(T copy, SceneNode& snode, int number)
: m_Frequency()
, m_NumberOfParticles(number)
, m_particles()
, m_activate(true)
, m_node(snode)
{
    setPosition({400.f,300.f});
    for (int i=0; i<m_NumberOfParticles; i++)
    {
        float angle(rand());
        float life(0.1+(rand()%100)/1000.f);
        m_particles.push_back(new Particle<T> {getPosition(), (40.f+rand()%100)*(sf::Vector2f (cos(angle),sin(angle))), life, life, T() });
        m_particles.back()->node.attachParent(m_node);
    }
}

template<typename T>
void ParticleEmitter<T>::setEmission(bool activate)
{
        m_activate = activate;
}

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
    if (m_activate)
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
}


template<>
void ParticleEmitter<SmokeShape>::apply(Particle<SmokeShape>* particle)
{
    sf::Vector2f gravity(0.f,particle->lifetime/particle->lifetime_max);
    particle->vel+=20.f*gravity;
}

template<>
void ParticleEmitter<SmokeShape>::effect(Particle<SmokeShape>* particle)
{
    sf::Color color(0,0,0,255*particle->lifetime/particle->lifetime_max);
    particle->node.m_Shape.setFillColor(color);
    particle->node.m_Shape.setRadius(5);
}

template<typename T>
void ParticleEmitter<T>::effect(Particle<T>* particle)
{
}

template<typename T>
void ParticleEmitter<T>::addParticle(int num)
{
    float angle(rand());
    float life(0.1+(rand()%100)/1000.f);
    m_particles[num] = new Particle<T> {getPosition(), (40.f+rand()%100)*(sf::Vector2f (cos(angle),sin(angle))), life, life, T() };
    m_particles[num]->node.attachParent(m_node);
}

template<typename T>
void apply(Particle<T>* particle)
{
}
