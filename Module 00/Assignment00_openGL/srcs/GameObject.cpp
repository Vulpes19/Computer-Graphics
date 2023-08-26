#include "GameObject.hpp"

GameObject::GameObject( void )
{}

GameObject::GameObject( std::vector<Point> &points, const char *vShader, const char *fShader ) : points(points), vertexShPath(vShader), fragmentShPath(fShader)
{
    this->vertexArrObj = 0;
    this->shaderProgram = 0;
}

GameObject::~GameObject( void )
{
    std::cout << "pskch" << std::endl;

    glDeleteBuffers(1, &vertexBufferObj);
    glDeleteBuffers(1, &elementBufferObj);
    glDeleteProgram(shaderProgram);
}

void GameObject::init( void )
{
    if ( vertexBufferObj != 0 )
    {
        glDeleteBuffers(1, &vertexBufferObj);
        vertexBufferObj = 0;
    }
    if ( elementBufferObj != 0 )
    {
        glDeleteBuffers(1, &elementBufferObj);
        elementBufferObj = 0;
    }
    if (vertexArrObj != 0)
    {
        glDeleteVertexArrays(1, &vertexArrObj);
        vertexArrObj = 0;
    }
    compileShaderProgram();
    for ( size_t i = 0, j = 0; i < 12 && j < points.size(); i += 3, j++ )
    {
        vertices[i] = points[j].x;
        vertices[i + 1] = points[j].y;
        vertices[i + 2] = points[j].z;
    }
    unsigned int indices[] = {
        0, 2, 3,
        0, 1, 3
    };
    glGenVertexArrays(1, &vertexArrObj);
    glGenBuffers(1, &vertexBufferObj);
    glGenBuffers(1, &elementBufferObj);
    glBindVertexArray(vertexArrObj);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObj);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);
}

void    GameObject::draw( void )
{
    glUseProgram( shaderProgram );
    glBindVertexArray( vertexArrObj );
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
    glBindVertexArray(0);
}

std::string GameObject::loadShaderFromFile( enum SHADER sh )
{
    std::ifstream file;
    if ( sh == VERTEX )
        file.open(vertexShPath);
    else
        file.open(fragmentShPath);
    if ( !file.is_open() )
        return ("NONE");
    std::string shader( (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>() );
    return (shader);
}

void    GameObject::compileShaderProgram( void )
{
    std::string vertexShaderStr = loadShaderFromFile( VERTEX );
    std::string fragmentShaderStr = loadShaderFromFile( FRAGMENT );
    const char *cnstVertexShader = vertexShaderStr.c_str();
    const char *cnstfragmentShader = fragmentShaderStr.c_str();
    if ( vertexShaderStr == "NONE" )
    {
        std::cerr << "error loading vertex shader from file" << std::endl;
    }
    if ( fragmentShaderStr == "NONE" )
        std::cerr << "error loading fragment shader from file" << std::endl;
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &cnstVertexShader, nullptr);
    glCompileShader(vertexShader);
    
    int success;
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        char infoLog[512];
        glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
        std::cerr << "Error: vertex shader compilation failed\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource( fragmentShader, 1, &cnstfragmentShader, NULL );
    glCompileShader(fragmentShader);
    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        char infoLog[512];
        glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
        std::cerr << "Error: fragment shader compilation failed\n" << infoLog << std::endl;
    }
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if ( !success )
    {
        char infoLog[512];
        glGetProgramInfoLog( shaderProgram, 512, NULL, infoLog );
        std::cerr << "Error: shader program linking failed\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}