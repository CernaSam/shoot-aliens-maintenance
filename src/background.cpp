#include "background.h"

Background::Background(sf::Vector2u dimensionsJeu)
{
    m_gameDimensions = dimensionsJeu;
    m_backgroundTexture[0].loadFromFile("ressources/images/background1.png");
    m_backgroundTexture[1].loadFromFile("ressources/images/background2.png");
    m_backgroundTexture[2].loadFromFile("ressources/images/background3.png");

    m_backgroundTexture[0].setRepeated(true);
    m_backgroundTexture[1].setRepeated(true);
    m_backgroundTexture[2].setRepeated(true);

    m_backgroundSprite[0].setTexture(m_backgroundTexture[0]);
    m_backgroundSprite[0].setTextureRect(sf::IntRect(0, 0, m_gameDimensions.x, m_backgroundTexture[0].getSize().y * 2));
    m_backgroundSprite[1].setTexture(m_backgroundTexture[1]);
    m_backgroundSprite[1].setTextureRect(sf::IntRect(0, 0, m_gameDimensions.x, m_backgroundTexture[1].getSize().y * 2));
    m_backgroundSprite[2].setTexture(m_backgroundTexture[2]);
    m_backgroundSprite[2].setTextureRect(sf::IntRect(0, 0, m_gameDimensions.x, m_backgroundTexture[2].getSize().y * 2));

    m_backgroundSprite[0].setPosition(0, (int)-m_backgroundTexture[0].getSize().y);
    m_backgroundSprite[1].setPosition(0, (int)-m_backgroundTexture[1].getSize().y);
    m_backgroundSprite[2].setPosition(0, (int)-m_backgroundTexture[2].getSize().y);
}

void Background::update(sf::Time elapsedTime)
{
    m_backgroundSprite[0].move(0, 30 * (elapsedTime.asSeconds() - m_backgroundElapsedTime.asSeconds()));
    m_backgroundSprite[1].move(0, 70 * (elapsedTime.asSeconds() - m_backgroundElapsedTime.asSeconds()));
    m_backgroundSprite[2].move(0, 150 * (elapsedTime.asSeconds() - m_backgroundElapsedTime.asSeconds()));

    if(m_backgroundSprite[0].getPosition().y >= 0)
        m_backgroundSprite[0].setPosition(0, (int)-m_backgroundTexture[0].getSize().y);

    if(m_backgroundSprite[1].getPosition().y >= 0)
       m_backgroundSprite[1].setPosition(0, (int)-m_backgroundTexture[1].getSize().y);

    if(m_backgroundSprite[2].getPosition().y >= 0)
        m_backgroundSprite[2].setPosition(0, (int)-m_backgroundTexture[2].getSize().y);
    m_backgroundElapsedTime = elapsedTime;
}

void Background::draw(GameEngine* shootTheAliens)
{
    sf::RenderTexture m_background;
    m_background.create(m_gameDimensions.x, m_gameDimensions.y);

    m_background.draw(m_backgroundSprite[0]);
    m_background.draw(m_backgroundSprite[1]);
    m_background.draw(m_backgroundSprite[2]);
    m_background.display();

    sf::Sprite img;
    img.setTexture(m_background.getTexture());
    shootTheAliens->getFenetre()->draw(img);
}
