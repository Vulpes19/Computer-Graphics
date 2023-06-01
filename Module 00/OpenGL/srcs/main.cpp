#include "Window.hpp"

int main( void )
{
    Window window(800, 600, "LearnOpenGL");
    window.init();
    while (!glfwWindowShouldClose(window.getWindow()))
    {
        window.render();
    }
    return (EXIT_SUCCESS);
}