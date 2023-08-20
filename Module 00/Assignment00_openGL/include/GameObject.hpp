#pragma once

#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include "Vector.hpp"
#include <vector>

enum SHADER
{
    VERTEX,
    FRAGMENT
};

class GameObject
{
    public:
        GameObject( void );
        GameObject( Vector, Vector, std::vector<Point> & );
        virtual ~GameObject( void );
        virtual const char *loadShaderFromFile( enum SHADER ) { return nullptr; };
        void    compileShaderProgram( void );
        virtual void    draw( void );
        virtual void    update( void ) {};
    protected:
        Vector  position;
        Vector  velocity;
        std::vector<Point> points;
        float   vertices[12];
        GLuint  vertexArrObj;
        GLuint  shaderProgram;
};