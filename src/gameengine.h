#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

using namespace std;

class GameState;

class GameEngine
{
public:

	void Init(const char* titre, int largeur, int hauteur);

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() {return m_running;}
	void Quit() {m_running = false;}

	std::shared_ptr<sf::RenderWindow> getFenetre() { return m_fenetre; }

private:
	//La pile d'�tats
	vector<GameState*> states;

	bool m_running = true;
	bool m_fullscreen;
	std::shared_ptr<sf::RenderWindow> m_fenetre;
};

#endif
