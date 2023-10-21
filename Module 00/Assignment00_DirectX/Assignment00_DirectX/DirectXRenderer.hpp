#pragma once

#include "DirectX.hpp"
#include "GameObject.hpp"
#include "InputHandler.hpp"
#include "Player.hpp"
#include "Obstacle.hpp"

class DirectXRenderer
{
	public:
		typedef std::chrono::high_resolution_clock time_clock;
		DirectXRenderer(HWND hWnd);
		~DirectXRenderer(void);
		void	update(void);
		void	render(void);
		ID3D11Device* getDevice(void) const;
		void	generateObstacles(void);
	private:
		HWND hWnd  = nullptr;
		IDXGISwapChain* swapChain = nullptr;
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* devContext = nullptr;
		ID3D11RenderTargetView* backBuff = nullptr;
		GameObject* player;
		InputHandler	*input;
		std::vector<Obstacle *> obstacles;
		time_clock::time_point	start;
		time_clock::time_point	end;
		int	score = 0;
		void	initDirect3D(void);
		void	createRenderTarget(void);
		void	setViewport(void);
};