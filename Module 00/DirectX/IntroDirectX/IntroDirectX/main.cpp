#include <windows.h>
#include <WinBase.h>
#include <windowsx.h>

LRESULT CALLBACK WindowProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return (0);
		}
		break;
	};
	return (DefWindowProc(hWnd, message, wParam, lParam));
}

int WINAPI	WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	//the handle for the window
	HWND window;
	//struct that holds information for the window class
	WNDCLASSEX windowClass;

	//clears the window class
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

	//filling the struct with information
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.lpszClassName = L"WindowClass1";

	//register the window class
	RegisterClassEx(&windowClass);

	//create the window
	window = CreateWindowEx(
		NULL,
		L"WindowClass1",		//name of the window class
		L"Hello Window !",		//title of the window
		WS_OVERLAPPEDWINDOW,	//window style
		300,					//x pos of the window
		300,					//y pos of the window
		600,					//width of the window
		300,					//height of the window
		NULL,					//parent window
		NULL,					//menus
		hInstance,				// application handle
		NULL					//used with multiple windows
	);

	//display window
	ShowWindow(window, nShowCmd);

	//this struct holds windows events
	MSG message;

	//main loop
	while (GetMessage(&message, NULL, 0, 0))
	{
		//translate the message into the right format
		TranslateMessage(&message);

		//send the message to the WindowProc function
		DispatchMessage(&message);
	}
	return (0);
}