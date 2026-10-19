#include <SFML/Graphics.hpp>
#include "gameengine.h"
#include "gamestate.h"

void GameEngine::Init(const char* titre, int largeur, int hauteur)
{
    m_fenetre = std::make_shared<sf::RenderWindow>(sf::VideoMode(largeur, hauteur), titre);
}

void GameEngine::ChangeState(GameState* state)
{
	if(!states.empty())
    {
		states.pop_back();
	}

	states.push_back(state);
	states.back()->Init();
}

void GameEngine::PushState(GameState* state)
{
	if(!states.empty())
    {
		states.back()->Pause();
	}

	states.push_back(state);
	states.back()->Init();
}

void GameEngine::PopState()
{
	if (!states.empty())
    {
		states.pop_back();
	}

	if (!states.empty())
    {
		states.back()->Resume();
	}
}

void GameEngine::HandleEvents()
{
	states.back()->HandleEvents(this);
}

void GameEngine::Update()
{
	states.back()->Update(this);
}

void GameEngine::Draw()
{
	states.back()->Draw(this);
}
