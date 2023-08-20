#pragma once

#include "GameObject.hpp"

class Player : public GameObject
{
    public:
        Player( Vector position, Vector velocity, std::vector<Point> &points ) : GameObject( position, velocity, points ) {};
        virtual ~Player( void );
        virtual const char *loadShaderFromFile( enum SHADER );
};