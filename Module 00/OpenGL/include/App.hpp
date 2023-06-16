#pragma once

#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include "Triangle.hpp"

class App
{
    public:
        App(int width, int height, const char* title);
        ~App( void );
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
        Triangle *tr;
};