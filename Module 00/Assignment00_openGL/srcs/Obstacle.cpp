#include "Obstacle.hpp"

Obstacle::Obstacle( std::vector<Point> points, const char *vShader, const char *fShader ) : GameObject( points, vShader, fShader )
{
    moveSpeed = 0.1f;
};

Obstacle::~Obstacle( void )
{}

void    Obstacle::update( void )
{
    float normalizedBottomBorder = -1.15f;
    for ( auto i = 1; i < 12; i += 3 )
    {
        if ( vertices[i] <= normalizedBottomBorder )
            isDead = true;
        vertices[i] -= 0.1f;
    }
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

bool    Obstacle::deadObstacle( void ) const
{
    return (isDead);
}