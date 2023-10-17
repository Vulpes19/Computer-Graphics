#pragma once

#include "GameObject.hpp"

class Obstacle : public GameObject
{
	public:
		Obstacle(std::vector<Vertex>, const char *, const char *);
		virtual ~Obstacle(void);
		void	update(void) override;
		bool	deadObstacle(void) const override;
	private:
		bool	isDead = false;
};