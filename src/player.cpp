#include "player.h"
#include <iostream>

enum Directions
{
    IMMOBILE, GAUCHE, DROITE
};

Player::Player()
{
    m_freqDeTir = 4;
}

Player::~Player()
{
}

void Player::set_player(sf::Vector2u gameDimensions, sf::Vector2u shipSize)
{
    m_position.x = gameDimensions.x / 2 - shipSize.x / 2;
    m_position.y = gameDimensions.y - shipSize.y - 10;
    m_maxSpeed = gameDimensions.x * 1.5;
    m_shipSize = shipSize;
    m_dimensionFenetre = gameDimensions;
}

void Player::move(sf::Time elapsedTime, int direction)
{
    if(this->is_alive())
    {
        m_acceleration = m_maxSpeed * (elapsedTime.asSeconds() - m_lastMovementTime.asSeconds()) * 6;

        if(m_speed == 0) m_direction = direction;

        if(direction == m_direction && direction != IMMOBILE)
        {
            m_speed = m_speed + m_acceleration;
        }
        else if(direction == IMMOBILE)
        {
            m_speed = m_speed - m_acceleration;
        }else{
            m_speed = m_speed - 2 * m_acceleration;
        }

        if(m_speed > m_maxSpeed) m_speed = m_maxSpeed;
        if(m_speed <= 0)
        {
            m_speed = 0;
        }

        if(m_direction == GAUCHE)
        {
            m_position.x = m_position.x - m_speed * (elapsedTime.asSeconds() - m_lastMovementTime.asSeconds());
        }
        else if(m_direction == DROITE)
        {
            m_position.x = m_position.x + m_speed * (elapsedTime.asSeconds() - m_lastMovementTime.asSeconds());
        }

        if(m_position.x < 0)
        {
            m_position.x = 0;
            m_speed = 0;
        }

        if(m_position.x > m_dimensionFenetre.x - m_shipSize.x)
        {
            m_position.x = m_dimensionFenetre.x - m_shipSize.x;
            m_speed = 0;
        }
    }
    m_lastMovementTime = elapsedTime;
}
