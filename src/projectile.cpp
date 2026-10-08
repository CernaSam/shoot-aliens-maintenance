#include "projectile.h"

Projectile::Projectile(sf::Time elapsedTime, bool isEnemy, int vitesseVaisseau, sf::Vector2f position, sf::Vector2u shipSize, sf::Vector2u m_projectileSize)
{
    m_ennemi = isEnemy;
    m_speed = vitesseVaisseau * 2;
    m_position.x = position.x + shipSize.x / 2 - m_projectileSize.x / 2;
    m_position.y = position.y + shipSize.y / 2;
    m_lastMovementTime = elapsedTime;

    if(!m_ennemi) SoundManager::getInstance()->playSound(TIR);
}

Projectile::~Projectile()
{
}

void Projectile::moveForward(sf::Time elapsedTime)
{
    if(m_ennemi)
    {
        m_position.y = m_position.y + m_speed * (elapsedTime.asSeconds() - m_lastMovementTime.asSeconds());
        m_lastMovementTime = elapsedTime;
    }else{
        m_position.y = m_position.y - 600 * (elapsedTime.asSeconds() - m_lastMovementTime.asSeconds());
        m_lastMovementTime = elapsedTime;
    }
}
