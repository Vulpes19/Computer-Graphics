#include	"DirectXRenderer.hpp"

DirectXRenderer::DirectXRenderer(HWND hWnd) : hWnd(hWnd)
{
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
	DXGI_SWAP_CHAIN_DESC	swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 4;
	swapChainDesc.Windowed = TRUE;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		NULL,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&swapChain,
		&device,
		nullptr,
		&devContext
	);

	createRenderTarget();
}

void	DirectXRenderer::createRenderTarget(void)
{
	ID3D11Texture2D* backBuffAddr;
	HRESULT hr = S_OK;

	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffAddr);
	if ( backBuffAddr != 0 )
		hr = device->CreateRenderTargetView(backBuffAddr, NULL, &backBuff);
	backBuffAddr->Release();
	devContext->OMSetRenderTargets(1, &backBuff, nullptr);
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
	HRESULT hr = swapChain->Present(0, 0);
}

ID3D11Device* DirectXRenderer::getDevice(void) const
{
	return (device);
}