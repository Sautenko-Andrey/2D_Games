#include "Game.h"


Game::Game()
: m_world{sf::Vector2u(800, 600), &m_textbox},
  m_snake{m_world.getBlockSize()},
  m_window{"Snake", sf::Vector2u(800, 600)}
{
    // Setting up class members

    m_textbox.setup(5, 14, 350, sf::Vector2f(225, 0));
    m_textbox.add("Your results");
}


void Game::handleInput(){
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
       m_snake.getPhysicalDirection() != Direction::Down)
    {
        m_snake.setDirection(Direction::Up);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
            m_snake.getPhysicalDirection() != Direction::Up)
    {
        m_snake.setDirection(Direction::Down);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
            m_snake.getPhysicalDirection() != Direction::Left)
    {
        m_snake.setDirection(Direction::Right);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
            m_snake.getPhysicalDirection() != Direction::Right)
    {
        m_snake.setDirection(Direction::Left);
    }

}

void Game::update(){

    /*
        Updating the position of our sprite each frame
    */

    m_window.update();  // Update window events

    // Snake speed in order to update the appropriate amount
    // of times per second
    float timestep = 1.0f / m_snake.getSpeed();

    if(m_elapsed_time.asSeconds() >= timestep){
        m_snake.tick();

        m_world.update(m_snake);
        m_elapsed_time -= sf::seconds(timestep);

        // If user lost
        if(m_snake.hasLost()){
            m_textbox.add("Game over! Score: " +
                           std::to_string(m_snake.getScore()));
            m_snake.reset();
        }
    }

}

void Game::render(){

    m_window.beginDraw();       // Clear

    // Render here
    m_world.render(*m_window.getRenderWindow());
    m_snake.render(*m_window.getRenderWindow());
    m_textbox.render(*m_window.getRenderWindow());

    m_window.endDraw();

}

Window* Game::getWindow(){

    return &m_window;

}


sf::Time Game::getElapsedTime(){
    return m_elapsed_time;
}


void Game::restartClock(){

    // Fixed time step
    m_elapsed_time += m_clock.restart();    
}