#include "DirectX.hpp"

DirectXRenderer::DirectXRenderer(HWND hWnd) : hWnd(hWnd)
{
	width = 800;
	height = 600;
	initDirect3D();
}

DirectXRenderer::~DirectXRenderer(void)
{
	swapChain->Release();
	backBuff->Release();
	device->Release();
	devContext->Release();
}

void	DirectXRenderer::initDirect3D(void)
{
	//struct that holds information about the swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	//swap chain description
	swapChainDesc.BufferCount = 1;                                  //one back buffer
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;   //use 32-bit color
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    //how swap chain is to be used
	swapChainDesc.OutputWindow = hWnd;                              //the window to be used
	swapChainDesc.SampleDesc.Count = 4;                             //how many multisamples
	swapChainDesc.Windowed = TRUE;                                  //windowed/full-screen mode

	HRESULT res = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&swapChain,
		&device,
		NULL,
		&devContext
	);

	if (FAILED(res))
	{
		throw(DirectXexcp(res, __FILE__, __LINE__));
	}
	createRenderTarget();
}

void	DirectXRenderer::createRenderTarget(void)
{
	ID3D11Texture2D* backBuffAddr;
	HRESULT	res;
	
	res = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffAddr);
	if (FAILED(res))
	{
		throw(DirectXexcp(res, __FILE__, __LINE__));
	}
	res = device->CreateRenderTargetView(backBuffAddr, NULL, &backBuff);
	if (FAILED(res))
	{
		throw(DirectXexcp(res, __FILE__, __LINE__));
	}
	backBuffAddr->Release();
	devContext->OMSetRenderTargets(1, &backBuff, NULL);
	setViewport();
}

void	DirectXRenderer::setViewport(void)
{
	D3D11_VIEWPORT	viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 800;
	viewport.Height = 600;

	devContext->RSSetViewports(1, &viewport);
}

void	DirectXRenderer::render(void)
{
	float color[] = { 1.0f, 0.5f, 0.0f, 1.0f };
	devContext->ClearRenderTargetView(backBuff, color);
	HRESULT res = swapChain->Present(0, 0);
	if (FAILED(res))
	{
		throw(DirectXexcp(res, __FILE__, __LINE__));
	}
}