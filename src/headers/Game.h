#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "consts.h"
#include "ResourceManager.h"
#include "PlayState.h"
#include "MenuState.h"
#include "TeamState.h"

#include "State.h"

class Game {
public:
	Game();
	~Game();
	void run();

	// ove dve metode, a bice ih vise, vracaju menadzere resursa
	const TextureManager* textures() const;
	const FontManager* fonts() const;
	const SoundBufferManager& sounds() const;
	void changeState(State* state); // Metoda koja dozvoljava promenu iz jednog u drugi State
	void exit();
private:
	void proccessEvents();
	void update();
	void render();
	void start();
	void checkForUpdate();
	sf::RenderWindow m_gameWindow;
	
	TextureManager m_textures;
	FontManager m_fonts;
	SoundBufferManager m_sounds;

	State* m_currState; // Ovo je pokazivac na trenutni State (na pocetku MenuState)
	sf::Clock m_clock;
};
#endif
