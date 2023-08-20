#include "GameObject.hpp"

class Obstacle : public GameObject
{
    public:
        Obstacle( void ) : GameObject( Vector(2f, 2f), Vector(2f, 2f) ) {};
        virtual ~Obstacle( void );
};