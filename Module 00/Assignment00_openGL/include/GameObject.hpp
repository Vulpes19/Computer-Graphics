#include "App.hpp"
#include "Vector.hpp"

enum SHADER
{
    VERTEX,
    FRAGMENT
};

class GameObject
{
    public:
        GameObject( void );
        GameObject( Vector &, Vector & );
        virtual ~GameObject( void );
        virtual const char *loadShaderFromFile( enum SHADER ) = 0;
        void    compileShaderProgram( void );
        virtual void    draw( void );
        virtual void    update( void );
    protected:
        Vector  position;
        Vector  velocity;
        float   vertices[12];
        GLuint  vertexArrObj;
        GLuint  shaderProgram;
};