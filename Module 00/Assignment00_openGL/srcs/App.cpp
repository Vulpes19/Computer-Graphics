#include "App.hpp"

App::App( int width, int height, const char *title )
{
    this->width = width;
    this->height = height;
    this->title = title;
    this->window = NULL;
    std::vector<Point> points;
    points.push_back(Point(-0.2f, 0.2f, 0.0f));
    points.push_back(Point(0.2f, 0.2f, 0.0f));
    points.push_back(Point(-0.2f, -0.2f, 0.0f));
    points.push_back(Point(0.2f, -0.2f, 0.0f));
    Vector pos(2.0f, 2.0f);
    Vector vel(2.0f, 2.0f);
    this->player = new Player(points, "srcs/vertexShader.glsl", "srcs/plFragmentShader.glsl");
    generateObstacles();
}

App::~App( void )
{
    glfwDestroyWindow(window);
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
    glfwSetKeyCallback(window, InputHandler::keyCallBack);
    player->init();
    for ( auto obstacle : obstacles )
        obstacle->init();
    start = time_clock::now();
    return (EXIT_SUCCESS);
}

void    App::render( void )
{
    glfwPollEvents();
    glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );
    player->draw();
    auto it = std::remove_if( obstacles.begin(), obstacles.end(), []( const GameObject *obstacle) {
        if ( obstacle->deadObstacle() )
        {
            delete obstacle;
            return (true);
        }
        return (false);
    });
    obstacles.erase(it, obstacles.end());
    if ( obstacles.empty() )
    {
        generateObstacles();
        for ( auto obstacle : obstacles )
            obstacle->init();
    }
    std::for_each( obstacles.begin(), obstacles.end(), []( GameObject *obstalce){
        obstalce->draw();
    });
    glfwSwapBuffers( window );
    end = time_clock::now();
    std::chrono::duration<double> elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    if ( player->handleMovement() )
        player->update();
    if ( elapsed.count() >= 1.0 )
    {
        for ( auto obstacle : obstacles )
            obstacle->update();
        start = time_clock::now();
    }
}

void    App::generateObstacles( void )
{
    std::random_device random;
    std::mt19937 gen(random());
    float minX = -1.05f;
    float maxX = 1.05f; 
    float maxY = 1.05f;
    
    std::uniform_real_distribution<float> distributionX(minX, maxX);
    std::uniform_real_distribution<float> distributionY(maxY, maxY -0.25f);
    for ( auto i = 0; i < 3; i++ )
    {
        float randomX = distributionX( gen );
        float randomY = distributionY( gen );
        std::vector<Point> points;
        points.push_back(Point(randomX, randomY, 0.0f));
        points.push_back(Point(randomX + 0.15f, randomY, 0.0f));
        points.push_back(Point(randomX, randomY - 0.25f, 0.0f));
        points.push_back(Point(randomX + 0.15f, randomY - 0.25f, 0.0f));
        obstacles.push_back( new Obstacle(points, "srcs/vertexShader.glsl", "srcs/obFragmentShader.glsl") );
    }
}

GLFWwindow* App::getWindow( void ) const
{
    return ( this->window );
}
