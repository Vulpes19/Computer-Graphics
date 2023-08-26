#include "Shape.hpp"

Shape::Shape(void)
{
	this->devContext = nullptr;
	this->device = nullptr;
	this->layout = nullptr;
	this->pixelShader = nullptr;
	this->vertexBuffer = nullptr;
	this->vertexShader = nullptr;
}

Shape::~Shape(void)
{
	vertexShader->Release();
	pixelShader->Release();
}

void	Shape::setDev(ID3D11Device* device, ID3D11DeviceContext* devContext)
{
	this->device = device;
	this->devContext = devContext;
}

void	Shape::loadShaders(void)
{
	ID3D10Blob *vertexBlob, *pixelBlob;
	HRESULT res = S_OK;
	
	//load and compile the two shaders
	//res = D3DCompileFromFile(L"VertexShader.hlsl", nullptr, nullptr, "main", "vs_4_0", 0, 0, &vertexBlob, nullptr );

	res = D3DCompileFromFile(L"shaders.shader", nullptr, nullptr, "VShader", "vs_4_0", 0, 0, &vertexBlob, nullptr);
	if (FAILED(res))
		throw(DirectXexcp(res, __FILE__, __LINE__));
	//res = D3DCompileFromFile(L"PixelShader.hlsl", nullptr, nullptr, "main", "vs_4_0", 0, 0, &pixelBlob, nullptr);
	res = D3DCompileFromFile(L"shaders.shader", nullptr, nullptr, "PShader", "ps_4_0", 0, 0, &pixelBlob, nullptr);
	if (FAILED(res))
		throw(DirectXexcp(res, __FILE__, __LINE__));
	
	//encapsulate both shaders into shader objects
	res = device->CreateVertexShader(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), nullptr, &vertexShader);
	if (FAILED(res))
		throw(DirectXexcp(res, __FILE__, __LINE__));
	res = device->CreatePixelShader(pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), nullptr, &pixelShader);
	if (FAILED(res))
		throw(DirectXexcp(res, __FILE__, __LINE__));

	devContext->VSSetShader(vertexShader, 0, 0);
	devContext->PSSetShader(pixelShader, 0, 0);
	
	createInputElements(vertexBlob);
}

void	Shape::createVertices(void)
{
	D3D11_BUFFER_DESC bd;
	HRESULT res = S_OK;
	Vertex triangle[] =
	{
		{0.0f, 0.5f, 0.0f, DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{-0.25f, -0.5f, 0.0f, DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
		{-0.45f, -0.5f, 0.0f, DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
	};

	ZeroMemory(&bd, sizeof(bd));

	//when creating vertex struct the data is stored in system memory, we need it
	//to be in video memory
	bd.Usage = D3D11_USAGE_DYNAMIC; //write access by CPU and GPU
	bd.ByteWidth = sizeof(Vertex) * 3;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //allow CPU to write in buffer

	res = device->CreateBuffer(&bd, nullptr, &vertexBuffer); //create the buffer
	if (FAILED(res))
		throw(DirectXexcp(res, __FILE__, __LINE__));

	D3D11_MAPPED_SUBRESOURCE ms;
	res = devContext->Map(vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	if (FAILED(res))
		throw(DirectXexcp(res, __FILE__, __LINE__));
	memcpy(ms.pData, triangle, sizeof(triangle));
	devContext->Unmap(vertexBuffer, NULL);
}

void	Shape::createInputElements(ID3D10Blob *vertexBlob)
{
	HRESULT res = S_OK;
	D3D11_INPUT_ELEMENT_DESC inputElmDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	res = device->CreateInputLayout(inputElmDesc, 2, vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), &layout);
	if (FAILED(res))
		throw(DirectXexcp(res, __FILE__, __LINE__));
	devContext->IASetInputLayout(layout);
}

void	Shape::render(void)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	devContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	devContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	devContext->Draw(3, 0);
}