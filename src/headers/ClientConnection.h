#ifndef CLINETCONNECTION_H
#define CLINETCONNECTION_H

#include <SFML/Network.hpp>
#include <string>

class ClientConnection {
public:
  ClientConnection();
  void send(int selected);
  bool wait();
  unsigned short send();
  unsigned short receive();
  int selected();
  std::string ip();
  bool turn();
  
private:
  sf::UdpSocket m_socket;
  sf::SocketSelector m_selector;
  unsigned short m_port_receive;
  unsigned short m_port_send;
  sf::Packet m_packet;
  std::string m_ip;
  // sf::IpAddress m_ip;
  int m_selected;
  bool m_turn;
};
#endif
