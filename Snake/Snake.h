#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>


// Structure of what will be consists our snake
struct SnakeSegment {

    SnakeSegment(int x, int y) : position{x, y} {}

    sf::Vector2i position;
};


// Alias for vector with snake's segments
//using SnakeContainer = std::vector<SnakeSegment>;
using SnakeContainer = std::deque<SnakeSegment>;

// Snake's direction enumeration
enum class Direction { None, Up, Down, Left, Right };


// Snake
class Snake {

public:

    explicit Snake(int block_size);

    // Helper methods
    void setDirection(Direction dir);

    Direction getDirection();

    int getSpeed();

    sf::Vector2i getPosition();

    int getLives();

    int getScore();

    void increaseScore();

    bool hasLost();

    void lose(); // Handle loosing here

    void toggleLost();

    void extend();   // Grow the snake

    void reset();    // Reset to starting position

    void move();    // Movement method

    void tick();    // Update method

    void cut(size_t segments);  // Method for cutting snake

    void render(sf::RenderWindow &window);

    Direction getPhysicalDirection();

private:

    void checkCollision();    // Checking for collisions

    SnakeContainer m_snake_body;  // Segment vector

    int m_size;  // Size of the graphics

    Direction m_dir;   // Current direction

    int m_speed;   // Speed of the snake

    int m_lives;   // Lives

    int m_score;   // Score

    bool m_lost;   // Losing state

    sf::RectangleShape m_body_rect;  // Shape used in rendering

};