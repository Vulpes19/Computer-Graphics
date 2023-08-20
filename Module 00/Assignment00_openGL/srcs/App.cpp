#include "App.hpp"

App::App( int width, int height, const char *title )
{
    this->width = width;
    this->height = height;
    this->title = title;
    this->window = NULL;
    std::vector<Point> points;
    points.push_back(Point(-0.5f, 0.5f, 0.0f));
    points.push_back(Point(0.5f, -0.5f, 0.0f));
    points.push_back(Point(0.0f, 0.5f, 0.0f));
    Vector pos(2.0f, 2.0f);
    Vector vel(2.0f, 2.0f);
    this->player = new Player(pos, vel, points);
}

App::~App( void )
{
    glfwTerminate();
}

int App::init( void )
{
    if ( !glfwInit() )
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return ( EXIT_FAILURE );
    }
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    window = glfwCreateWindow( width, height, title, nullptr, nullptr );
    if ( !window )
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return ( EXIT_FAILURE );
    }
    glfwMakeContextCurrent( window );
    if ( !gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress ) )
    {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        return ( EXIT_FAILURE );
    }
    glViewport( 0, 0, width, height );
    return (EXIT_SUCCESS);
}

void    App::render( void )
{
    glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );
    glfwSwapBuffers( window );
    glfwPollEvents();
}

GLFWwindow* App::getWindow( void ) const
{
    return ( this->window );
}
