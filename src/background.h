#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SFML/Graphics.hpp>
#include "gamestate.h"


class Background
{
    public:
        Background(sf::Vector2u dimensionsJeu);
        virtual ~Background();

        void update(sf::Time elapsedTime);
        void draw(GameEngine* shootTheAliens);
    private:
        sf::Vector2u m_gameDimensions;

        sf::Texture *m_backgroudTexture;
        sf::Sprite *m_backgroundSprite;

        sf::Time m_backgroundElapsedTime;
};

#endif // BACKGROUND_H
