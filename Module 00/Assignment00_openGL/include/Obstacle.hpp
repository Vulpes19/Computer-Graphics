#include "GameObject.hpp"

class Obstacle : public GameObject
{
    public:
        Obstacle( std::vector<Point>, const char *, const char * );
        virtual ~Obstacle( void );
        void            update( void ) override;
        bool            deadObstacle( void ) const override;
        void            handleCollision( std::vector<float>, int & ) override;
    private:
        bool    isDead = false;
};