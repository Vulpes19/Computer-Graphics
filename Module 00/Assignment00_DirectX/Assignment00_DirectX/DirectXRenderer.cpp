#include	"DirectXRenderer.hpp"

DirectXRenderer::DirectXRenderer(HWND hWnd) : hWnd(hWnd)
{
	initDirect3D();
	std::vector<Vertex> points;
	points.push_back({ 0.2f, -0.99f, 0.0f });
	points.push_back({ -0.2f, -0.99f, 0.0f });
	points.push_back({ -0.2f, -0.7f, 0.0f });
	points.push_back({ 0.2f, -0.7f, 0.0f });
	
	player = new Player(points, "VertexShader.hlsl", "PlayerPixelShader.hlsl");
	player->setDevice(device, devContext);
	player->loadShaders();
	player->createVertices();
	input = new InputHandler(hWnd);
	InputObserver* playerObs = dynamic_cast<InputObserver*>(player);
	if (playerObs)
		input->addObserver(playerObs);
	generateObstacles();
	start = time_clock::now();
}

DirectXRenderer::~DirectXRenderer(void)
{
	swapChain->Release();
	backBuff->Release();
	device->Release();
	devContext->Release();
	delete player;
	delete input;
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
	if (FAILED(hr))
		throw(DirectXException(hr, __FILE__, __LINE__));
	createRenderTarget();
}

void	DirectXRenderer::createRenderTarget(void)
{
	ID3D11Texture2D* backBuffAddr;
	HRESULT hr = S_OK;

	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffAddr);
	if (FAILED(hr))
		throw(DirectXException(hr, __FILE__, __LINE__));
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

void	DirectXRenderer::update(void)
{
	input->pollDevice();
	input->processInput();
	if (obstacles.empty())
		generateObstacles();
	end = time_clock::now();
	std::chrono::duration<double> elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	if (elapsed.count() >= 1.0)
	{
		for (auto& obstacle : obstacles)
			obstacle->update();
		start = time_clock::now();
	}
	auto it = remove_if(obstacles.begin(), obstacles.end(), [](const Obstacle* obstacle) {
		return obstacle->deadObstacle() ? true : false;
	});
	obstacles.erase(it, obstacles.end());
}

void	DirectXRenderer::render(void)
{
	float color[] = { 0.0f, 0.5f, 0.0f, 1.0f };
	devContext->ClearRenderTargetView(backBuff, color);
	//test->setDevice(device, devContext);
	player->render();
	for (auto &obstacle : obstacles)
		obstacle->render();
	HRESULT hr = swapChain->Present(0, 0);
	if (FAILED(hr))
		throw(DirectXException(hr, __FILE__, __LINE__));
}

ID3D11Device* DirectXRenderer::getDevice(void) const
{
	return (device);
}

void	DirectXRenderer::generateObstacles(void)
{
	std::random_device  random;
	std::mt19937 gen(random());
	float minX = -1.0f;
	float maxX = 1.0f;
	float maxY = 1.0f;
	std::uniform_real_distribution<float> distributionX(minX, maxX);
	std::uniform_real_distribution<float> distributionY(maxY - 0.25f, maxY);
	for (auto i = 0; i < 3; i++)
	{
		float randomX = distributionX(gen);
		float randomY = distributionY(gen);
		std::vector<Vertex> points;
		points.push_back(Vertex(randomX, randomY));
		points.push_back(Vertex(randomX + 0.15f, randomY));
		points.push_back(Vertex(randomX + 0.15f, randomY - 0.25f));
		points.push_back(Vertex(randomX, randomY - 0.25f));
		obstacles.push_back(new Obstacle(points, "VertexShader.hlsl", "ObstaclesPixelShader.hlsl"));
	}
	for (auto& obstacle : obstacles)
	{
		obstacle->setDevice(device, devContext);
		obstacle->loadShaders();
		obstacle->createVertices();
	}
}