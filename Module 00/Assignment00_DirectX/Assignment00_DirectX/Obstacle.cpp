#include "Obstacle.hpp"

Obstacle::Obstacle(std::vector<Vertex> vertices, const char *vShaderPath = "VertexShader.hlsl", const char *pShaderPath = "ObstaclePixelShader.hlsl") : GameObject(vertices, vShaderPath, pShaderPath)
{}

Obstacle::~Obstacle(void)
{}

void	Obstacle::update(int &score)
{
	Vertex v = vertices[0];
	if (v.y < -1.0f)
	{
		score += 5;
		OutputDebugStringA("The score is ");
		OutputDebugStringA(std::to_string(score).c_str());
		OutputDebugStringA("\n");
		isDead = true;
		return;
	}
	for (auto i = 0; i < vertices.size(); i++)
	{
		Vertex vertex = vertices[i];
		vertex.y -= 0.1f;
		vertices[i] = vertex;
	}
	createVertices();
}

void	Obstacle::handleCollision(std::vector<Vertex> playerPos, int& score)
{
	if (((vertices[2].x >= playerPos[0].x && vertices[2].x <= playerPos[1].x) || (vertices[3].x >= playerPos[0].x && vertices[3].x <= playerPos[1].x))
		&& (vertices[2].y <= playerPos[0].y && vertices[2].y >= playerPos[3].y))
	{
		isDead = true;
		score -= 5;
		OutputDebugStringA("The score is ");
		OutputDebugStringA(std::to_string(score).c_str());
		OutputDebugStringA("\n");
		return;
	}
}

bool	Obstacle::deadObstacle(void) const
{
	return (isDead);
}