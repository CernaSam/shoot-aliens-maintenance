#include "alien.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>

Alien::Alien(sf::Time elapsedTime, int niveau, float difficulte, sf::Vector2u gameDimensions, sf::Vector2u shipSize)
{
    m_speed = 500 * difficulte + niveau * 20;
    if(niveau == 1)
    {
        if(rand() % 100 + 1 < 30)
        {
            m_arme = true;
        }else{
            m_arme = false;
        }
    }
    else if(niveau <= 2)
    {
        if(rand() % 100 + 1 < 60)
        {
            m_arme = true;
        }else{
            m_arme = false;
        }
    }
    else if(niveau <= 4)
    {
        if(rand() % 100 + 1 < 90)
        {
            m_arme = true;
        }else{
            m_arme = false;
        }
    }else{
        m_arme = true;
    }
    m_position.x = rand() % (gameDimensions.x + 1 - shipSize.x);
    m_position.y = -100;
    m_freqDeTir = 1 + difficulte + niveau / 5;
    m_lastMovementTime = elapsedTime;
}

Alien::~Alien()
{
}

void Alien::moveForward(sf::Time elapsedTime)
{
    m_position.y = m_position.y + m_speed * (elapsedTime.asSeconds() - m_lastMovementTime.asSeconds());
    m_lastMovementTime = elapsedTime;
}

bool Alien::shoot(sf::Time elapsedTime)
{
    Ship::shoot(elapsedTime);
    if(!(m_arme)) m_tirer = false;
    return m_tirer;
}
