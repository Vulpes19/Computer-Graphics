#pragma once

class InputObserver
{
	public:
		virtual void	keyDown(int key) = 0;
		virtual void	keyUp(int key) = 0;
		virtual	void	mouseMove(float x, float y) = 0;
};