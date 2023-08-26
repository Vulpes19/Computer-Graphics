#include "DirectXRenderer.hpp"
#include <string>

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

	//window size and client size
	RECT size = { 0, 0, 800, 600 };
	AdjustWindowRect(&size, WS_OVERLAPPEDWINDOW, FALSE);

	//create the window
	window = CreateWindowEx(
		NULL,
		L"WindowClass1",		//name of the window class
		L"Hello Window !",		//title of the window
		WS_OVERLAPPEDWINDOW,	//window style
		300,					//x pos of the window
		300,					//y pos of the window
		size.right - size.left,	//width of the window
		size.bottom - size.top,	//height of the window
		NULL,					//parent window
		NULL,					//menus
		hInstance,				// application handle
		NULL					//used with multiple windows
	);

	//display window
	ShowWindow(window, nShowCmd);

	DirectXRenderer wnd(window);
	//this struct holds windows events
	MSG msg = { 0 };
	try
	{
		//main loop
		while (TRUE)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				//translate the message into the right format
				TranslateMessage(&msg);

				//send the message to the WindowProc function
				DispatchMessage(&msg);
				if (msg.message == WM_QUIT)
					break;
			}
			else
			{
				wnd.render();
			}
		}
	}
	catch (const DirectXexcp &e)
	{
		OutputDebugStringA(e.what());
		OutputDebugStringA("\n");
		OutputDebugStringA("In file: ");
		OutputDebugStringA(e.GetFile());
		OutputDebugStringA("\n");
		OutputDebugStringA("In line: ");
		OutputDebugStringA(std::to_string(e.getLine()).c_str());
		OutputDebugStringA("\n");
	}

	return (msg.wParam);
}