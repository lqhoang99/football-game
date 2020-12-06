#ifndef GOAL_H
#define GOAL_H

#include <SFML/Graphics.hpp>
#include "consts.h"
class Goal
{
public:
  Goal(double x, double y, const sf::Texture &texture);
  const sf::Vector2f& position() const;
  void render(sf::RenderWindow& window);

private:
  sf::Sprite m_image;
  sf::Vector2f m_position;
};

#endif
