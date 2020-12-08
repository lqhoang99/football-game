#include "client.hpp"
#include <iostream>

client::client ()
{
}

client::client(unsigned short port)
  {
    m_port=port;
    bindPort();
    m_selector.add(m_receiver);
    m_ipAddress=sf::IpAddress::getLocalAddress();
    //m_ipAddress_send=sf::IpAddress::getLocalAddress();
  }

void client::bindPort()
{
  m_receiver.bind(m_port);
}

void client::send(const unsigned short port,int posX_send,int posY_send)
{
  
    m_packet_send << posX_send << posY_send;
    if (m_sender.send(m_packet_send,m_ipAddress_send,port) == sf::UdpSocket::Done){
    }
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

void client::receive (int *posX_receive,int *posY_receive)
{
  int posX,posY;

  sf::IpAddress ip;

  unsigned short port;

  if (m_selector.wait(sf::milliseconds(1))) {

    if (m_receiver.receive(m_packet_receive,ip,port) == sf::UdpSocket::Done) {
    
      if (m_packet_receive >> posX >> posY) {
        *posX_receive=posX;
        *posY_receive=posY;
      }
    }
  }
}
