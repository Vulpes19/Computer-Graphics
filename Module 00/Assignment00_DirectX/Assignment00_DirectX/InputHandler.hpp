#pragma once

#include "DirectX.hpp"
#include "InputObserver.hpp"
#include <vector>

class InputHandler
{
	public:
		InputHandler(HWND);
		~InputHandler(void);
		void	pollDevice(void);
		void	addObserver(InputObserver*);
		void	eraseObserver(InputObserver*);
		void	processInput(void);
		void	notifyKeyDown(int key);
		void	notifyKeyUp(int key);
		void	notifyMouseMove(float x, float y);
	private:
		IDirectInput8	*directInput = nullptr;
		IDirectInputDevice8* keyboardDevice = nullptr;
		std::vector<InputObserver*> observers;
		bool keyWasPressed = false;
};