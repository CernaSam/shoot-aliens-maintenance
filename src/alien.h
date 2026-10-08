#ifndef ALIEN_H
#define ALIEN_H

#include "gamestate.h"
#include "ship.h"

class Alien : public Ship
{
    public:
        Alien(sf::Time elapsedTime, int niveau, float difficulte, sf::Vector2u gameDimensions, sf::Vector2u shipSize);
        virtual ~Alien();

        void moveForward(sf::Time elapsedTime);
        bool shoot(sf::Time elapsedTime);

        const int get_speed() const
        {
            return m_speed;
        }
    private:
        bool m_arme;
        sf::Vector2u m_projectileSize;
};

#endif // ALIEN_H
