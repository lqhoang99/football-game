#ifndef TEAM_H_
#define TEAM_H_

#include "Entity.h"
#include "Formation.h"
#include "consts.h"
#include "client.h"
#include <vector>

class Team {
public:
    Team(const sf::Texture& texture, Entity* ball, Goal *goal,Goal *goal2, unsigned int port_listen, unsigned int port_send, const std::string& ip, bool turn);
    ~Team();
    void render(sf::RenderWindow& window);
    void update();

    void mouse(sf::Event::MouseButtonEvent& event);

    void reset();
    void receiveMessage();
    void setFormation(Formation* formation);

    Team& enemy();
    void setEnemy(Team* other);

    Entity& player(size_t index) const;
    client m_client;

    bool stoped();
    bool turn();

private:
    std::vector<Entity*> m_players;
    Entity* m_ball;
    Goal *m_goal1;
    Goal *m_goal2;
    Formation *m_formation;
    Team *m_enemy;
    size_t m_selected;
    unsigned int m_port_send;
    bool m_turn;

    void collisionTeammates(size_t index);
    void collisionEnemy(size_t index);
    void findSelectedPlayer(int x, int y);
};

#endif
