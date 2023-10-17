#pragma once

#include "GameObject.hpp"

class Player : public GameObject
{
    public:
        Player( std::vector<Point> &, const char *, const char * );
        virtual ~Player( void );
        bool    handleMovement( void ) override;
        void    update( void ) override;
        std::vector<float>    getVertices( void ) const override;
};