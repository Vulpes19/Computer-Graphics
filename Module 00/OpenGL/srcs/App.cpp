#include "App.hpp"

App::App(int width, int height, const char* title)
{
    this->width = width;
    this->height = height;
    this->title = title;
    tr = new Triangle(vec3(-0.5f, -0.5f, 0.0f), vec3(0.0f, 0.5f, 0.0f), vec3(0.5f, -0.5f, 0.0f));
    // exit(1);
}

App::~App( void )
{
    glfwTerminate();
}

int App::init( void )
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return (EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Shouldn't be needed but required on macos
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // We don't want the window to be resizable
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return (EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        return (EXIT_FAILURE);
    }
    glViewport(0, 0, width, height);
    // exit(1);
    tr->init();
    return (EXIT_SUCCESS);
}

void    App::render( void )
{
    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set the clear color to a nice green
    // glClear(GL_COLOR_BUFFER_BIT); // Clear the screen in preparation for new drawing
    tr->render();
    glfwSwapBuffers(window); // Swap the buffers to display what was just drawn
    glfwPollEvents(); // Look for events
}

GLFWwindow* App::getWindow( void ) const
{
    return (window);
}