#include "headers/Team.h"

Team::Team(const sf::Texture& texture, Entity* ball, Goal *goal,Goal *goal2, unsigned int port_listen, unsigned int port_send, const std::string& ip, bool turn)
  : m_client(port_listen,ip)
  , m_port_send(port_send)
  , m_turn(turn)
{


  for (size_t i = 0; i < 3; i++) {
    m_players.push_back(new Entity(0, 0, texture, 0, 0));
  }

  // lopta
  m_ball = ball;
  //goal
  m_goal1 = goal;
  m_goal2 = goal2;


  // kada nije selektovan nijedan igrac, bice vrednost veca od velicine niza
  m_selected = m_players.size() + 1;
}
Team::~Team() {
    for (size_t i = 0; i < m_players.size(); i++) {
      delete m_players[i];
    }
    delete m_formation;
}
void Team::update(){

    receiveMessage();
    for (size_t i = 0; i < m_players.size(); i++) {

      m_players[i]->checkEntityCollision(*m_ball); // kolizija pojedinca sa loptom
      m_players[i]->checkGoalCollision(*m_goal1, *m_goal2);
      collisionTeammates(i); // kolizija sa saigracima
      collisionEnemy(i);

      m_players[i]->update();
    }
}

void Team::render(sf::RenderWindow& window) {
    for (size_t i = 0; i < m_players.size(); i++) {
      m_players[i]->render(window);
    }
  }
Entity& Team::player(size_t index) const {
    return *m_players[index];
}
void Team::collisionTeammates(size_t index) {
    size_t size = m_players.size();

    for (size_t i = index+1; i < size; i++) {
      m_players[index]->checkEntityCollision(*m_players[i]);
    }
}

void Team::mouse(sf::Event::MouseButtonEvent& event) {
  if (event.button == sf::Mouse::Button::Left) {

    if (m_selected > m_players.size()) {
      findSelectedPlayer(event.x, event.y);
    } else {

      double hit_x = (m_players[m_selected]->position().x - event.x)/10;
      double hit_y = (m_players[m_selected]->position().y - event.y)/10;

      // hit_max regulise koliki je maksimalno jak udarac
      const double hit_max = 20;
      hit_x = ((std::abs(hit_x) > hit_max) ? (hit_x > 0 ? hit_max : - hit_max) : hit_x);
      hit_y = ((std::abs(hit_y) > hit_max) ? (hit_y > 0 ? hit_max : - hit_max) : hit_y);

      m_turn = false;
      m_client.send(m_port_send,m_selected,hit_x,hit_y);
      m_players[m_selected]->setDirection(hit_x,hit_y);

      std::cout << m_selected << " " << hit_x << " " << hit_y << std::endl;

      m_selected = m_players.size() + 1;
    };
  }
}
void Team::findSelectedPlayer(int x, int y) {
  for (size_t i = 0; i < m_players.size(); i++) {
    Entity* p = m_players[i];

    if (x >= p->position().x-p->radius() && x <= p->position().x+p->radius()) {
      if (y >= p->position().y-p->radius() && y <= p->position().y+p->radius()) {
        m_selected = i;
        return;
      }
    }
  }
}
void Team::reset(){

    // centralni igrac
    m_players[0]->setPosition( m_formation->center().x  , m_formation->center().y);
    m_players[0]->setDirection(0,0);
    // levi igrac
    m_players[1]->setPosition( m_formation->left().x  , m_formation->left().y);
    m_players[1]->setDirection(0,0);
    //desni igrac
    m_players[2]->setPosition( m_formation->right().x  , m_formation->right().y);
    m_players[2]->setDirection(0,0);

}

void Team::receiveMessage()
{
  if (m_client.receive(m_enemy->m_players))
    m_turn = true;
}

void Team::setFormation(Formation* formation) {
  m_formation = formation;
  reset();
}

Team& Team::enemy() {
  return *m_enemy;
}

void Team::setEnemy(Team* other){
  m_enemy = other;
}
void Team::collisionEnemy(size_t index) {
    size_t size = m_players.size();

    for (size_t i = 0; i < size; i++) {
      m_players[index]->checkEntityCollision(m_enemy->player(i));
    }
}
bool Team::stoped(){
    size_t size = m_players.size();

    for (size_t i = 0; i < size; i++) {
      if(abs(m_players[i]->direction().x) > 0.0001 || abs(m_players[i]->direction().y) > 0.0001 ){
        return false;
      }
    }
    return true;
}

bool Team::turn()
{
  return m_turn;
}
