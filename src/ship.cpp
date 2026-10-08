#include "ship.h"

int Ship::nbrEtat = 4;
int Ship::nbrDeVaisseaux = 0;

Ship::Ship()
{
    m_vivant = true;
    m_opacite = 255;
    m_etat = 0;
    m_speed = 0;
    m_id = Ship::nbrDeVaisseaux;
    Ship::nbrDeVaisseaux++;
}

Ship::~Ship()
{
}

void Ship::die(sf::Time elapsedTime)
{
    if(m_opacite > 0)
    {
        m_opacite = m_opacite - 255 * (elapsedTime.asSeconds() - m_deathTime.asSeconds()) * 2;
        m_deathTime = elapsedTime;
    }
    else if(m_opacite < 0)
    {
        m_opacite = 0;
    }
    if(m_opacite == 0)
    {
        SoundManager::getInstance()->playEngineSound(m_id, true);
    }
}

bool Ship::shoot(sf::Time elapsedTime)
{
    m_tirer = false;
    if(elapsedTime.asSeconds() - m_lastShotTime.asSeconds() > 1 / m_freqDeTir)
    {
        m_lastShotTime = elapsedTime;
        m_tirer = true;
    }
    return m_tirer;
}

void Ship::changeState(sf::Time elapsedTime)
{
    if((elapsedTime.asMilliseconds() - m_lastStateChangeTime.asMilliseconds()) >= 75)
    {
        if(m_etat >= nbrEtat-2)
        {
            m_etat = 0;
        }else{
            m_etat++;
        }
        m_lastStateChangeTime = elapsedTime;
    }
    if((elapsedTime.asMilliseconds() - m_tempsPasseRupture.asMilliseconds()) >= 30)
    {
        if(m_etat == nbrEtat-1)
        {
            m_etat = 0;
        }else{
            if(rand() % 50 + 1 == 1)
            {
                m_etat = nbrEtat-1;
            }
        }
        m_tempsPasseRupture = elapsedTime;
    }
}

sf::Vector2u Ship::get_size(sf::Vector2u tailleJoueur)
{
    sf::Vector2u taille = sf::Vector2u(tailleJoueur.x/nbrEtat, tailleJoueur.y);
    return taille;
}
