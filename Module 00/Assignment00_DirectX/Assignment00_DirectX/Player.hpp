#pragma once

#include "GameObject.hpp"

class Player : public GameObject
{
	public:
		Player(std::vector<Vertex> points);
		~Player(void);
};