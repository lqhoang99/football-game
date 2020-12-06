#ifndef FORMATION_H
#define FORMATION_H

#include <SFML/Graphics.hpp>
#include "consts.h"

class Formation
{
public:
  Formation(double left_x , double left_y ,double right_x , double right_y, double center_x  , double center_y);
  const sf::Vector2f& right() const;
  const sf::Vector2f& left() const;
  const sf::Vector2f& center() const;

private:
  sf::Vector2f m_left;
  sf::Vector2f m_right;
  sf::Vector2f m_center;
};

#endif
