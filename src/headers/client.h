#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "Entity.h"

class client {
public:
  client();
  client(unsigned short port,std::string ip);

  sf::IpAddress getAddress () const;
  void setAddress (sf::IpAddress ipAddress);
  bool receive (std::vector<Entity*> players);
  void send (const unsigned short port, int number, double x, double y);
  void start ();
  void bindPort();
  // void changePosition ();

private:
  unsigned short m_port;
  sf::IpAddress m_ipAddress_send;
  // sf::IpAddress m_ipAddress_receive;
  sf::IpAddress m_ipAddress;
  sf::UdpSocket m_sender;
  sf::UdpSocket m_receiver;
  sf::SocketSelector m_selector;
  sf::Packet m_packet_send;
  sf::Packet m_packet_receive;
  // sf::Clock m_clock;
};

// sf::Packet& operator <<(sf::Packet& Packet, sf::Vector2f direction);
// sf::Packet& operator >>(sf::Packet& Packet, sf::Vector2f direction);

#endif
