#include "App.hpp"
#include "Triangle.hpp"

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