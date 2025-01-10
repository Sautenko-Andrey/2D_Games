#include<SFML/Graphics.hpp>
#include"Snake.h"
#include"World.h"
#include"Game.h"


int main(){

    // Program entrypoint
    Game game; // Creating our game object


    while(!game.getWindow()->isDone()){

        // Game loop
        game.handleInput();

        game.update();

        game.render();

        game.restartClock();
    }


    return 0;
}