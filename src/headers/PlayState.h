#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include "Game.h"
#include "State.h"
#include "Entity.h"
#include "Goal.h"
#include "Team.h"
#include "Formation.h"

class PlayState : public State {
public:
    PlayState(Game* game, const std::string& team, const std::string& team2, unsigned short receive_port, unsigned short send_port, std::string ip, bool turn);
    ~PlayState();

    void update();
    void render(sf::RenderWindow& window);
    void keyboard(sf::Keyboard::Key& key);
    void mouse(sf::Event::MouseButtonEvent& event);
    void resetBall();
    void isGoal(Goal &goal1 , Goal &goal2);
private:

  Goal *m_goal_home;
  Goal *m_goal_away;
  Team *m_team1;
  Team *m_team2;

  Entity* m_ball;

  sf::Vector2u score;
  sf::Text m_score_home;
  sf::Text m_separator;
  sf::Text m_score_away;
  sf::Sprite m_field;
  sf::Sound m_whistle;

  unsigned short m_receive_port;
  unsigned short m_send_port;
};

#endif
