#include "Obstacle.hpp"

Obstacle::Obstacle(std::vector<Vertex> vertices, const char *vShaderPath = "VertexShader.hlsl", const char *pShaderPath = "ObstaclePixelShader.hlsl") : GameObject(vertices, vShaderPath, pShaderPath)
{}

Obstacle::~Obstacle(void)
{}

void	Obstacle::update(void)
{
	Vertex v = vertices[1];
	if (v.y < -1.0f)
		return;
	for (auto i = 0; i < vertices.size(); i++)
	{
		Vertex vertex = vertices[i];
		vertex.y -= 0.1f;
		vertices[i] = vertex;
		OutputDebugStringW(L"Y: ");
		OutputDebugStringA(std::to_string(vertex.y).c_str());
		OutputDebugStringW(L" ");
	}
	createVertices();
}

bool	Obstacle::deadObstacle(void) const
{
	return (isDead);
}