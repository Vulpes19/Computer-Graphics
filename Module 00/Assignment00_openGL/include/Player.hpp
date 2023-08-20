#include "GameObject.hpp"

class Player : public GameObject
{
    public:
        Player( void ) : GameObject( Vector(2f, 2f), Vector(2f, 2f) ) {};
        virtual ~Player( void );
        virtual const char *loadShaderFromFile( enum SHADER );
};