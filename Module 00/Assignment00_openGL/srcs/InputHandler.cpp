#include "InputHandler.hpp"

InputHandler *InputHandler::instancePtr = nullptr;

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
    {
        keyStates[key] = GLFW_RELEASE;
        return (true);
    }
    else
        return (false);
}

void    InputHandler::keyCallBack(GLFWwindow *, int key, int, int action, int )
{
    InputHandler::getInstance()->setKeyState(key, action);
}

void    InputHandler::setKeyState( int key, int action )
{
    keyStates[key] = action;
}