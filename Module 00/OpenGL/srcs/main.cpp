#include "App.hpp"
#include "Draw.hpp"

int main( void )
{
    App game(800, 600, "LearnOpenGL");

     game.init();
    while ( glfwWindowShouldClose(game.getWindow()) == GLFW_FALSE )
    {
        game.render();
    }
    return (EXIT_SUCCESS);
}