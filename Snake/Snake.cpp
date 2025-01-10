#include"Snake.h"

enum class Coords {
    SnakeSegStartCoordX = 5,
    SnakeSeg1StartCoordY = 7,
    SnakeSeg2StartCoordY = 6,
    SnakeSeg3StartCoordY = 5
};

enum class Values {
    Speed = 5,
    Lives = 3,
    Score = 0
};

Snake::Snake(int block_size)
: m_size{block_size}
{
    // snake segments appear visually slightly separated
    // when we substract 1 from m_size variable
    m_body_rect.setSize(sf::Vector2f(m_size - 1, m_size - 1));

    reset();  // reset to starting position
}


/*************************************************************************
 * Methods
*************************************************************************/


/*
    This chunk of code will be called every time a new game begins.
    First, it will clear the snake segment vector from the previous game.
    After that, some snake segments will get added. Because of our 
    implementation, the first element in the vector is always going to be
    the head. The coordinates for the snake pieces are hardcoded for now,
    just to keep it simple.
*/
void Snake::reset(){

    // Clear vecotr of snake segments
    m_snake_body.clear();

    // add 3 snake segments with their appropriate coordinats
    m_snake_body.push_back(
        SnakeSegment(static_cast<int>(Coords::SnakeSegStartCoordX),
                     static_cast<int>(Coords::SnakeSeg1StartCoordY)));

    m_snake_body.push_back(
        SnakeSegment(static_cast<int>(Coords::SnakeSegStartCoordX),
                     static_cast<int>(Coords::SnakeSeg2StartCoordY)));
    
    m_snake_body.push_back(
        SnakeSegment(static_cast<int>(Coords::SnakeSegStartCoordX),
                     static_cast<int>(Coords::SnakeSeg3StartCoordY)));

    // Start off still(no snake movement)
    // until a player presses a key to move the snake.
    setDirection(Direction::None);   
    

    m_speed = static_cast<int>(Values::Speed);
    m_lives = static_cast<int>(Values::Lives);
    m_score = static_cast<int>(Values::Score);
    m_lost = false;
}


void Snake::setDirection(Direction dir){
    m_dir = dir;
}


Direction Snake::getDirection(){
    return m_dir;
}


int Snake::getSpeed(){
    return m_speed;
}


sf::Vector2i Snake::getPosition(){

    // Return snake's head position or (1,1) if body is empty
    return (!m_snake_body.empty() ? 
             m_snake_body.front().position :
            sf::Vector2i(1, 1)); 
}


int Snake::getLives(){
    return m_lives;
}


int Snake::getScore(){
    return m_score;
}


void Snake::increaseScore(){
    m_score += 10;
    ++m_speed;
}


bool Snake::hasLost(){
    return m_lost;
}


void Snake::lose(){
    m_lost = true;
}


void Snake::toggleLost(){
    m_lost = !m_lost;
}


void Snake::extend(){

    if(m_snake_body.empty()){
        return;
    }

    // Create a reference to the last element in the segment vector
    SnakeSegment &tail_head = m_snake_body[m_snake_body.size() - 1];

    // The snake is longer than one segment or it's not
    if(m_snake_body.size() > 1){
        // Reference points to the next to last element
        SnakeSegment &tail_bone = m_snake_body[m_snake_body.size() - 2];

        if(tail_head.position.x == tail_bone.position.x){
            if(tail_head.position.y > tail_bone.position.y){
                m_snake_body.push_back(
                    SnakeSegment(
                        tail_head.position.x, tail_head.position.y + 1
                    )
                );
            }
            else{
                m_snake_body.push_back(
                    SnakeSegment(
                        tail_head.position.x, tail_head.position.y - 1
                    )
                );
            }
        }
        else if(tail_head.position.y == tail_bone.position.y){
            if(tail_head.position.x > tail_bone.position.x){
                m_snake_body.push_back(
                    SnakeSegment(
                        tail_head.position.x + 1, tail_head.position.y
                    )
                );
            }
            else{
                m_snake_body.push_back(
                    SnakeSegment(
                        tail_head.position.x - 1, tail_head.position.y
                    )
                );
            }
        }
    }
    else{
        if(m_dir == Direction::Up){
            m_snake_body.push_back(
                SnakeSegment(
                    tail_head.position.x, tail_head.position.y + 1
                )
            );
        }
        else if(m_dir == Direction::Down){
            m_snake_body.push_back(
                SnakeSegment(
                    tail_head.position.x, tail_head.position.y - 1
                )
            );
        }
        else if(m_dir == Direction::Left){
            m_snake_body.push_back(
                SnakeSegment(
                    tail_head.position.x + 1, tail_head.position.y
                )
            );
        }
        else if(m_dir == Direction::Right){
            m_snake_body.push_back(
                SnakeSegment(
                    tail_head.position.x - 1, tail_head.position.y
                )
            );
        }
    }
}


void Snake::tick(){

    /*
        Update method
    */

    // Check if the snake should be moved or not, 
    // based on its size and direction.
    if(m_snake_body.empty() || m_dir == Direction::None){
        return;
    }

    move();
    checkCollision();
}


void Snake::move(){

    for(auto i{m_snake_body.size() - 1}; i > 0; --i){
        m_snake_body[i].position = m_snake_body[i - 1].position;
    }

    if(m_dir == Direction::Left){
        --m_snake_body[0].position.x;
    }
    else if(m_dir == Direction::Right){
        ++m_snake_body[0].position.x;
    }
    else if(m_dir == Direction::Up){
        --m_snake_body[0].position.y;
    }
    else if(m_dir == Direction::Down){
        ++m_snake_body[0].position.y;
    }

}


void Snake::checkCollision(){

    if(m_snake_body.size() < 5){
        return;
    }

    SnakeSegment &head = m_snake_body.front();

    for(auto it{m_snake_body.begin() + 1}; it != m_snake_body.end(); ++it){
        // If both positions are the same,
        // the head is intersecting with the body
        if(it->position == head.position){
            auto segments{m_snake_body.end() - it};
            cut(segments);
            // There can only be one collision at a time
            // so we use break here
            break;
        }
    }
}


void Snake::cut(size_t segments){

    if(segments > m_snake_body.size()){
        return;
    }

    for(size_t i{0}; i < segments; ++i){
        m_snake_body.pop_back();
    }

    --m_lives;

    if(!m_lives){
        lose();
        return;
    }
}


void Snake::render(sf::RenderWindow &window){

    if(m_snake_body.empty()){
        return;
    }

    auto head = m_snake_body.begin();

    m_body_rect.setFillColor(sf::Color::Yellow);

    m_body_rect.setPosition(
        head->position.x * m_size,
        head->position.y * m_size
    );

    window.draw(m_body_rect);

    m_body_rect.setFillColor(sf::Color::Green);

    for(auto it{m_snake_body.begin() + 1}; it != m_snake_body.end(); ++it){
        m_body_rect.setPosition(
            it->position.x * m_size,
            it->position.y * m_size
        );

        window.draw(m_body_rect);
    }
}


/*
    Clarify physical direction of the snake
    according to its head and neck.
*/
Direction Snake::getPhysicalDirection(){
    if(m_snake_body.size() <= 1){
        return Direction::None;
    }

    SnakeSegment &head = m_snake_body[0];
    SnakeSegment &neck = m_snake_body[1];

    if(head.position.x == neck.position.x){
        return (head.position.y > neck.position.y) ?
                Direction::Down : Direction::Up;
    }
    else if(head.position.y == neck.position.y){
        return (head.position.x > neck.position.x) ?
                Direction::Right : Direction::Left;
    }

    return Direction::None;
}