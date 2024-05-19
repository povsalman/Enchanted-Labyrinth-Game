#pragma once

#include <SFML/Graphics.hpp>
#include "backtracker.h" // Include necessary maze data or configurations
#include "player.h" // Include necessary maze data or configurations

//int eX, eY;

class Enemy : public sf::Drawable {
public:
   // Enemy();

    Enemy();

    // Update the enemy's position and behavior
    void update();
    void move();

    // Method to set the position of the enemy
    void setPosition(const sf::Vector2f& position) {
        m_position = position;
        m_shape.setPosition(position);
    }
    
    void setPosition(int xposition, int yposition) {
        m_position.x = xposition;
        m_position.y = yposition;

        m_shape.setPosition(m_position);
    }

    void setScale(float x, float y) {
        m_shape.setScale(x, y);
    }

    // Check collision with player sprite
    bool checkCollision(const sf::Sprite& player);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

//private:
    sf::RectangleShape m_shape; // Shape of the enemy
    sf::Vector2f m_position;    // Position of the enemy
    float m_speed;               // Speed of the enemy

    // Add any additional variables or methods you may need
};

Enemy::Enemy() {
    // Initialize enemy properties
    //m_shape.setSize(sf::Vector2f(10, 10)); // Adjust size as needed
    //m_shape.setFillColor(sf::Color::Red);  // Adjust color as needed
    //m_speed = 5.0f;                         // Adjust speed as needed
    //// Set initial position of the enemy
    //// Ensure enemies spawn outside maze borders but inside gaps
    //// Example:
    //m_position = sf::Vector2f(120, 120); // Adjust initial position as needed


    //m_shape.setSize(sf::Vector2f(10, 10)); // Adjust size as needed
    //m_shape.setFillColor(sf::Color::Red);  // Adjust color as needed


    //// Seed the random number generator
    //srand(time(0));

    //// Define maze boundary
    //int minX = initialPos.x;                             // Minimum X coordinate within maze boundary
    //int maxX = (initialPos.x + nCells * 10) + 10; // Maximum X coordinate within maze boundary
    //int minY = initialPos.y;                             // Minimum Y coordinate within maze boundary
    //int maxY = (initialPos.y + mCells * 10) + 10;// Maximum Y coordinate within maze boundary

    //while (1) {

    //    // Generate random position within maze boundary
    //    int randomX = minX + rand() % (maxX - minX + 1);
    //    int randomY = minY + rand() % (maxY - minY + 1);

    //    if (!cell[eX][eY - 1].isWall) {
    //        m_position.x = randomX;
    //        m_position.y = randomY;
    //        break;
    //    }

    //}


}

void Enemy::update() {
    // Implement movement logic here
    // Example:
    // Move the enemy randomly within the maze
    // Ensure enemies stay within maze bounds and navigate through gaps
    // Example:
    m_position.x += m_speed;
    m_position.y += m_speed;
    // Update the position of the enemy shape
    m_shape.setPosition(m_position);
}

void Enemy :: move()
{
    //if(direction==1)
    //x--;
}

bool Enemy::checkCollision(const sf::Sprite& player) {
    // Implement collision detection logic with the player sprite
    // Example:
    // sf::FloatRect enemyBounds = m_shape.getGlobalBounds();
    // sf::FloatRect playerBounds = player.getGlobalBounds();
    // return enemyBounds.intersects(playerBounds);
    return false; // Placeholder, update as needed
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw the enemy shape to the target
    target.draw(m_shape, states);
}