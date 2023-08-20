#include "GameObject.hpp"

GameObject::GameObject( void )
{}

GameObject::GameObject( Vector &position, Vector &velocity ) : position(position), velocity(velocity)
{}

GameObject::~GameObject( void )
{}

void    GameObject::draw( void )
{
    glUseProgram( shaderProgram );
    glBindVertexArray( vertexArrObj );
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
    glBindVertexArray(0);
}

void    GameObject::compileShaderProgram( void )
{
    const char *vertexShaderStr = loadShaderFromFile( VERTEX );
    const char *fragmentShaderStr = loadShaderFromFile( FRAGMENT );

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderStr, nullptr);
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
    glShaderSource( fragmentShader, 1, &fragmentShaderStr, nullptr );
    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        char infoLog[512];
        glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
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
        glGetProgramInfoLog( success, 512, NULL, infoLog );
        std::cerr << "Error: shader program linking failed\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}