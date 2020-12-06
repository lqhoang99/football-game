#include "headers/Formation.h"
#include "iostream"


Formation::Formation(double left_x , double left_y ,double right_x , double right_y, double center_x  , double center_y)
  : m_left(left_x , left_y), m_right(right_x,right_y), m_center(center_x, center_y)
  {

  }

const sf::Vector2f& Formation::left() const {
    return m_left;
}
const sf::Vector2f& Formation::right() const {
    return m_right;
}
const sf::Vector2f& Formation::center() const {
    return m_center;
}
