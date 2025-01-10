#include "Window.h"

/*
***************************************************************************
    Public methods
***************************************************************************
*/
Window::Window(){

    setUp("Window", sf::Vector2u(640, 480));

}



Window::Window(const std::string &title, const sf::Vector2u &size){

    setUp(title, size);

}



Window::~Window(){

    destroy();

}



void Window::beginDraw(){

    m_window.clear(sf::Color::Black);

}



void Window::endDraw(){

    m_window.display();

}



void Window::update(){

    sf::Event event;
    while(m_window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            m_is_done = true;
        }
        else if(event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::F5){
            
            toggleFullScreen();

        }
    }

}



bool Window::isDone(){

    return m_is_done;
}



bool Window::isFullScreen(){

    return m_is_full_screen;
}



sf::Vector2u Window::getWindowSize(){

    return m_window_size;
}



void Window::toggleFullScreen(){

    m_is_full_screen = !m_is_full_screen;

    destroy();

    create();

}



void Window::draw(sf::Drawable &drawable){

    m_window.draw(drawable);
}


/*
***************************************************************************
    Private methods
***************************************************************************
*/
void Window::setUp(const std::string &title, 
                   const sf::Vector2u &size){

    m_window_title = title;
    m_window_size = size;
    m_is_full_screen = false;
    m_is_done = false;

    create();

}



void Window::destroy(){

    m_window.close();

}



void Window::create(){

    auto style = (m_is_full_screen ? sf::Style::Fullscreen : sf::Style::Default);

    m_window.create(
        {m_window_size.x, m_window_size.y, 32}, 
        m_window_title,
        style
    );
}


sf::RenderWindow* Window::getRenderWindow(){
    return &m_window;
}