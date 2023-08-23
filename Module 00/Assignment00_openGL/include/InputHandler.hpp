#pragma once

#include <iostream>
#include <glad.h>
#include <glfw3.h>

class InputHandler
{
    public:
        static InputHandler *getInstance( void );
        bool    isKeyPressed( int key );
        static void    keyCallBack( GLFWwindow *, int key, int , int action, int );
        void    setKeyState( int key, int action );
    private:
        InputHandler( void );
        static InputHandler *instancePtr;
        uint8_t keyStates[GLFW_KEY_LAST + 1] = {0};
};

// InputHandler *InputHandler::instancePtr = nullptr;