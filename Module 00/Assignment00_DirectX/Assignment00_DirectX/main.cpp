#include "DirectX.hpp"
#include "DirectXRenderer.hpp"

LRESULT	CALLBACK	WindowProc(
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
	}
	return (DefWindowProcW(hWnd, message, wParam, lParam));
}

int	WINAPI	WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR		lpCmdLine,
	int	nShowCmd
)
{
	HWND	window;
	WNDCLASSEX	windowClass;

	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.lpszClassName = L"WindowClass1";
	RegisterClassEx(&windowClass);

	RECT size = { 0, 0, 800, 600 };
	AdjustWindowRect(&size, WS_OVERLAPPEDWINDOW, FALSE);
	
	window = CreateWindowEx(
		NULL,
		L"WindowClass1",
		L"Assignment00-DirectX",
		WS_OVERLAPPEDWINDOW,
		300,
		300,
		size.right - size.left,
		size.bottom - size.top,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(window, nShowCmd);
	MSG msg = { 0 };
	try
	{
		DirectXRenderer App(window);

		while (TRUE)
		{
			if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
				if (msg.message == WM_QUIT)
					break;
			}
			else
			{
				App.render();
				App.update();
			}
		}
	}
	catch (const DirectXException& e)
	{
		OutputDebugStringA(e.what());
		OutputDebugStringA("\nfile ");
		OutputDebugStringA(e.getFile());
		OutputDebugStringA(", ");
		OutputDebugStringA(std::to_string(e.getLine()).c_str());
		OutputDebugStringA("\n");
	}
	return (msg.wParam);
}