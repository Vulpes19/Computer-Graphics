#pragma once

#include "GameObject.hpp"

class Player : public GameObject
{
    public:
        Player( std::vector<Point> &points, const char *vShader, const char *fShader );
        virtual ~Player( void );
        bool    handleMovement( void ) override;
        void    update( void ) override;
};