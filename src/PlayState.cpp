#include "headers/PlayState.h"

PlayState::PlayState(Game* game, const std::string& team, const std::string& team2, unsigned short receive_port, unsigned short send_port, std::string ip, bool turn)
    :State(game)
{
  m_ball = new Entity(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, game->textures()->get("ball"),0,0);

  m_goal_home = new Goal((WINDOW_WIDTH- GOAL_WIDTH)/2, 0, game->textures()->get("goal2"));
  m_goal_away = new Goal((WINDOW_WIDTH - GOAL_WIDTH)/2, WINDOW_HEIGHT - GOAL_HEIGHT , game->textures()->get("goal"));

  // Inicijalizacija prvog tima i povezivanje
  m_team1 = new Team(game->textures()->get(team), m_ball, m_goal_home,m_goal_away, receive_port, send_port, ip, turn);
  m_team1->setFormation(new Formation(120  , WINDOW_HEIGHT - 120, WINDOW_WIDTH -120 , WINDOW_HEIGHT - 120,  WINDOW_WIDTH/2  , WINDOW_HEIGHT - 250));

  // Inicijalizacija drugog tima i povezivanje
  m_team2 = new Team(game->textures()->get(team2), m_ball, m_goal_home,m_goal_away, receive_port, send_port, ip, !turn);
  m_team2->setFormation(new Formation(WINDOW_WIDTH-120, 120, 120, 120, WINDOW_WIDTH/2 , 250 ));

  m_team1->setEnemy(m_team2);
  m_team2->setEnemy(m_team1);

  m_field.setTexture(p_game->textures()->get("field"));
	m_field.setScale(0.677,0.625);


  score.x = 0;
  score.y = 0;

  m_score_home = sf::Text(std::to_string(score.x), p_game->fonts()->get("menu_font") , 40);
  m_score_home.setRotation(90);
  m_score_home.setPosition(WINDOW_WIDTH - 20 , WINDOW_HEIGHT/2.0 - (m_score_home.getGlobalBounds().height) - 15);

  m_separator = sf::Text(":", p_game->fonts()->get("menu_font") , 40 );
  m_separator.setRotation(90);
  m_separator.setPosition(WINDOW_WIDTH - 20 , WINDOW_HEIGHT/2.0 - (m_separator.getGlobalBounds().height)/2 );

  m_score_away = sf::Text( std::to_string(score.y), p_game->fonts()->get("menu_font") , 40);
  m_score_away.setRotation(90);
  m_score_away.setPosition(WINDOW_WIDTH - 20 , WINDOW_HEIGHT/2.0 + 15);

  m_whistle.setBuffer(p_game->sounds().get("whistle"));
  m_whistle.setVolume(70);
  m_whistle.play();


  // m_receive_port = receive_port;
  // m_send_port = send_port;
}
PlayState::~PlayState() {
  delete m_ball;

  delete m_goal_home;
  delete m_goal_away;
  delete m_team1;
  delete m_team2;
}
void PlayState::update() {

  m_team1->update();
  m_team2->update();
	m_ball->update();
  isGoal(*m_goal_home,*m_goal_away);

}
void PlayState::render(sf::RenderWindow& window) {

  window.draw(m_field);
  window.draw(m_separator);
  window.draw(m_score_home);
  window.draw(m_score_away);
	m_ball->render(window);
  m_team1->render(window);
  m_team2->render(window);
  m_goal_home->render(window);
  m_goal_away->render(window);
}
void PlayState::keyboard(sf::Keyboard::Key& key) {

}
void PlayState::mouse(sf::Event::MouseButtonEvent& event) {

  // ako je klikut igrac i svi saigraci su zaustavljeni onda moze da se igrac
  // treba dodati uslov i da je potez u toku ili tako nesto za mrezu
  if(m_team1->stoped() && m_team2->stoped() && m_team1->turn() == true){
    m_team1->mouse(event);
  }
}

void PlayState::isGoal(Goal &goal1 , Goal &goal2){
  if(int g = m_ball->isInGoal(goal1,goal2) ){
    if(g == 1) score.x += 1;
    if(g == 2) score.y += 1;

    m_score_home.setString(std::to_string(score.x));
    m_score_away.setString(std::to_string(score.y));

    m_team1->reset();
    m_team2->reset();
    resetBall();
    m_whistle.play();

  }
  m_ball->checkGoalCollision(goal1,goal2);
}
void PlayState::resetBall(){
  m_ball->setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
  m_ball->setDirection(0,0);
}
//m_serbian_chetnik->render(window);
