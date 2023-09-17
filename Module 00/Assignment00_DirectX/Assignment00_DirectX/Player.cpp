#include "Player.hpp"
#include <string>

Player::Player( std::vector<Vertex> vertices ) : GameObject(vertices), InputObserver()
{}

Player::~Player(void)
{}

void	Player::keyDown(BYTE key)
{
	switch (key)
	{
	case DIK_W:
		handleMovement(DIRECTION::UP);
		break;
	case DIK_S:
		handleMovement(DIRECTION::DOWN);
		break;
	case DIK_A:
		handleMovement(DIRECTION::LEFT);
		break;
	case DIK_D:
		handleMovement(DIRECTION::RIGHT);
		break;
	default:
		break;
	}
}

void	Player::handleMovement(DIRECTION dir)
{
	if (dir == DIRECTION::UP)
	{
		Vertex v = vertices[0];
		v.y += 0.1f;
		if (v.y > 1.0f)
			return;
		for (auto i = 0; i < vertices.size(); i++)
		{
			Vertex vertex = vertices[i];
			vertex.y += 0.1f;
			vertices[i] = vertex;
			OutputDebugStringW(L"Y: ");
			OutputDebugStringA(std::to_string(vertex.y).c_str());
			OutputDebugStringW(L" ");
		}
	}
	if (dir == DIRECTION::DOWN)
	{
		Vertex v = vertices[1];
		v.y -= 0.1f;
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
	}
	if (dir == DIRECTION::RIGHT)
	{
		Vertex v = vertices[0];
		v.x += 0.1f;
		if (v.x > 1.0f)
			return;
		for (auto i = 0; i < vertices.size(); i++)
		{
			Vertex vertex = vertices[i];
			vertex.x += 0.1f;
			if (vertex.x > 1.0f)
				return;
			vertices[i] = vertex;
			OutputDebugStringW(L"X: ");
			OutputDebugStringA(std::to_string(vertex.x).c_str());
			OutputDebugStringW(L" ");
		}
	}
	if (dir == DIRECTION::LEFT)
	{
		Vertex v = vertices[1];
		v.x -= 0.1f;
		if (v.x < -1.0f)
			return;
		for (auto i = 0; i < vertices.size(); i++)
		{
			Vertex vertex = vertices[i];
			vertex.x -= 0.1f;
			if (vertex.x < -1.0f)
				return;
			vertices[i] = vertex;
			OutputDebugStringW(L"X: ");
			OutputDebugStringA(std::to_string(vertex.x).c_str());
			OutputDebugStringW(L" ");
		}
	}
	OutputDebugStringW(L"\n");
	createVertices();
}