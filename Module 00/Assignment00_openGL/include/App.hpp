#pragma once

#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include "InputHandler.hpp"
#include "Player.hpp"

class App
{
    public:
        App( int width, int height, const char* title );
        ~App( void );
        int         init( void );
        GLFWwindow* getWindow( void ) const;
        void        render( void );
    private:
        GLFWwindow* window;
        int width;
        int height;
        const char* title;
        GameObject  *player;
};