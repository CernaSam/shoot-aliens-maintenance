#ifndef FOND_H
#define FOND_H
#include <SFML/Graphics.hpp>
#include "gamestate.h"


class Fond
{
    public:
        Fond(sf::Vector2u dimensionsJeu);
        virtual ~Fond();

        void update(sf::Time elapsedTime);
        void draw(GameEngine* shootTheAliens);
    private:
        sf::Vector2u m_gameDimensions;

        sf::Texture *m_backgroudTexture;
        sf::Sprite *m_backgroundSprite;

        sf::Time m_backgroundElapsedTime;
};

#endif // FOND_H
