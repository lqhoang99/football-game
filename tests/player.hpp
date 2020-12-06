#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "client.hpp"

class player
{
public:
  // player();

  player(int posX_send=300,int posY_send=50,int posY_receive=220,int posX_receive=100,int x=5,int y=5,int port_send=10000,char type='y', int port_listen=15000);

  void drawCircle(sf::RenderWindow &window);
  void changePosition ();
  void sendMessage();
  void receiveMessage();

  client m_client;
private:
  int m_posX_receive;
  int m_posY_receive;
  int m_y;
  int m_x;
  int m_posX_send;
  int m_posY_send;
  sf::CircleShape circle_send;
  sf::CircleShape circle_receive;
  unsigned int m_port_send;
  sf::Clock m_clock;
  char m_type;
};

#endif
