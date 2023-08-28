#pragma once

#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include "InputHandler.hpp"
#include "Player.hpp"
#include "Obstacle.hpp"
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>

class App
{
	public:
		typedef std::chrono::high_resolution_clock time_clock;
		App( int width, int height, const char* title );
		~App( void );
		int         init( void );
		GLFWwindow* getWindow( void ) const;
		void        render( void );
		void		generateObstacles( void );
	private:
		GLFWwindow*					window;
		int							width;
		int							height;
		const char					*title;
		std::unique_ptr<GameObject>	player;
		std::vector<std::unique_ptr<GameObject>>	obstacles;
		time_clock::time_point start;
		time_clock::time_point end;
};