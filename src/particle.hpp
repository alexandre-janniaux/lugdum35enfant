#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>

template<typename T>
struct Particle
{
    sf::Vector2f pos; // Position
    sf::Vector2f vel; // Velocity
    float lifetime;
    T node;
};


template<typename T>
class ParticleEmitter:
{
public:
    ParticleEmitter(T copy);
    //~ParticleEmitter();
    void setFrequency(float);
    void setNumberOfParticles(float);
    int getNumberOfParticles() { return m_particles.size(); }
    void onCreate(Particle<T>);
    void update(sf::Time);
    void addParticle();
    void apply(Particles<T>*);
    void effect(Particle<T>*);
private:
    std::vector<Particle<T>*> m_particles;
    float m_Frequency;
    float m_NumberOfParticles;
    SceneNode* m_node;
};

ParticleEmitter::ParticleEmitter(T copy)
: m_Frequency()
, m_NumberOfParticles()
, m_particles()
, m_node()
{

}

/*ParticleSystem::~ParticleSystem()
{
    for( int i = m_particles.begin(); i != m_particles.end(); i++ )
    {
        delete m_particles[i];
    }
}
*/

void ParticleEmitter::setFrequency(float frequency)
{
    m_Frequency = frequency;
}

void ParticleEmitter::setNumberOfParticles(float number)
{
    m_NumberOfParticles = number;
}

void ParticleEmitter::onCreate(Particle<T> particle)
{

}

void ParticleEmitter::update(sf::Time time)
{
    float initNb(m_NumberOfParticles);
    m_NumberOfParticles+=time.asSeconds()*m_frequency;
    for (int i=0, i<(static_cast<int>(m_NumberOfParticles)-static_cast<int>(initNb)), i++)
        addParticle();
    for (int i=0,i<m_NumberOfParticles, i++)
    {
        m_particles[i].pos+=m_particles[i].vel*time.asSeconds();
        m_particles[i].lifetime-=time.asSeconds();
        apply(m_particles[i]);
    }
}

template<SmokeShape>
void ParticleEmitter::apply(Particle<Smoke>* particle)
{
    sf::Vector2f gravity(0,0.3)
    particle.vel-=gravity;
}

template<SmokeShape>
void effect(Particle<Smoke>* particle)
{
    sf::Color color(255,255,255,255*particle.lifetime/particle.lifetime_max);
    particle.m_Shape.setFillColor(color);
}

template<typename T>
void effect(Particle<T>* particle)
{
}

template<typename T>
void ParticleEmitter::addParticle()
{
    float angle(rand())
    m_particles.push_back(Particle {m_node.getPosition(), sf::Vector2f (cos(angle),sin(angle)), 2.f, T() });
}

template<typename T>
void apply(Particle<T>* particle)
{
}

struct SmokeShape
{
    sf::CircleShape m_Shape;
    float lifetime_max;
};

