#ifndef MENU_H
#define JEU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "gameengine.h"
#include "gamestate.h"
#include "player.h"
#include "alien.h"
#include "projectile.h"
#include "explosion.h"
#include "fond.h"
#include "soundmanager.h"


class Game : public GameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* shootTheAliens);
	void Update(GameEngine* shootTheAliens);
	void Draw(GameEngine* shootTheAliens);

private:
	sf::View m_mainView;
	sf::Vector2u m_windowDimensions;
	sf::Vector2u m_gameDimensions;
	int m_score;
    int m_scoreFinal;
    int m_highscore;
    bool m_gameOver;

    sf::Font m_fonts;
    sf::Text m_start;
    sf::Text m_texteScore;
    sf::Text m_texteScorePrecedent;
    sf::Text m_texteHighscore;
    sf::Text m_version;
    sf::Text m_textePause;
    sf::FloatRect m_fontsm_bounds;

    bool m_chargementFini;
    bool m_isPLaying;
    bool m_isPaused;
    float m_difficulty;
    int m_level; // Float pour �viter les r�sultat de division incoh�rents
                    // A voir si possible de remettre en int sans bug
    int m_previousLevelDeaths;
    int m_deaths;
    int m_aliensTotal;

    sf::Clock mainClock;
    sf::Time elapsedTime;
    sf::Time pausedDuration;
    sf::Time m_pauseStartTime;
    sf::Time tempsPasseNiveau;
    sf::Time tempsPassePop;

    std::vector<Alien> m_alien;
    sf::Texture m_alienTexture;
    std::vector<sf::Sprite> m_alienSprite;
    sf::Vector2u m_alienSize;

    std::vector<Projectile> m_tir;
    sf::Texture m_projectileTexture;
    std::vector<sf::Sprite> m_projectileSprite;
    sf::Vector2u m_projectileSize;

    std::vector<Explosion> m_explosion;
    sf::Texture m_explosionTexture;
    std::vector<sf::Sprite> m_explosionsSprite;

    Player m_joueur;
    sf::Texture m_playerTexture;
    sf::Sprite m_playerSprite;
    sf::Vector2u m_playerSize;
    int m_playerMovementDirection;

    Fond *m_fond = NULL;
    sf::RectangleShape m_pauseBackground;

    ostringstream screenshotFilename;
    time_t timer;
    int randomValue;
};

#endif
