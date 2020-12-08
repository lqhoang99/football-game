#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include "player.hpp"

// player p1;
player p2(100,220,50,330,5,5,15000,'x',10000);

void defineWindow(sf::RenderWindow &window);

int main ()
{
  sf::RenderWindow window(sf::VideoMode(800,600), "Krugovi");

  defineWindow(window);

  return 0;
}

void defineWindow(sf::RenderWindow &window)
{
  sf::Event event;

  while (window.isOpen()) {
    while(window.pollEvent(event)) {
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
          window.close();
      }
      if (event.type==sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::White);

    p2.sendMessage();

    p2.receiveMessage();



    p2.drawCircle(window);

    window.display();
  }
}
