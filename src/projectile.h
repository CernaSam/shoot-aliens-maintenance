#ifndef TIR_H
#define TIR_H

#include "gamestate.h"
#include "soundmanager.h"
#include <vector>
#include <iostream>

class Projectile
{
    public:
        Projectile(sf::Time elapsedTime, bool isEnemy, int speed, sf::Vector2f position, sf::Vector2u alienSize, sf::Vector2u m_projectileSize);
        virtual ~Projectile();

        void moveForward(sf::Time elapsedTime);

        const sf::Vector2f get_position() const
        {
            return m_position;
        }
        const bool get_enemy() const
        {
            return m_ennemi;
        }
    private:
        sf::Vector2f m_position;
        int m_speed;
        bool m_ennemi;

        sf::Time m_lastMovementTime;
};

#endif // TIR_H
