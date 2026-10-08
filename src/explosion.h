#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "alien.h"
#include "player.h"
#include "soundmanager.h"

class Explosion
{
    public:
        Explosion(sf::Time tempsPassePrincipal, sf::Vector2f position, sf::Vector2u tailleVaisseau, unsigned int tailleExplosion, int vitesse);
        virtual ~Explosion();

        const sf::Vector2f get_position() const
        {
            return m_position;
        }
        const int get_state() const
        {
            return m_etat;
        }

        void changeState(sf::Time tempsPassePrincipal);
        void moveForward(sf::Time tempsPassePrincipal);
    private:
        int m_etat;
        sf::Vector2f m_position;
        int m_vitesse;

        sf::Time m_tempsPasseEtat;
        sf::Time m_tempsPasseAvancer;
};

#endif // EXPLOSION_H
