#include "DirectX.hpp"

IDXGISwapChain* swapChain;       //pointer to swap chain interface
ID3D11Device* device;			  //pointer to Direct3D device interface
ID3D11DeviceContext* devContext;

void	initDirect3D(HWND hWnd)
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

	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&swapChain,
		&device,
		NULL,
		&devContext
	);

}

void	clean(void)
{
	swapChain->Release();
	device->Release();
	devContext->Release();
}