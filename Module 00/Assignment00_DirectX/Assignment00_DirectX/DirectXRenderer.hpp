#pragma once

#include "DirectX.hpp"

class DirectXRenderer
{
	public:
		DirectXRenderer(HWND hWnd);
		~DirectXRenderer(void);
		void	render(void);
		ID3D11Device* getDevice(void) const;
	private:
		HWND hWnd  = nullptr;
		IDXGISwapChain* swapChain = nullptr;
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* devContext = nullptr;
		ID3D11RenderTargetView* backBuff = nullptr;
		void	initDirect3D(void);
		void	createRenderTarget(void);
		void	setViewport(void);
};