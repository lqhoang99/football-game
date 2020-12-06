#include "headers/client.h"
#include <iostream>

client::client ()
{
}

client::client(unsigned short port, std::string ip)
  {
    m_port=port;
    bindPort();
    m_selector.add(m_receiver);
    m_ipAddress=sf::IpAddress::getLocalAddress();
    m_ipAddress_send=sf::IpAddress(ip);
  }

void client::bindPort()
{
  m_receiver.bind(m_port);
}

void client::send(const unsigned short port, int number, double x, double y)
{
    // Pakujemo podatke u paket
    m_packet_send << number << x << y;
    // Saljemo podatke
    if (m_sender.send(m_packet_send,m_ipAddress_send,port) == sf::UdpSocket::Done){
    }
    // Cistimo paket, praznimo ga
    m_packet_send.clear();
}

sf::IpAddress client::getAddress () const
{
  return m_ipAddress;
}

void client::setAddress (sf::IpAddress ipAddress)
{
  m_ipAddress_send=ipAddress;
}

bool client::receive (std::vector<Entity*> players)
{
  int number;
  double x,y;

  // Adresa sa kojeg su poslati podaci
  sf::IpAddress ip;
  // Port sa kojeg su stigli podaci
  unsigned short port;
  // Cekamo na poruku 1 milisekundu, ako je socket spreman uzimaju se podaci
  if (m_selector.wait(sf::milliseconds(1))) {
    // Primamo paket
    if (m_receiver.receive(m_packet_receive,ip,port) == sf::UdpSocket::Done) {
      // Uzimamo podatke iz paketa
      if (m_packet_receive >> number >> x >> y) {
        std::cout << number << " " << x << " " << y << std::endl;
        players[number]->setDirection(-x,-y);
        return true;
      }
    }
  }
  return false;
}

// sf::Packet& operator <<(sf::Packet& packet, sf::Vector2f direction)
// {
//   return packet << direction;
// }
//
// sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f direction)
// {
//   return packet >> direction;
// }
