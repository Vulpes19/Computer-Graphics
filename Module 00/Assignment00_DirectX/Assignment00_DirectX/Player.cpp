#include "Player.hpp"

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
		OutputDebugStringW(L"W is pressed\n");
		break;
	case DIK_S:
		OutputDebugStringW(L"S is pressed\n");
		break;
	case DIK_A:
		OutputDebugStringW(L"A is pressed\n");
		break;
	case DIK_D:
		OutputDebugStringW(L"D is pressed\n");
		break;
	default:
		break;
	}
}

void	Player::handleMovement(DIRECTION dir)
{
	if (dir == DIRECTION::UP)
	{
		for (auto i = 0; i < vertices.size(); i++)
		{
			Vertex vertex = vertices[i];
			vertex.y += 0.1f;
			vertices[i] = vertex;
		}
	}
	createVertices();
}