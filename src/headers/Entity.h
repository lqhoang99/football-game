#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/Graphics.hpp>
#include "Goal.h"

#include <iostream>


class Entity
{
public:
    Entity(double x, double y, const sf::Texture& texture,double x_, double y_);
    Entity(const sf::Vector2f& position, const sf::Texture& texture);

    // geteri
    const sf::Vector2f& position() const;
    const sf::Vector2f& direction() const;
    const sf::Vector2f& center() const;
    const sf::Sprite& image() const;
    const int radius() const;
    const double mass() const;

    // seteri
    void setPosition(double x, double y);
    void setPosition(const sf::Vector2f& position);
    void setDirection(double x , double y);
    void setDirection(const sf::Vector2f& direction);
    void setCenter(double x, double y);

    void update();
    void render(sf::RenderWindow& window);

    bool checkEntityCollision(Entity& other);
    // bool colisionField();
    void checkBoundaryCollision();
    void checkGoalCollision(Goal &goal, Goal &goal2);
    int isInGoal(Goal &goal , Goal &goal2);

private:
    sf::Vector2f m_position; // Mozda staviti Vector2f
    sf::Vector2f m_center;
    sf::Sprite m_image;
    sf::Vector2f m_direction;

    int m_radius;
    double m_mass;

    float distanceBetweenPoints(float x1, float y1, float x2, float y2);
    void move();
};

#endif
