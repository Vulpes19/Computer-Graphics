#pragma once

#include <iostream>
#include <glad.h>
#include <glfw3.h>

class Window
{
    public:
        Window(int width, int height, const char* title);
        ~Window( void );
        int init( void );
        GLFWwindow* getWindow( void ) const;
        // void clear( void );
        // void update( void );
        void render( void );
        // void handleEvents( void );
    private:
        GLFWwindow* window;
        int width;
        int height;
        const char* title;
};