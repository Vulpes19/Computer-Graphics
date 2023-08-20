#include <iostream>

struct Vector
{
    Vector( void ) : x(0), y(0) {};
    Vector( float x, float y ) : x(x), y(y) {};
    Vector( Vector &copy ) : x(copy.x), y(copy.y) {};
    Vector &operator=( const Vector &copy ) {
        x = copy.x;
        y = copy.y;
    };
    float x;
    float y;
};