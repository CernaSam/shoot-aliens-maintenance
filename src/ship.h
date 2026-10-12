#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include "gamestate.h"
#include "soundmanager.h"

class Ship
{
    public:
        Ship();
        virtual ~Ship();

        void die(sf::Time elapsedTime);
        bool shoot(sf::Time elapsedTime);
        void changeState(sf::Time elapsedTime);
        static sf::Vector2u get_size(sf::Vector2u playerSize);
        const sf::Vector2f get_position() const
        {
            return m_position;
        }
        const bool is_alive() const
        {
            return m_alive;
        }
        const int get_opacity() const
        {
            return m_opacity;
        }
        const int get_nbr_images() const
        {
            return numberOfStates;
        }
        const int get_state() const
        {
            return m_state;
        }
        const int get_id() const
        {
            return m_id;
        }
        void set_alive(sf::Time elapsedTime, bool alive)
        {
            m_alive = alive;
            m_deathTime = elapsedTime;
        }
        void set_opacity(int opacity)
        {
            m_opacity = opacity;
        }
    protected:
        int m_speed;
        bool m_shooting;
        float m_shootingFrequency;
        sf::Vector2f m_position;
        sf::Vector2u m_shipSize;

        sf::Time m_lastMovementTime;
    private:
        bool m_alive;
        int m_opacity;
        int m_state;
        static int numberOfStates;
        static int numberOfShips;
        int m_id;

        sf::Time m_lastShotTime;
        sf::Time m_deathTime;
        sf::Time m_lastStateChangeTime;
        sf::Time m_lastSpecialStateTime;
};

#endif // SHIP_H
