#include "alien.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>

Alien::Alien(sf::Time elapsedTime, int level, float difficulty, sf::Vector2u gameDimensions, sf::Vector2u shipSize)
{
    m_speed = 500 * difficulty + level * 20;
    m_shootingFrequency = 1 + difficulty + level / 5;
    m_lastMovementTime = elapsedTime;
    
    if(level == 1)
    {
        if(rand() % 100 + 1 < 30)
        {
            m_armed = true;
        }else{
            m_armed = false;
        }
    }
    else if(level <= 2)
    {
        if(rand() % 100 + 1 < 60)
        {
            m_armed = true;
        }else{
            m_armed = false;
        }
    }
    else if(level <= 4)
    {
        if(rand() % 100 + 1 < 90)
        {
            m_armed = true;
        }else{
            m_armed = false;
        }
    }else{
        m_armed = true;
    }
    m_position.x = rand() % (gameDimensions.x + 1 - shipSize.x);
    m_position.y = -100;
}

void Alien::moveForward(sf::Time elapsedTime)
{
    m_position.y = m_position.y + m_speed * (elapsedTime.asSeconds() - m_lastMovementTime.asSeconds());
    m_lastMovementTime = elapsedTime;
}

bool Alien::shoot(sf::Time elapsedTime)
{
    Ship::shoot(elapsedTime);
    if(!(m_armed)) m_shooting = false;
    return m_shooting;
}
