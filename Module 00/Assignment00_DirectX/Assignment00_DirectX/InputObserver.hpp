#pragma once

//observer pattern

class InputObserver
{
	public:
		virtual void	keyDown(BYTE key) = 0;
		virtual void	keyUp(int key) = 0;
		virtual	void	mouseMove(float x, float y) = 0;
};