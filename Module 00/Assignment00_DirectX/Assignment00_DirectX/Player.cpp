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