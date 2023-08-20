#pragma once

#include <iostream>

struct Vector
{
    Vector( void ) : x(0), y(0) {};
    Vector( float x, float y ) : x(x), y(y) {};
    Vector( Vector &copy ) : x(copy.x), y(copy.y) {};
    Vector &operator=( const Vector &copy ) {
        x = copy.x;
        y = copy.y;
        return (*this);
    };
    float x;
    float y;
};

struct Point
{
    Point( void ) : x(0.0f), y(0.0f), z(0.0f) {};
    Point( float x, float y, float z = 0.0f ) : x(x), y(y), z(z) {};
    float x;
    float y;
    float z;
};