#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "alien.h"
#include "player.h"
#include "soundmanager.h"

class Explosion
{
    public:
        Explosion(sf::Time elapsedTime, sf::Vector2f position, sf::Vector2u shipSize, unsigned int explosionSize, int speed);

        const sf::Vector2f get_position() const
        {
            return m_position;
        }
        const int get_state() const
        {
            return m_state;
        }

        void changeState(sf::Time elapsedTime);
        void moveForward(sf::Time elapsedTime);
    private:
        int m_state;
        sf::Vector2f m_position;
        int m_speed;

        sf::Time m_lastStateChangeTime;
        sf::Time m_lastMovementTime;
};

#endif // EXPLOSION_H
