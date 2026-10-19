#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SFML/Graphics.hpp>
#include "gamestate.h"
#include <array>


class Background
{
    public:
        Background(sf::Vector2u dimensionsJeu);

        void update(sf::Time elapsedTime);
        void draw(GameEngine* shootTheAliens);
    private:
        sf::Vector2u m_gameDimensions;

        std::array<sf::Texture, 3> m_backgroundTexture;
        std::array<sf::Sprite, 3> m_backgroundSprite;

        sf::Time m_backgroundElapsedTime;
};

#endif // BACKGROUND_H
