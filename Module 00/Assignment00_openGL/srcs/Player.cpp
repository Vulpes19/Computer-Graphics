#include "Player.hpp"
#include <fstream>
#include <string>

 Player::Player( Vector position, Vector velocity, std::vector<Point> &points, const char *vShader, const char *fShader ) : GameObject( position, velocity, points, vShader, fShader )
 {
    moveSpeed = 0.2f;
 }
       
Player::~Player( void )
{}

bool    Player::handleMovement( void )
{
    if ( InputHandler::getInstance()->isKeyPressed(GLFW_KEY_W) )
    {
        for ( auto i = 1; i < 12; i += 3 )
        {
            std::cout << vertices[i] << " " << HEIGHT << std::endl;
            if ( vertices[i] < HEIGHT )
                vertices[i] += moveSpeed;
        }
        return (true);
    }
    if ( InputHandler::getInstance()->isKeyPressed(GLFW_KEY_S) )
    {
        for ( auto i = 1; i < 12; i += 3 )
        {
            std::cout << vertices[i] << " " << WIDTH << std::endl;
            vertices[i] -= moveSpeed;
        }
        return (true);
    }
    if ( InputHandler::getInstance()->isKeyPressed(GLFW_KEY_A) )
    {
        for ( auto i = 0; i < 12; i += 3 )
            vertices[i] -= moveSpeed;
        return (true);
    }
    if ( InputHandler::getInstance()->isKeyPressed(GLFW_KEY_D) )
    {
        for ( auto i = 0; i < 12; i += 3 )
            vertices[i] += moveSpeed;
        return (true);
    }
    return (false);
}

void    Player::update( void )
{
    GLuint vertexBufferObj = 0;
    GLuint elementBufferObj = 0;
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