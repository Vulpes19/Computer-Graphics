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

void	InputHandler::processInput(void)
{
	BYTE  diKeys[256];
	if (keyboardDevice->GetDeviceState(256, diKeys) == DI_OK)
	{
		BYTE key = '0';
		if (diKeys[DIK_W] & 0x80)
			key = DIK_W;
		if (diKeys[DIK_S] & 0x80)
			key = DIK_S;
		if (diKeys[DIK_A] & 0x80)
			key = DIK_A;
		if (diKeys[DIK_D] & 0x80)
			key = DIK_D;
		if (key != '0')
		{
			if (!keyWasPressed)  // Only notify observers if the key wasn't pressed before
			{
				OutputDebugStringW(L"a key is pressed\n");
				for (auto observer : observers)
					observer->keyDown(key);
			}
			keyWasPressed = true;  // Set the flag to true to indicate the key was pressed
		}
		else
		{
			keyWasPressed = false;  // Reset the flag if no key is currently pressed
		}
	}
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
		observer->mouseMove(x, y);
}