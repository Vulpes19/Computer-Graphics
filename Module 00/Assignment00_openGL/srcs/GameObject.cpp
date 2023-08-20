#include "GameObject.hpp"

GameObject::GameObject( void )
{}

GameObject::GameObject( Vector position, Vector velocity, std::vector<Point> &points ) : position(position), velocity(velocity), points(points)
{
    GLuint vertexBufferObj;
    GLuint elementBufferObj;
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