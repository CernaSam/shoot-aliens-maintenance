#include "fond.h"

Fond::Fond(sf::Vector2u dimensionsJeu)
{
    m_gameDimensions = dimensionsJeu;
    m_backgroudTexture = new sf::Texture[3];
    m_backgroundSprite = new sf::Sprite[3];
    m_backgroudTexture[0].loadFromFile("ressources/images/fond1.png");
    m_backgroudTexture[1].loadFromFile("ressources/images/fond2.png");
    m_backgroudTexture[2].loadFromFile("ressources/images/fond3.png");

    m_backgroudTexture[0].setRepeated(true);
    m_backgroudTexture[1].setRepeated(true);
    m_backgroudTexture[2].setRepeated(true);

    m_backgroundSprite[0].setTexture(m_backgroudTexture[0]);
    m_backgroundSprite[0].setTextureRect(sf::IntRect(0, 0, m_gameDimensions.x, m_backgroudTexture[0].getSize().y * 2));
    m_backgroundSprite[1].setTexture(m_backgroudTexture[1]);
    m_backgroundSprite[1].setTextureRect(sf::IntRect(0, 0, m_gameDimensions.x, m_backgroudTexture[1].getSize().y * 2));
    m_backgroundSprite[2].setTexture(m_backgroudTexture[2]);
    m_backgroundSprite[2].setTextureRect(sf::IntRect(0, 0, m_gameDimensions.x, m_backgroudTexture[2].getSize().y * 2));

    m_backgroundSprite[0].setPosition(0, (int)-m_backgroudTexture[0].getSize().y);
    m_backgroundSprite[1].setPosition(0, (int)-m_backgroudTexture[1].getSize().y);
    m_backgroundSprite[2].setPosition(0, (int)-m_backgroudTexture[2].getSize().y);
}

Fond::~Fond()
{
    delete m_backgroudTexture;
    delete m_backgroundSprite;
}

void Fond::update(sf::Time elapsedTime)
{
    m_backgroundSprite[0].move(0, 30 * (elapsedTime.asSeconds() - m_backgroundElapsedTime.asSeconds()));
    m_backgroundSprite[1].move(0, 70 * (elapsedTime.asSeconds() - m_backgroundElapsedTime.asSeconds()));
    m_backgroundSprite[2].move(0, 150 * (elapsedTime.asSeconds() - m_backgroundElapsedTime.asSeconds()));

    if(m_backgroundSprite[0].getPosition().y >= 0)
        m_backgroundSprite[0].setPosition(0, (int)-m_backgroudTexture[0].getSize().y);

    if(m_backgroundSprite[1].getPosition().y >= 0)
       m_backgroundSprite[1].setPosition(0, (int)-m_backgroudTexture[1].getSize().y);

    if(m_backgroundSprite[2].getPosition().y >= 0)
        m_backgroundSprite[2].setPosition(0, (int)-m_backgroudTexture[2].getSize().y);
    m_backgroundElapsedTime = elapsedTime;
}

void Fond::draw(GameEngine* shootTheAliens)
{
    sf::RenderTexture m_fond;
    m_fond.create(m_gameDimensions.x, m_gameDimensions.y);

    m_fond.draw(m_backgroundSprite[0]);
    m_fond.draw(m_backgroundSprite[1]);
    m_fond.draw(m_backgroundSprite[2]);
    m_fond.display();

    sf::Sprite img;
    img.setTexture(m_fond.getTexture());
    shootTheAliens->getFenetre()->draw(img);
}
