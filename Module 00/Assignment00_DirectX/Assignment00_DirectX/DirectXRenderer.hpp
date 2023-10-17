#pragma once

#include "DirectX.hpp"
#include "GameObject.hpp"
#include "InputHandler.hpp"
#include "Player.hpp"

class DirectXRenderer
{
	public:
		DirectXRenderer(HWND hWnd);
		~DirectXRenderer(void);
		void	update(void);
		void	render(void);
		ID3D11Device* getDevice(void) const;
	private:
		HWND hWnd  = nullptr;
		IDXGISwapChain* swapChain = nullptr;
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* devContext = nullptr;
		ID3D11RenderTargetView* backBuff = nullptr;
		GameObject* player;
		InputHandler	*input;
		void	initDirect3D(void);
		void	createRenderTarget(void);
		void	setViewport(void);
};