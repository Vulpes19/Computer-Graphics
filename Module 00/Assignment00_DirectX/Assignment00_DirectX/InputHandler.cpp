#include "InputHandler.hpp"

InputHandler::InputHandler(HWND hWnd)
{
	HRESULT res = S_OK;
	res = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	if (FAILED(res))
		throw(DirectXException(res, __FILE__, __LINE__));

	//GUID_SysKeyboard is the GUID for the system keyboard device
	res = directInput->CreateDevice(GUID_SysKeyboard, &keyboardDevice, nullptr);
	if (FAILED(res))
		throw(DirectXException(res, __FILE__, __LINE__));

	//c_dfDIKeyboard is a predefined data format for keyboard input
	res = keyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(res))
		throw(DirectXException(res, __FILE__, __LINE__));
	
	//set the cooperative level for the keyboard device 
	res = keyboardDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(res))
		throw(DirectXException(res, __FILE__, __LINE__));
	
	//aquire the keyboard device
	res = keyboardDevice->Acquire();
	if (FAILED(res))
		throw(DirectXException(res, __FILE__, __LINE__));
}

InputHandler::~InputHandler(void)
{
	if (keyboardDevice)
	{
		keyboardDevice->Unacquire();
		keyboardDevice->Release();
	}
	if (directInput)
		directInput->Release();
}

void	InputHandler::pollDevice(void)
{
	keyboardDevice->Poll();
}

void	InputHandler::addObserver(InputObserver *observer)
{
	observers.push_back(observer);
}

void	InputHandler::eraseObserver(InputObserver* observer)
{
	auto it = std::find(observers.begin(), observers.end(), observer);
	observers.erase(it);
}

void	InputHandler::notifyKeyDown(int key)
{
	for (auto observer : observers)
		observer->keyDown(key);
}

void	InputHandler::notifyKeyUp(int key)
{
	for (auto observer : observers)
		observer->keyUp(key);
}

void	InputHandler::notifyMouseMove(float x, float y)
{
	for (auto observer : observers)
		observer->mouseMove();
}