#ifndef VAISSEAU_H
#define VAISSEAU_H

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
        static sf::Vector2u get_size(sf::Vector2u tailleJoueur);
        const sf::Vector2f get_position() const
        {
            return m_position;
        }
        const bool is_alive() const
        {
            return m_vivant;
        }
        const int get_opacity() const
        {
            return m_opacite;
        }
        const int get_nbr_images() const
        {
            return nbrEtat;
        }
        const int get_state() const
        {
            return m_etat;
        }
        const int get_id() const
        {
            return m_id;
        }
        void set_alive(sf::Time elapsedTime, bool alive)
        {
            m_vivant = alive;
            m_deathTime = elapsedTime;
        }
        void set_opacity(int opacity)
        {
            m_opacite = opacity;
        }
    protected:
        int m_speed;
        bool m_tirer;
        float m_freqDeTir;
        sf::Vector2f m_position;
        sf::Vector2u m_shipSize;

        sf::Time m_lastMovementTime;
    private:
        bool m_vivant;
        int m_opacite;
        int m_etat;
        static int nbrEtat;
        static int nbrDeVaisseaux;
        int m_id;

        sf::Time m_lastShotTime;
        sf::Time m_deathTime;
        sf::Time m_lastStateChangeTime;
        sf::Time m_tempsPasseRupture;
};

#endif // VAISSEAU_H
