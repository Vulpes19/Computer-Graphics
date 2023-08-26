#pragma once

#include "GameObject.hpp"

class Player : public GameObject
{
    public:
        Player( std::vector<Point> &points, const char *vShader, const char *fShader );
        virtual ~Player( void );
        virtual bool    handleMovement( void );
        virtual void    update( void );
};