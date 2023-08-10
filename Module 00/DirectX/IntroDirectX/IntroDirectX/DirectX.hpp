#pragma once

#include <Windows.h>
#include <Windowsx.h>
#include <WinBase.h>
#include <d3d11.h>
#include <d3d10.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3d10.lib")

extern IDXGISwapChain	*swapChain;       //pointer to swap chain interface
extern ID3D11Device* device;			  //pointer to Direct3D device interface
extern ID3D11DeviceContext* devContext;  //pointer to Direct3D device context

void	initDirect3D(HWND hWnd);
void	clean(void);