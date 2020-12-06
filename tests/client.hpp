#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#ifndef CLIENT_H
#define CLIENT_H

class client {
public:
  client();
  client(unsigned short port);

  sf::IpAddress getAddress () const;
  void setAddress (sf::IpAddress ipAddress);
  void receive (int *posX_receive,int *posY_receive);
  void send (const unsigned short port,int posX_send,int posY_send);
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

#endif
