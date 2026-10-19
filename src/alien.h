#ifndef ALIEN_H
#define ALIEN_H

#include "gamestate.h"
#include "ship.h"

class Alien : public Ship
{
    public:
        Alien(sf::Time elapsedTime, int level, float difficulty, sf::Vector2u gameDimensions, sf::Vector2u shipSize);

        void moveForward(sf::Time elapsedTime);
        bool shoot(sf::Time elapsedTime);

        const int get_speed() const
        {
            return m_speed;
        }
        const bool get_armed() const
        {
            return m_armed;
        }
        const float get_shootingFrequency() const
        {
            return m_shootingFrequency;
        }
        const sf::Time get_lastMovementTime() const
        {
            return m_lastMovementTime;
        }
    private:
        bool m_armed;
        sf::Vector2u m_projectileSize;
};

#endif // ALIEN_H
