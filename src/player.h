#ifndef JOUEUR_H
#define JOUEUR_H

#include "gamestate.h"
#include "ship.h"
#include <SFML/Audio.hpp>

class Player : public Ship
{
    public:
        Player();
        virtual ~Player();

        void move(sf::Time tempsPassePrincipal, int direction);

        void set_player(sf::Vector2u dimensionJeu, sf::Vector2u tailleVaisseau);
    private:
        sf::Vector2u m_dimensionFenetre;
        int m_vitesseMax;
        float m_acceleration;
        int m_direction;

        sf::SoundBuffer buff;
        sf::Sound son;
};

#endif // JOUEUR_H
