#pragma once

#include "GameObject.hpp"

class Obstacle : public GameObject
{
	public:
		Obstacle(std::vector<Vertex>);
		virtual ~Obstacle(void);
		void	loadShaders(void) override;
		void	update(void) override;
		bool	deadObstacle(void) const override;
	private:
		bool	isDead = false;
};