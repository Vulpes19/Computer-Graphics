#pragma once

#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include "Vector.hpp"
#include <vector>
#include <fstream>
#include "InputHandler.hpp"

#define WIDTH 800
#define HEIGHT 600

enum SHADER
{
	VERTEX,
	FRAGMENT
};

class GameObject
{
	public:
		GameObject( void );
		GameObject( std::vector<Point> &, const char *, const char * );
		virtual ~GameObject( void );
		std::string		loadShaderFromFile( enum SHADER );
		void			init( void );
		void			compileShaderProgram( void );
		virtual void    draw( void );
		virtual bool    handleMovement( void ) { return (false); };
		virtual void    update( void ) {};
        virtual	bool    deadObstacle( void ) const { return (false); };
	protected:
		std::vector<Point>	points;
		float   			vertices[12];
		float				moveSpeed;
		GLuint				vertexArrObj = 0;
		GLuint				shaderProgram = 0;
		GLuint				vertexBufferObj = 0;
    	GLuint				elementBufferObj = 0;
		const char			*vertexShPath;
		const char			*fragmentShPath;
        // bool    isDead = false;
};