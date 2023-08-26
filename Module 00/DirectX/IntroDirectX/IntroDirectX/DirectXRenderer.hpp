#pragma once

#include "DirectX.hpp"
#include "Shape.hpp"

class DirectXRenderer
{
	public:
		DirectXRenderer(HWND hWnd);
		~DirectXRenderer(void);
		void	render(void);
		ID3D11Device* getDevice(void) const;
	private:
		HWND hWnd;
		size_t	width;
		size_t	height;
		IDXGISwapChain* swapChain;        //pointer to swap chain interface
		ID3D11Device* device;			  //pointer to Direct3D device interface
		ID3D11DeviceContext* devContext;  //pointer to Direct3D device context
		ID3D11RenderTargetView* backBuff; //pointer to back buffer
		Shape	triangle;
		void	initDirect3D(void);
		void	createRenderTarget(void);
		void	setViewport();
};