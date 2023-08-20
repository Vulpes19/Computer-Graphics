#include "InputHandler.hpp"

InputHandler::InputHandler( void )
{}

InputHandler *InputHandler::getInstance( void )
{
    if ( instancePtr == nullptr )
        instancePtr = new InputHandler();
    return ( instancePtr );
}

bool    InputHandler::isKeyPressed( int key )
{
    if ( keyStates[key] == GLFW_PRESS )
        return (true);
    else
        return (false);
}

void    InputHandler::keyCallBack(GLFWwindow *, int key, int, int action, int )
{
    if  ( action == GLFW_PRESS )
        keyStates[key] = action;
}
