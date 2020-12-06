#include "headers/ClientConnection.h"
#include <iostream>

ClientConnection::ClientConnection()
{
  m_socket.bind(sf::Socket::AnyPort);
  m_selector.add(m_socket);
  m_port_receive = m_socket.getLocalPort();
  std::string bash("./fallow.sh " + std::to_string(m_port_receive));
  system(bash.c_str());
  // m_ip = sf::IpAddress::getLocalAddress();
}

void ClientConnection::send(int selected)
{
  m_packet << selected;
  // std::cout << m_selected << std::endl;

  m_socket.send(m_packet,"hostname -I",20000);
}

bool ClientConnection::wait()
{
  // std::cout << "USAO" << std::endl;
  unsigned short port;
  sf::IpAddress ip;
  if (m_selector.wait(sf::milliseconds(1))) {
    if (m_socket.receive(m_packet,ip,port) == sf::UdpSocket::Done)
      if (m_packet >> m_port_send >> m_selected >> m_ip >> m_turn) {
        m_socket.unbind();
        // m_ip.IpAddress(m_ip_string);
        return true;
      }
  }
  return false;
}

unsigned short ClientConnection::send()
{
  return m_port_send;
}
unsigned short ClientConnection::receive()
{
  return m_port_receive;
}
int ClientConnection::selected()
{
  return m_selected;
}
std::string ClientConnection::ip()
{
  return m_ip;
}
bool ClientConnection::turn()
{
  return m_turn;
}
