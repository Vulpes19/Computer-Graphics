#pragma once

#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <vector>

struct vec3
{
    vec3( void ) : x(0.0f), y(0.0f), z(0.0f) {};
    vec3(float x, float y, float z) : x(x), y(y), z(z) {};
    float x;
    float y;
    float z;
};

class Draw
{
    public:
        Draw( void );
        ~Draw( void );
        void    initTriangle( vec3, vec3, vec3 );
        void    initRectangle( vec3, vec3, vec3, vec3 );
        void    initTwoTriangles( vec3, vec3, vec3, vec3, vec3 );
        void    initTwoTrianglesDifferentBuf( vec3, vec3, vec3, vec3, vec3 );
        void    compileShaderProgram( void );
        void    renderTriangle( void );
        void    renderTwoTriangles( void );
        void    renderRectangle( void );
    private:
        // std::vector< struct vec3 > points;
        float vertices[9];
        GLuint vertexArrObj;
        GLuint vertexArrObjs[2];
        GLuint vertexBufferObj;
        GLuint vertexBufferObjs[2];
        GLuint elementBufferObj;
        GLuint IndexBufferObj;
        GLuint shaderProgram1;
        GLuint shaderProgram2;
};