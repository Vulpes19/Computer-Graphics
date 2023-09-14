#pragma once

#include "GameObject.hpp"
#include "InputObserver.hpp"

class Player : public GameObject, public InputObserver 
{
	public:
		Player(std::vector<Vertex>);
		~Player(void);
		void	keyDown(BYTE) override;
		void	keyUp(int) override {};
		void	mouseMove(float, float) override {};
};