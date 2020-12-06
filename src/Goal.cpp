#include "headers/Goal.h"
#include "iostream"

Goal::Goal(double x, double y, const sf::Texture &texture)
  : m_image(texture)
  , m_position(x,y)
  {
    m_image.setPosition(x,y);
    m_image.setScale(1.3,1);
    
  }

void Goal::render(sf::RenderWindow& window) {
    window.draw(m_image);
}

const sf::Vector2f& Goal::position() const {
    return m_position;
}
