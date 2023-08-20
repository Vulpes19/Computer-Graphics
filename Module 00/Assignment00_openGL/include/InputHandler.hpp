#pragma once

#include "App.hpp"

class InputHandler
{
    public:
        static InputHandler *getInstance( void );
        bool    isKeyPressed( int key );
        void    keyCallBack( GLFWwindow *, int key, int , int action, int );
    private:
        InputHandler( void );
        static InputHandler *instancePtr;
        uint8_t keyStates[GLFW_KEY_LAST + 1] = {0};
};

InputHandler *InputHandler::instancePtr = nullptr;