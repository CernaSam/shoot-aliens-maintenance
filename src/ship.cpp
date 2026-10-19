#include "ship.h"

int Ship::numberOfStates = 4;
int Ship::numberOfShips = 0;

Ship::Ship() : m_alive(true), m_opacity(255), m_state(0), m_speed(0)
{
    Ship::numberOfShips++;
}

void Ship::die(sf::Time elapsedTime)
{
    if(m_opacity > 0)
    {
        m_opacity = m_opacity - 255 * (elapsedTime.asSeconds() - m_deathTime.asSeconds()) * 2;
        m_deathTime = elapsedTime;
    }
    else if(m_opacity < 0)
    {
        m_opacity = 0;
    }
    if(m_opacity == 0)
    {
        SoundManager::getInstance()->playEngineSound(m_id, true);
    }
}

bool Ship::shoot(sf::Time elapsedTime)
{
    m_shooting = false;
    if(elapsedTime.asSeconds() - m_lastShotTime.asSeconds() > 1 / m_shootingFrequency)
    {
        m_lastShotTime = elapsedTime;
        m_shooting = true;
    }
    return m_shooting;
}

void Ship::changeState(sf::Time elapsedTime)
{
    if((elapsedTime.asMilliseconds() - m_lastStateChangeTime.asMilliseconds()) >= 75)
    {
        if(m_state >= numberOfStates-2)
        {
            m_state = 0;
        }else{
            m_state++;
        }
        m_lastStateChangeTime = elapsedTime;
    }
    if((elapsedTime.asMilliseconds() - m_lastSpecialStateTime.asMilliseconds()) >= 30)
    {
        if(m_state == numberOfStates-1)
        {
            m_state = 0;
        }else{
            if(rand() % 50 + 1 == 1)
            {
                m_state = numberOfStates-1;
            }
        }
        m_lastSpecialStateTime = elapsedTime;
    }
}

sf::Vector2u Ship::get_size(sf::Vector2u playerSize)
{
    sf::Vector2u size = sf::Vector2u(playerSize.x/numberOfStates, playerSize.y);
    return size;
}
