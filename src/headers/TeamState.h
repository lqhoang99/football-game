#ifndef TEAMSTATE_H_
#define TEAMSTATE_H_

#include "Game.h"
#include "State.h"
#include "PlayState.h"
#include <vector>
#include <iostream>
#include "ClientConnection.h"

class TeamState : public State {

public:
    TeamState(Game* game);
    ~TeamState();

    void update();
    void render(sf::RenderWindow& window);
    void keyboard(sf::Keyboard::Key& key);
    void mouse(sf::Event::MouseButtonEvent& event);

private:
    std::vector<std::string> m_teams;
    
    sf::Sprite m_current, m_left, m_right;
    sf::Sprite m_background;
    sf::Sprite m_loadingImg;
    sf::Text m_teamName, m_message, m_waitmsg;
    sf::Vector2f m_currPos;
    
    int m_selected;
    bool m_loading;
    
    ClientConnection m_client;

    void setTeams();
};

#endif
