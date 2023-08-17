#pragma once

#include <Windows.h>
#include <Windowsx.h>
#include <WinBase.h>
#include <d3d11.h>
#include <d3d10.h>
#include "ErrorHandling.hpp"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3d10.lib")


class DirectXRenderer
{
	private:
		HWND hWnd;
		size_t	width;
		size_t	height;
		IDXGISwapChain* swapChain;        //pointer to swap chain interface
		ID3D11Device* device;			  //pointer to Direct3D device interface
		ID3D11DeviceContext* devContext;  //pointer to Direct3D device context
		ID3D11RenderTargetView* backBuff; //pointer to back buffer
		void	initDirect3D(void);
		void	createRenderTarget(void);
		void	setViewport();
	public:
		DirectXRenderer(HWND hWnd);
		~DirectXRenderer(void);
		void	render(void);
};