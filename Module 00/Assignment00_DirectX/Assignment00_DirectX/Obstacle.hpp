#pragma once

#include "GameObject.hpp"

class Obstacle : public GameObject
{
	public:
		Obstacle(std::vector<Vertex>, const char *, const char *);
		virtual ~Obstacle(void);
		void	update(int &) override;
		void	handleCollision(std::vector<Vertex>, int&);
		bool	deadObstacle(void) const override;
	private:
		bool	isDead = false;
};