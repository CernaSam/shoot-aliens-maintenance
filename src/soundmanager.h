#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <map>
#include <SFML/Audio.hpp>
#include "ship.h"

enum Sons {TIR, EXPLOSION};

class SoundManager
{
    public:
        SoundManager();
        static SoundManager *getInstance()
        {
            if (SoundManager::m_singleton == NULL)
            {
                SoundManager::m_singleton = new SoundManager;
            }
            return SoundManager::m_singleton;
        }

        static void kill()
        {
            if (SoundManager::m_singleton != NULL)
            {
                delete SoundManager::m_singleton;
                SoundManager::m_singleton = NULL;
            }
        }
        void cleanupFinishedSounds();
        void pause(bool pause);
        void playPause(bool pause, sf::Sound *son);
        void playSound(Sons type);
        void playStrafeSound(bool stop, sf::Time elapsedTime, bool stopImmediately = false);
        void playEngineSound(int ownerId, bool stop);
        void fx(sf::Time elapsedTime);
    protected:
    private:
        static SoundManager *m_singleton;
        sf::Music m_musique;
        std::deque<sf::Sound> m_son;
        std::map<int, std::deque<sf::Sound> > m_son_reacteur;
        std::array<sf::Sound, 2> m_son_strafe;
        std::array<sf::Sound, 4> m_son_fx;

        int const m_nbrSonsTir = 3;
        std::array<sf::SoundBuffer, 3> m_buffer_tir;
        int const m_nbrSonsExplosion = 4;
        std::array<sf::SoundBuffer, 4> m_buffer_explosion;
        int const m_nbrSonsReacteur = 4;
        std::array<sf::SoundBuffer, 4> m_buffer_reacteur;
        int const m_nbrSonsStrafe = 2;
        std::array<sf::SoundBuffer, 2> m_buffer_strafe;
        int const m_nbrFX = 4;
        std::array<sf::SoundBuffer, 4> m_buffer_fx;

        unsigned int m_volumeMusique, m_volumeFX, m_volumeTir, m_volumeExplosion, m_volumeReacteur, m_volumeStrafe;
        float m_volume, m_volumeBruitages;

        int tir;
        float m_vitesseAttenuationStrafe;
        sf::Time m_lastFadeTime;
        sf::Time m_lastEffectTime;
};

#endif // SOUNDMANAGER_H
