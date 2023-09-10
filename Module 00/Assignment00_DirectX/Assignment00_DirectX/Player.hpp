#pragma once

#include "GameObject.hpp"
#include "InputObserver.hpp"

class Player : public GameObject, public InputObserver 
{
	public:
		Player(std::vector<Vertex> points);
		~Player(void);
};