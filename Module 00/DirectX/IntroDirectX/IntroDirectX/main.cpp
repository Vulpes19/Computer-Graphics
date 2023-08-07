#include <windows.h>
#include <winbase.h>

int WINAPI	WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	MessageBox(NULL, L"Learning DirectX 11 :)", L"Hello Window", MB_ICONEXCLAMATION | MB_OK);
	return (0);
}