#ifndef ALIEN_H
#define ALIEN_H

#include "gamestate.h"
#include "ship.h"

class Alien : public Ship
{
    public:
        Alien(sf::Time tempsPassePrincipal, int niveau, float difficulte, sf::Vector2u dimensionJeu, sf::Vector2u tailleVaisseau);
        virtual ~Alien();

        void moveForward(sf::Time tempsPassePrincipal);
        bool shoot(sf::Time tempsPassePrincipal);

        const int get_speed() const
        {
            return m_vitesse;
        }
    private:
        bool m_arme;
        sf::Vector2u m_tailleTir;
};

#endif // ALIEN_H
