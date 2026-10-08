#include "game.h"

enum Directions
{
    IMMOBILE, GAUCHE, DROITE
};

struct AABB
{
  float x;
  float y;
  int largeur;
  int hauteur;
};

bool Collision(AABB objet1, AABB objet2)
{
   if((objet2.x >= objet1.x + objet1.largeur)   // trop � droite
	|| (objet2.x + objet2.largeur <= objet1.x)  // trop � gauche
	|| (objet2.y >= objet1.y + objet1.hauteur)  // trop en bas
	|| (objet2.y + objet2.hauteur <= objet1.y)) // trop en haut
          return false;
   else
          return true;
}

void Game::Init()
{
    m_gameDimensions.x = 400;
    m_gameDimensions.y = 700;

    m_fond = new Fond(m_gameDimensions);

    m_isPLaying = false;
    m_isPaused = false;
    m_difficulty = 0.5;
    m_level = 1;
    m_deaths = 0;
    m_aliensTotal = 0;
    m_score = 0;
    m_scoreFinal = 0;
    m_highscore = 0;
    m_gameOver = false;

    m_fonts.loadFromFile("ressources/bnmachine.ttf");
    m_start.setFont(m_fonts);
    m_start.setString("I Wanna Kill Aliens !");
    m_start.setCharacterSize(32);
    m_start.setColor(sf::Color::Red);
    m_fontsm_bounds = m_start.getLocalBounds();
    m_start.setOrigin(m_fontsm_bounds.width/2, m_fontsm_bounds.height/2);

    m_version.setFont(m_fonts);
    m_version.setString("1.0.0 Legacy");
    m_version.setCharacterSize(13);
    m_version.setColor(sf::Color(255, 255, 255, 100));

    m_texteScore.setFont(m_fonts);
    m_texteScore.setCharacterSize(42);
    m_texteScore.setColor(sf::Color::White);

    m_texteScorePrecedent.setFont(m_fonts);
    m_texteScorePrecedent.setCharacterSize(32);
    m_texteScorePrecedent.setColor(sf::Color::White);

    m_texteHighscore.setFont(m_fonts);
    m_texteHighscore.setCharacterSize(32);
    m_texteHighscore.setColor(sf::Color::Yellow);

    m_textePause.setFont(m_fonts);
    m_textePause.setString("Pause");
    m_textePause.setCharacterSize(50);
    m_textePause.setColor(sf::Color::White);

    m_playerTexture.loadFromFile("ressources/images/joueur.png");
    m_alienTexture.loadFromFile("ressources/images/alien.png");
    m_projectileTexture.loadFromFile("ressources/images/tir.png");
    m_explosionTexture.loadFromFile("ressources/images/explosion.png");

    m_projectileSize = m_projectileTexture.getSize();
    m_playerSize = Ship::get_size(m_playerTexture.getSize());
    m_alienSize = Ship::get_size(m_alienTexture.getSize());
}

void Game::Cleanup()
{
    delete m_fond;
}

void Game::Pause()
{
}

void Game::Resume()
{
}

void Game::HandleEvents(GameEngine* shootTheAliens)
{
    // On inspecte tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente it�ration
    sf::Event event;
    while(shootTheAliens->getFenetre()->pollEvent(event))
    {
        //Ev�nement "fermeture demand�e" : on ferme la fen�tre
        if(event.type == sf::Event::Closed)
        {
            shootTheAliens->getFenetre()->close();
            shootTheAliens->Quit();
        }

         //On attrape les �v�nements de redimensionnement
        if(event.type == sf::Event::Resized)
        {
            //On met � jour la vue, avec la nouvelle taille de la fen�tre
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            shootTheAliens->getFenetre()->setView(sf::View(visibleArea));
        }

        //Commencer, Pause, Quitter
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Space && m_isPLaying == false)
            {
                m_isPLaying = true;
                SoundManager::getInstance()->playEngineSound(m_joueur.get_id(), false);
            }

            if(event.key.code == sf::Keyboard::P && m_isPLaying)
            {
                if(m_isPaused)
                {
                    pausedDuration += mainClock.getElapsedTime() - m_pauseStartTime;
                    SoundManager::getInstance()->pause(false);
                }else{
                    m_pauseStartTime = mainClock.getElapsedTime();
                    SoundManager::getInstance()->pause(true);
                }
                m_isPaused = (m_isPaused) ? false : true;
            }
            if(event.key.code == sf::Keyboard::C)
            {
                if(!(m_isPaused))
                {
                    m_pauseStartTime = mainClock.getElapsedTime();
                    m_isPaused = true;
                }
                timer = time(NULL);
                randomValue = rand()%(90)+10;
                screenshotFilename << "screens/" << timer << "_" << randomValue << ".png";
                shootTheAliens->getFenetre()->capture().saveToFile(screenshotFilename.str());
                screenshotFilename.str("");
                if(m_isPaused)
                {
                    pausedDuration += mainClock.getElapsedTime() - m_pauseStartTime;
                    m_isPaused = false;
                }
            }
            if(event.key.code == sf::Keyboard::Q)
            {
                shootTheAliens->getFenetre()->close();
                shootTheAliens->Quit();
            }
        }

        if(m_isPLaying)
        {
            //D�placement du joueur
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                m_playerMovementDirection = GAUCHE;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                m_playerMovementDirection = DROITE;
            }else{
                m_playerMovementDirection = IMMOBILE;
            }
        }
    }
}

void Game::Update(GameEngine* shootTheAliens)
{
    m_windowDimensions = shootTheAliens->getFenetre()->getSize();
    m_fontsm_bounds = m_version.getLocalBounds();
    m_version.setPosition(m_fontsm_bounds.width - 67, m_gameDimensions.y - m_fontsm_bounds.height - 7);

    if(m_isPLaying)
    {
        if(m_isPaused)
        {
            m_fontsm_bounds = m_textePause.getLocalBounds();
            m_textePause.setPosition(m_gameDimensions.x - m_fontsm_bounds.width - 5, -5);
            m_textePause.setOrigin(m_fontsm_bounds.width/2, m_fontsm_bounds.height/2);
            m_textePause.setPosition(m_gameDimensions.x/2, m_gameDimensions.y/2);
            m_pauseBackground.setSize(sf::Vector2f(m_gameDimensions.x, m_gameDimensions.y));
            m_pauseBackground.setFillColor(sf::Color(0,15,31,127));
            SoundManager::getInstance()->playStrafeSound(false, mainClock.getElapsedTime() - pausedDuration, true);
        }else{
            m_fond->update(mainClock.getElapsedTime() - pausedDuration);
            SoundManager::getInstance()->fx(mainClock.getElapsedTime() - pausedDuration);
            //Niveaux
            elapsedTime = mainClock.getElapsedTime() - pausedDuration;
            if(elapsedTime.asSeconds() - tempsPasseNiveau.asSeconds() > 5 / m_difficulty)
            {
                tempsPasseNiveau = elapsedTime;
                m_level++;
            }

            //Score
            stringstream convert;
            convert << m_score;
            string score = convert.str();
            m_texteScore.setString(score);
            m_fontsm_bounds = m_texteScore.getLocalBounds();
            m_texteScore.setPosition(m_gameDimensions.x - m_fontsm_bounds.width - 5, -5);


            //D�placements du joueur
            m_joueur.move(mainClock.getElapsedTime() - pausedDuration, m_playerMovementDirection);
            m_playerSprite.setPosition(m_joueur.get_position());
            if(m_playerMovementDirection == GAUCHE || m_playerMovementDirection == DROITE) SoundManager::getInstance()->playStrafeSound(false, mainClock.getElapsedTime() - pausedDuration);
            else SoundManager::getInstance()->playStrafeSound(true, mainClock.getElapsedTime() - pausedDuration);
            //Projectile du joueur
            if(m_joueur.shoot(mainClock.getElapsedTime() - pausedDuration))
            {
                m_tir.push_back(Projectile(mainClock.getElapsedTime() - pausedDuration, false, 0, m_joueur.get_position(), m_playerSize, m_projectileSize));
                m_projectileSprite.push_back(sf::Sprite());
                m_projectileSprite.back().setTexture(m_projectileTexture);
                m_projectileSprite.back().setPosition(m_tir.back().get_position());
            }

            //Pop
            elapsedTime = mainClock.getElapsedTime() - pausedDuration;
            if(elapsedTime.asSeconds() - tempsPassePop.asSeconds() > 0.5 / (m_difficulty + float(m_level) / 5) || m_alien.size() == 0)
            {
                tempsPassePop = elapsedTime;
                m_alien.push_back(Alien(mainClock.getElapsedTime() - pausedDuration, m_level, m_difficulty, m_gameDimensions, m_alienSize));
                m_alienSprite.push_back(sf::Sprite());
                m_alienSprite.back().setTexture(m_alienTexture);
                m_alienSprite.back().setPosition(sf::Vector2f(m_alien.back().get_position()));
                m_aliensTotal++;
            }
            //Alien dans l'�cran
            sf::Vector2f posAlien = m_alien.front().get_position();
            if(posAlien.y < m_gameDimensions.y)
            {
                //Actions
                for(unsigned int i = 0 ; i < m_alien.size() && m_alien.size() > 0 ; i++)
                {
                    //D�placements alien
                    m_alienSprite[i].setPosition(sf::Vector2f(m_alien[i].get_position()));
                    m_alien[i].moveForward(mainClock.getElapsedTime() - pausedDuration);
                    //Projectile des aliens
                    if(m_alien[i].is_alive() == true && m_alien[i].shoot(mainClock.getElapsedTime() - pausedDuration))
                    {
                        m_tir.push_back(Projectile(mainClock.getElapsedTime() - pausedDuration, true, m_alien[i].get_speed(), m_alien[i].get_position(), m_alienSize, m_projectileSize));
                        m_projectileSprite.push_back(sf::Sprite());
                        m_projectileSprite.back().setTexture(m_projectileTexture);
                        m_projectileSprite.back().setPosition(m_tir.back().get_position());
                    }
                }
            }else{
                //Destruction de l'alien sorti de l'�cran
                m_alien.erase(m_alien.begin());
                m_alienSprite.erase(m_alienSprite.begin());
            }

            //D�placement tirs
            for(unsigned int i = 0 ; i < m_tir.size() && m_tir.size() > 0 ; i++)
            {
                m_tir[i].moveForward(mainClock.getElapsedTime() - pausedDuration);
                m_projectileSprite[i].setPosition(m_tir[i].get_position());
            }
            //Destruction des tirs sortis de l'�cran
            if(m_tir.size() > 1)
            {
                sf::Vector2f posTir = m_tir.front().get_position();
                while(posTir.y > m_gameDimensions.y || posTir.y < -100)
                {
                    m_tir.erase(m_tir.begin());
                    m_projectileSprite.erase(m_projectileSprite.begin());
                    if(m_tir.size() > 0)
                    {
                        posTir = m_tir.front().get_position();
                    }
                }
            }

            //Tests de collision
            sf::Vector2f posJoueur = m_joueur.get_position();
            AABB aabbJoueur = {posJoueur.x, posJoueur.y, m_playerSize.x, m_playerSize.y};
            sf::Vector2f posTir;

            vector<Projectile>::iterator iteratorTir;
            vector<Alien>::iterator iteratorAlien;
            vector<sf::Sprite>::iterator iteratorSprite;

            //Aliens-Player
            for(unsigned int i=0 ; i < m_alien.size() ; i++)
            {
                posAlien = m_alien[i].get_position();
                AABB aabbAlien = {posAlien.x, posAlien.y, m_alienSize.x, m_alienSize.y};
                if(m_alien[i].is_alive() == true && Collision(aabbJoueur, aabbAlien))
                {
                    m_joueur.set_alive(mainClock.getElapsedTime() - pausedDuration, false);
                    m_alien[i].set_alive(mainClock.getElapsedTime() - pausedDuration, false);
                }
            }

            //Tirs
            for(unsigned int i=0 ; i < m_tir.size() ; i++)
            {
                //Tirs-Player
                if(m_tir[i].get_enemy())
                {
                    posTir = m_tir[i].get_position();
                    AABB aabbTir = {posTir.x, posTir.y, m_projectileSize.x, m_projectileSize.y};
                    if(m_joueur.is_alive() == true && Collision(aabbJoueur, aabbTir)) m_joueur.set_alive(mainClock.getElapsedTime() - pausedDuration, false);
                } //Tirs-Aliens
                else if(!(m_tir[i].get_enemy()))
                {
                    posTir = m_tir[i].get_position();
                    AABB aabbTir = {posTir.x, posTir.y, m_projectileSize.x, m_projectileSize.y};
                    for(unsigned int a=0 ; a < m_alien.size() ; a++)
                    {
                        posAlien = m_alien[a].get_position();
                        AABB aabbAlien = {posAlien.x, posAlien.y, m_alienSize.x, m_alienSize.y};
                        if(m_alien[a].is_alive() == true && Collision(aabbTir, aabbAlien))
                        {
                            m_score++;
                            m_alien[a].set_alive(mainClock.getElapsedTime() - pausedDuration, false);

                            iteratorTir = m_tir.begin() + i;
                            m_tir.erase(iteratorTir);
                            iteratorSprite = m_projectileSprite.begin() + i;
                            m_projectileSprite.erase(iteratorSprite);
                        }
                    }
                }
            }
            //Mort des vaisseaux
            //Aliens
            for(unsigned int i=0 ; i < m_alien.size() ; i++)
            {
                if(m_alien[i].is_alive() == false)
                {
                    if(m_alien[i].get_opacity() == 255)
                    {
                        m_explosion.push_back(Explosion(mainClock.getElapsedTime() - pausedDuration, m_alien[i].get_position(), m_alienSize, m_explosionTexture.getSize().y, m_alien[i].get_speed()));
                        m_explosionsSprite.push_back(sf::Sprite());
                        m_explosionsSprite.back().setTexture(m_explosionTexture);
                        m_explosionsSprite.back().setTextureRect(sf::IntRect(0, 0, 100, 100));
                        m_explosionsSprite.back().setPosition(m_explosion.back().get_position());
                    }
                    m_alien[i].die(mainClock.getElapsedTime() - pausedDuration);
                    m_alienSprite[i].setColor(sf::Color(255, 255, 255, m_alien[i].get_opacity()));
                    if(m_alien[i].get_opacity() == 0)
                    {
                        iteratorAlien = m_alien.begin() + i;
                        m_alien.erase(iteratorAlien);
                        iteratorSprite = m_alienSprite.begin() + i;
                        m_alienSprite.erase(iteratorSprite);
                    }
                }
            }
            //Player
            if(m_joueur.is_alive() == false)
            {
                if(m_joueur.get_opacity() == 255)
                {
                    m_explosion.push_back(Explosion(mainClock.getElapsedTime() - pausedDuration, m_joueur.get_position(), m_playerSize, m_explosionTexture.getSize().y, 0));
                    m_explosionsSprite.push_back(sf::Sprite());
                    m_explosionsSprite.back().setTexture(m_explosionTexture);
                    m_explosionsSprite.back().setTextureRect(sf::IntRect(0, 0, 100, 100));
                    m_explosionsSprite.back().setPosition(m_explosion.back().get_position());
                }
                m_joueur.die(mainClock.getElapsedTime() - pausedDuration);
                m_playerSprite.setColor(sf::Color(255, 255, 255, m_joueur.get_opacity()));
                if(m_joueur.get_opacity() == 0)
                {
                    m_scoreFinal = m_score;
                    m_gameOver = true;
                    m_isPLaying = false;
                }
            }
            //Gestion des explosions
            if(m_explosion.size() > 0)
            {
                for(unsigned int i = 0 ; i < m_explosion.size() ; i++)
                {
                    m_explosion[i].changeState(mainClock.getElapsedTime() - pausedDuration);
                    m_explosionsSprite[i].setTextureRect(sf::IntRect(100*m_explosion[i].get_state(), 0, 100, 100));
                    m_explosion[i].moveForward(mainClock.getElapsedTime() - pausedDuration);
                    m_explosionsSprite[i].setPosition(m_explosion[i].get_position());
                }
                if(m_explosion.front().get_state() >= 9)
                {
                    m_explosion.erase(m_explosion.begin());
                    m_explosionsSprite.erase(m_explosionsSprite.begin());
                }
            }
            //Animation des vaisseaux
            m_playerSprite.setTextureRect(sf::IntRect(0, 0, m_playerSize.x, m_playerSize.y));
            m_joueur.changeState(mainClock.getElapsedTime() - pausedDuration);
            m_playerSprite.setTextureRect(sf::IntRect(m_playerSize.x*m_joueur.get_state(), 0, m_playerSize.x, m_playerSize.y));
            for(unsigned int i = 0 ; i < m_alien.size() ; i++)
            {
                m_alienSprite[i].setTextureRect(sf::IntRect(0, 0, m_alienSize.x, m_alienSize.y));
                m_alien[i].changeState(mainClock.getElapsedTime() - pausedDuration);
                m_alienSprite[i].setTextureRect(sf::IntRect(m_alienSize.x*m_alien[i].get_state(), 0, m_alienSize.x, m_alienSize.y));
            }
        }
    }else{
        m_fond->update(mainClock.getElapsedTime() - pausedDuration);
        m_start.setPosition(m_gameDimensions.x/2, m_gameDimensions.y/3);

        //Ouverture des highscores
        ifstream highscore("highscore", ios::in);
        if(highscore)
        {
            highscore >> m_highscore;
            highscore.close();
        }

        if(m_gameOver)
        {
            //On coupe le son des strafe
            SoundManager::getInstance()->playStrafeSound(false, mainClock.getElapsedTime() - pausedDuration, true);
            //Enregistrement du highscore
            if(m_score > m_highscore)
            {
                m_highscore = m_score;
                ofstream highscore("highscore", ios::out | ios::trunc);
                if(highscore)
                {
                    highscore << m_scoreFinal;
                    highscore.close();
                }
            }
            //Enregistrement des performances
            ofstream historyFile("history", ios::out | ios::app);
            if(historyFile)
            {
                float killRatio;
                (m_aliensTotal > 0) ? (killRatio = (float)m_scoreFinal / (float)m_aliensTotal) : (killRatio = 0);
                historyFile << m_level << ";" << m_scoreFinal << ";" << m_aliensTotal << ";" << killRatio << "\n";
                historyFile.close();
            }

            //R�initialisation pour une nouvelle partie
            m_score = 0;
            m_level = 1;
            m_previousLevelDeaths = 0;
            m_deaths = 0;
            m_aliensTotal = 0;
            tempsPasseNiveau = mainClock.getElapsedTime() - pausedDuration;
            tempsPassePop = mainClock.getElapsedTime() - pausedDuration;
            m_alien.clear();
            m_alienSprite.clear();
            m_tir.clear();
            m_projectileSprite.clear();
            m_explosion.clear();
            m_explosionsSprite.clear();
            m_gameOver = false;
            m_joueur.set_alive(mainClock.getElapsedTime() - pausedDuration, true);
            m_joueur.set_opacity(255);
            m_playerSprite.setColor(sf::Color(255, 255, 255, 255));
        }

        //affichage du score et highscore
        string score = "Your score : ";
        stringstream convert;
        convert << m_scoreFinal;
        score += convert.str();
        convert.str("");
        m_texteScorePrecedent.setString(score);
        m_fontsm_bounds = m_texteScorePrecedent.getLocalBounds();
        m_texteScorePrecedent.setOrigin(m_fontsm_bounds.width/2, m_fontsm_bounds.height/2);
        m_texteScorePrecedent.setPosition(m_gameDimensions.x/2, m_gameDimensions.y/2);

        score = "Highscore : ";
        convert << m_highscore;
        score += convert.str();
        m_texteHighscore.setString(score);
        m_fontsm_bounds = m_texteHighscore.getLocalBounds();
        m_texteHighscore.setOrigin(m_fontsm_bounds.width/2, m_fontsm_bounds.height/2);
        m_texteHighscore.setPosition(m_gameDimensions.x/2, m_gameDimensions.y/3*2);

        m_playerSprite.setTexture(m_playerTexture);
        m_joueur.set_player(m_gameDimensions, sf::Vector2u(m_playerSize.x, m_playerSize.y));
    }

    m_mainView.reset(sf::FloatRect(0, 0, 400, 700));
    m_mainView.setSize(400, 700);
    sf::Vector2f facteurViewport;
    if((float)m_windowDimensions.x/m_windowDimensions.y < (float)m_gameDimensions.x/m_gameDimensions.y)
    {
        //largeur de fenetre petite
        facteurViewport.x = 1;
        facteurViewport.y = ((float)m_windowDimensions.x/m_windowDimensions.y)*((float)m_gameDimensions.y/m_gameDimensions.x);
        m_mainView.setViewport(sf::FloatRect(0, (float)(1-facteurViewport.y) / 2, facteurViewport.x, facteurViewport.y));
    }else{
        //largeur de fenetre grande
        facteurViewport.x = ((float)m_windowDimensions.y/m_windowDimensions.x)*((float)m_gameDimensions.x/m_gameDimensions.y);
        facteurViewport.y = 1;
        m_mainView.setViewport(sf::FloatRect((float)(1-facteurViewport.x)/2, 0, facteurViewport.x, facteurViewport.y));
    }

    SoundManager::getInstance()->cleanupFinishedSounds();
    shootTheAliens->getFenetre()->setView(m_mainView);
}

void Game::Draw(GameEngine* shootTheAliens)
{
    shootTheAliens->getFenetre()->clear(sf::Color::Black);

    m_fond->draw(shootTheAliens);

    if(m_isPLaying)
    {
        for(unsigned int i = 0 ; i < m_projectileSprite.size() ; i++)
        {
            shootTheAliens->getFenetre()->draw(m_projectileSprite[i]);
        }
        shootTheAliens->getFenetre()->draw(m_playerSprite);
        for(unsigned int i = 0 ; i < m_alienSprite.size() && m_alienSprite.size() > 0 ; i++)
        {
            shootTheAliens->getFenetre()->draw(m_alienSprite[i]);
        }
        for(unsigned int i = 0 ; i < m_explosionsSprite.size() && m_explosionsSprite.size() > 0 ; i++)
        {
            shootTheAliens->getFenetre()->draw(m_explosionsSprite[i]);
        }
        if(m_isPaused)
        {
            shootTheAliens->getFenetre()->draw(m_pauseBackground);
            shootTheAliens->getFenetre()->draw(m_textePause);
        }
        shootTheAliens->getFenetre()->draw(m_texteScore);
    }else{
        shootTheAliens->getFenetre()->draw(m_start);
        shootTheAliens->getFenetre()->draw(m_texteScorePrecedent);
        shootTheAliens->getFenetre()->draw(m_texteHighscore);
    }
    shootTheAliens->getFenetre()->draw(m_version);
    shootTheAliens->getFenetre()->display();
}
