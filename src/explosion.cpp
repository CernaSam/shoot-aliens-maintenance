#include "explosion.h"

Explosion::Explosion(sf::Time elapsedTime, sf::Vector2f position, sf::Vector2u shipSize, unsigned int explosionSize, int speed)
{
    m_etat = 0;
    m_position.x = position.x - explosionSize / 2 + shipSize.x / 2;
    m_position.y = position.y - explosionSize / 2 + shipSize.y / 2;
    m_speed = speed;
    m_lastStateChangeTime = elapsedTime;
    m_lastMovementTime = elapsedTime;
    SoundManager::getInstance()->playSound(EXPLOSION);
}

Explosion::~Explosion()
{
}

void Explosion::changeState(sf::Time elapsedTime)
{
    if((elapsedTime.asMilliseconds() - m_lastStateChangeTime.asMilliseconds()) >= 75)
    {
        m_etat++;
        m_lastStateChangeTime = elapsedTime;
    }
}

void Explosion::moveForward(sf::Time elapsedTime)
{
    m_position.y = m_position.y + m_speed * (elapsedTime.asSeconds() - m_lastMovementTime.asSeconds());
    m_lastMovementTime = elapsedTime;
}
