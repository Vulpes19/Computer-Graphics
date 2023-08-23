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
    // NormalizedCoordinate = (2 * ScreenCoordinate) / WindowSize - 1
    float normalizedTopBorder = 1.15f;
    float normalizedBottomBorder = -1.15f;
    float normalizedLeftBorder = -1.15f;
    float normalizedRightBorder = 1.15f;
    int     directionX = 0;
    int     directionY = 0;


    if ( InputHandler::getInstance()->isKeyPressed(GLFW_KEY_W) )
        directionY = 1;
    if ( InputHandler::getInstance()->isKeyPressed(GLFW_KEY_S) )
        directionY = -1;
    if ( InputHandler::getInstance()->isKeyPressed(GLFW_KEY_A) )
        directionX = -1;
    if ( InputHandler::getInstance()->isKeyPressed(GLFW_KEY_D) )
        directionX = 1;
    if ( directionX == 0 && directionY == 0 )
        return (false);
    for ( auto i = 0; i < 12; i += 3 )
    {
        float posX = vertices[i] + moveSpeed * directionX;
        float posY = vertices[i + 1] + moveSpeed * directionY;
        if ( posX > normalizedRightBorder || posX < normalizedLeftBorder ||
            posY > normalizedTopBorder || posY < normalizedBottomBorder )
        {
            std::cout << normalizedLeftBorder << " " << posX << " " << normalizedRightBorder << std::endl;
            std::cout << normalizedTopBorder << " " << posY << " " << normalizedBottomBorder << std::endl;
            return ( false );
        }
    }
    for ( auto i = 0; i < 12; i += 3 )
    {
        vertices[i] += moveSpeed * directionX;
        vertices[i + 1] += moveSpeed * directionY;
    }
    return (true);
}

void    Player::update( void )
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