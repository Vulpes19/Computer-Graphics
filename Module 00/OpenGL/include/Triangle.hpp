#pragma once

#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <vector>

struct vec3
{
    vec3(float x, float y, float z) : x(x), y(y), z(z) {};
    float x;
    float y;
    float z;
};

class Triangle
{
    public:
        Triangle( vec3 p1, vec3 p2, vec3 p3 );
        ~Triangle( void );
        void    init( void );
        void    compileShaderProgram( void );
        void    render( void );
    private:
        std::vector< struct vec3 > points;
        // float   vec3[9];
        GLuint vertexArrObj;
        GLuint vertexBufferObj;
        GLuint IndexBufferObj;
        GLuint shaderProgram;
};