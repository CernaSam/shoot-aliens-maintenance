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

        void die(sf::Time tempsPassePrincipal);
        bool shoot(sf::Time tempsPassePrincipal);
        void changeState(sf::Time tempsPassePrincipal);
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
        void set_alive(sf::Time tempsPassePrincipal, bool vivant)
        {
            m_vivant = vivant;
            m_tempsPasseMourir = tempsPassePrincipal;
        }
        void set_opacity(int opacite)
        {
            m_opacite = opacite;
        }
    protected:
        int m_vitesse;
        bool m_tirer;
        float m_freqDeTir;
        sf::Vector2f m_position;
        sf::Vector2u m_tailleVaisseau;

        sf::Time m_tempsPasseMouvement;
    private:
        bool m_vivant;
        int m_opacite;
        int m_etat;
        static int nbrEtat;
        static int nbrDeVaisseaux;
        int m_id;

        sf::Time m_tempsPasseTirer;
        sf::Time m_tempsPasseMourir;
        sf::Time m_tempsPasseEtat;
        sf::Time m_tempsPasseRupture;
};

#endif // VAISSEAU_H
