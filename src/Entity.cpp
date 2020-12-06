#include "headers/Entity.h"
#include "headers/consts.h"
#include <iostream>
#include <math.h>

Entity::Entity(double x, double y, const sf::Texture& texture, double x_, double y_)
    :m_position(x, y), m_image(texture)
{
    m_image.setPosition(x, y);
    m_radius = m_image.getTexture()->getSize().x/2;
    m_center.x = x + m_radius;
    m_center.y =  y + m_radius;
    // Stavljeno zbog testiranja funkcije move
    m_direction.x=x_;
    m_direction.y=y_;
    m_mass=0.1*(m_radius);
}

Entity::Entity(const sf::Vector2f& position, const sf::Texture& texture)
    :m_position(position), m_image(texture)
{
    m_image.setPosition(position.x, position.y);
    m_radius = m_image.getTexture()->getSize().x;
    m_center.x = position.x + m_radius;
    m_center.y = position.y + m_radius;
}

const sf::Vector2f& Entity::position() const {
    return m_position;
}

const sf::Vector2f& Entity::direction() const {
    return m_direction;
}

const sf::Vector2f& Entity::center() const {
    return m_center;
}

const sf::Sprite& Entity::image() const {
    return m_image;
}

const int Entity::radius() const {
  return m_radius;
}

const double Entity::mass() const
{
    return m_mass;
}

void Entity::setPosition(double x, double y) {
  m_position.x = x;
  m_position.y = y;
}
void Entity::setDirection(double x , double y) {
  m_direction.x = x;
  m_direction.y = y;
}

void Entity::setPosition(const sf::Vector2f& position) {
  m_position.x = position.x;
  m_position.y = position.y;
}
void Entity::setDirection(const sf::Vector2f& direction) {
  m_direction.x = direction.x;
  m_direction.y = direction.y;
}

void Entity::setCenter(double x, double y)
{
  m_center.x=x;
  m_center.y=y;
}

void Entity::update() {
  move();
  checkBoundaryCollision();
  // checkEntityCollision(other);
}

void Entity::render(sf::RenderWindow& window) {
  m_image.setPosition(m_position.x-m_radius,m_position.y-m_radius);
  window.draw(m_image);
}

void Entity::move()
{
  // Uvecavamo trenutnu poziciju objekta, idemo za x i y koliko kaze vektor pravca
  m_position.x+=m_direction.x;
  m_position.y+=m_direction.y;

  // Azurira se centar sprite-a, samim tim i entity-a
  m_center.x = m_position.x + m_radius;
  m_center.y = m_position.y + m_radius;

  // Postavlja se pozicija teksture kako bi iscrtavanje bilo moguce
  m_image.setPosition(m_position.x-m_radius,m_position.y-m_radius);
}

void Entity::checkBoundaryCollision()
{
  if (m_position.x > WINDOW_WIDTH-m_radius) {
    m_position.x = WINDOW_WIDTH-m_radius;
    m_direction.x *= -1;
  }
  else if (m_position.x < m_radius) {
    m_position.x = m_radius;
    m_direction.x *= -1;
  }
  else if (m_position.y > WINDOW_HEIGHT-m_radius) {
    m_position.y = WINDOW_HEIGHT-m_radius;
    m_direction.y *= -1;
  }
  else if (m_position.y < m_radius) {
    m_position.y = m_radius;
    m_direction.y *= -1;
  }
  m_direction.x*=0.970;
  m_direction.y*=0.970;
  /*
  if( 0.0001 > abs(m_direction.x)){
    m_direction.x = 0;
  }
  if(0.0001 > abs(m_direction.y)){
    m_direction.y = 0;
  }
  */
}
void Entity::checkGoalCollision(Goal &goal , Goal &goal2)
{
  // gornji gol leva stativa
  if (m_image.getGlobalBounds().left < goal.position().x + 7 && m_image.getGlobalBounds().left + 2*m_radius > goal.position().x &&
      m_image.getGlobalBounds().top < goal.position().y + GOAL_HEIGHT && 2*m_radius + m_image.getGlobalBounds().top > goal.position().y)
  {
    m_direction.x *= -1;
    m_direction.y *= -1;
  }
  // gornji  gol desna stativa
  if (m_image.getGlobalBounds().left < goal.position().x + GOAL_WIDTH && m_image.getGlobalBounds().left + 2*m_radius > goal.position().x + GOAL_WIDTH - 7 &&
      m_image.getGlobalBounds().top < goal.position().y + GOAL_HEIGHT && 2*m_radius + m_image.getGlobalBounds().top > goal.position().y)
  {
    m_direction.x *= -1;
    m_direction.y *= -1;
  }
  //donji gol leva stativa
  if (m_image.getGlobalBounds().left < goal2.position().x + 7 && m_image.getGlobalBounds().left + 2*m_radius > goal2.position().x &&
      m_image.getGlobalBounds().top < goal2.position().y + GOAL_HEIGHT && 2*m_radius + m_image.getGlobalBounds().top > goal2.position().y)
  {
    m_direction.x *= -1;
    m_direction.y *= -1;
  }
  //donji gol desna stativa
  if (m_image.getGlobalBounds().left < goal2.position().x + GOAL_WIDTH && m_image.getGlobalBounds().left + 2*m_radius > goal2.position().x + GOAL_WIDTH - 7 &&
      m_image.getGlobalBounds().top < goal2.position().y + GOAL_HEIGHT && 2*m_radius + m_image.getGlobalBounds().top > goal2.position().y)
  {
    m_direction.x *= -1;
    m_direction.y *= -1;
  }



}
int Entity::isInGoal(Goal &goal , Goal &goal2)
{
  if (m_image.getGlobalBounds().left < goal.position().x + GOAL_WIDTH - m_radius && m_image.getGlobalBounds().left + 2*m_radius > goal.position().x + m_radius &&
      m_image.getGlobalBounds().top < goal.position().y + GOAL_HEIGHT - m_radius && 2*m_radius + m_image.getGlobalBounds().top > goal.position().y)
  {

      return 1;
  }
  if (m_image.getGlobalBounds().left < goal2.position().x + GOAL_WIDTH - m_radius && m_image.getGlobalBounds().left + 2*m_radius > goal2.position().x + m_radius &&
      m_image.getGlobalBounds().top < goal2.position().y + GOAL_HEIGHT && 2*m_radius + m_image.getGlobalBounds().top > goal2.position().y + GOAL_HEIGHT - m_radius)
  {
      return 2;
  }
  return 0;
}
bool Entity::checkEntityCollision(Entity& other)
{
  sf::Vector2f distanceVect(other.position().x-m_position.x, other.position().y-m_position.y);

  // Calculate magnitude of the vector separating the balls
  float distanceVectMag = sqrt(distanceVect.x*distanceVect.x+distanceVect.y*distanceVect.y);

  // Minimum distance before they are touching
  float minDistance = m_radius + other.radius();

  if (distanceVectMag < minDistance) {
    float distanceCorrection = (minDistance-distanceVectMag)/2.0;
    sf::Vector2f d (distanceVect.x,distanceVect.y);
    float d_norm=sqrt(d.x*d.x+d.y*d.y);
    sf::Vector2f correctionVector (d.x/d_norm*distanceCorrection,d.y/d_norm*distanceCorrection);
    other.setPosition(other.position().x+correctionVector.x,other.position().y+correctionVector.y);
    m_position.x-=correctionVector.x;
    m_position.y-=correctionVector.y;

    // get angle of distanceVect
    float theta  = atan(distanceVect.y/distanceVect.x);
    // // precalculate trig values
    float sine = sin(theta);
    float cosine = cos(theta);

    sf::Vector2f bTemp0;
    sf::Vector2f bTemp1;
    /* this ball's position is relative to the other
     so you can use the vector between them (bVect) as the
     reference point in the rotation expressions.
     bTemp[0].position.x and bTemp[0].position.y will initialize
     automatically to 0.0, which is what you want
     since b[1] will rotate around b[0] */
    bTemp1.x  = cosine * distanceVect.x + sine * distanceVect.y;
    bTemp1.y  = cosine * distanceVect.y - sine * distanceVect.x;

    // rotate Temporary velocities
    sf::Vector2f vTemp0;
    sf::Vector2f vTemp1;

    vTemp0.x  = cosine * m_direction.x + sine * m_direction.y;
    vTemp0.y  = cosine * m_direction.y - sine * m_direction.x;
    vTemp1.x  = cosine * other.direction().x + sine * other.direction().y;
    vTemp1.y  = cosine * other.direction().y - sine * other.direction().x;

    sf::Vector2f vFinal0;
    sf::Vector2f vFinal1;

    // final rotated m_direction for b[0]
    vFinal0.x = ((m_mass - other.mass()) * vTemp0.x + 2 * other.mass() * vTemp1.x) / (m_mass + other.mass());
    vFinal0.y = vTemp0.y;

    // final rotated m_direction for b[0]
    vFinal1.x = ((other.mass() - m_mass) * vTemp1.x + 2 * m_mass * vTemp0.x) / (m_mass + other.mass());
    vFinal1.y = vTemp1.y;

    // hack to avoid clumping
    bTemp0.x += vFinal0.x;
    bTemp1.x += vFinal1.x;

    /* Rotate ball positions and velocities back
     Reverse signs in trig expressions to rotate
     in the opposite direction */
    // rotate balls
    sf::Vector2f bFinal0;
    sf::Vector2f bFinal1;

    bFinal0.x = cosine * bTemp0.x - sine * bTemp0.y;
    bFinal0.y = cosine * bTemp0.y + sine * bTemp0.x;
    bFinal1.x = cosine * bTemp1.x - sine * bTemp1.y;
    bFinal1.y = cosine * bTemp1.y + sine * bTemp1.x;

    // update balls to screen position
    other.setPosition(m_position.x + bFinal1.x,m_position.y + bFinal1.y);

    m_position.x+=bFinal0.x;
    m_position.y+=bFinal0.y;

    m_direction.x = cosine * vFinal0.x - sine * vFinal0.y;
    m_direction.y = cosine * vFinal0.y + sine * vFinal0.x;
    other.setDirection(cosine * vFinal1.x - sine * vFinal1.y,cosine * vFinal1.y + sine * vFinal1.x);
    return true;
  }
  return false;
}

float Entity::distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
  return abs(sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2))));
}
