#ifndef STATE_H_
#define STATE_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourceManager.h"
#include "consts.h"

class Game;

class State
{
public:
    virtual ~State();

    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void keyboard(sf::Keyboard::Key& key) = 0; // Metoda za input sa tastature
    virtual void mouse(sf::Event::MouseButtonEvent& event) = 0; // Metoda za input sa tastature
protected:
    State(Game* game);
    Game* p_game;
    sf::Text m_backText;
};

#endif
