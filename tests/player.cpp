#include "player.hpp"
#include <iostream>

player::player(int posX_send,int posY_send,int posY_receive,int posX_receive,int x,int y,int port_send, char type, int port_listen)
  :m_posX_receive(posX_receive)
  ,m_posY_receive(posY_receive)
  ,m_posX_send(posX_send)
  ,m_posY_send(posY_send)
  ,m_y(y)
  ,circle_send(50)
  ,circle_receive(50)
  ,m_client(port_listen)
  ,m_port_send(port_send)
  ,m_type(type)
  ,m_x(x)
  {
    m_clock.restart();
  }

void player::drawCircle(sf::RenderWindow &window)
{
  circle_send.setFillColor(sf::Color::Yellow);
  circle_send.setOutlineThickness(15);
  circle_send.setOutlineColor(sf::Color::Green);
  circle_send.setPosition(m_posX_send,m_posY_send);
  circle_receive.setFillColor(sf::Color::Yellow);
  circle_receive.setOutlineThickness(15);
  circle_receive.setOutlineColor(sf::Color::Green);
  circle_receive.setPosition(m_posX_receive,m_posY_receive);
  window.draw(circle_send);
  window.draw(circle_receive);
}

void player::changePosition ()
{
  if (m_type=='x') {
    if (m_x>0 && m_posX_send+m_x>685) {
      m_posX_send=685;
      m_x=-m_x;
    }
    else if (m_x<0 && m_posX_send+m_x<15) {
      m_posX_send=15;
      m_x=-m_x;
    }
    else
      m_posX_send=m_posX_send+m_x;
  }
  else {
    if (m_y>0 && m_posY_send+m_y>485) {
      m_posY_send=485;
      m_y=-m_y;
    }
    else if (m_y<0 && m_posY_send+m_y<15) {
      m_posY_send=15;
      m_y=-m_y;
    }
    else
      m_posY_send=m_posY_send+m_y;
  }
}

void player::sendMessage()
{
  if (m_clock.getElapsedTime().asSeconds() >= 0.007) {
    changePosition();
    m_client.send(m_port_send,m_posX_send,m_posY_send);
    m_clock.restart();
  }
}

void player::receiveMessage()
{
  m_client.receive(&m_posX_receive,&m_posY_receive);
}
