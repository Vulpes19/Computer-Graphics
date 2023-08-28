#include "App.hpp"

int main( void )
{
    App game(800, 600, "assignment00-OpenGL");

     game.init();
    while ( glfwWindowShouldClose(game.getWindow()) == GLFW_FALSE )
    {
        game.render();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return (EXIT_SUCCESS);
}