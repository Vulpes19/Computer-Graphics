#include "GameObject.hpp"

GameObject::GameObject(std::vector<Vertex> vertices) : vertices(vertices)
{
	//loadShaders();
	//createVertices();
}

GameObject::~GameObject(void)
{}

void	GameObject::loadShaders(void)
{
	ID3D10Blob* vertexBlob, * pixelBlob;
	HRESULT hr = S_OK;

	hr = D3DCompileFromFile(L"VertexShader.hlsl", nullptr, nullptr, "main", "vs_4_0", 0, 0, &vertexBlob, nullptr);
	if (FAILED(hr))
		throw(DirectXException(hr, __FILE__, __LINE__));
	hr = D3DCompileFromFile(L"PlayerPixelShader.hlsl", nullptr, nullptr, "main", "ps_4_0", 0, 0, &pixelBlob, nullptr);
	if (FAILED(hr))
		throw(DirectXException(hr, __FILE__, __LINE__));
	hr = device->CreateVertexShader(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), nullptr, &vertexShader);
	if (FAILED(hr))
		throw(DirectXException(hr, __FILE__, __LINE__));
	hr = device->CreatePixelShader(pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), nullptr, &pixelShader);
	if (FAILED(hr))
		throw(DirectXException(hr, __FILE__, __LINE__));
	devContext->VSSetShader(vertexShader, 0, 0);
	devContext->PSSetShader(pixelShader, 0, 0);
	createInputElements(vertexBlob);
}

void	GameObject::createVertices(void)
{
	//D3D11_BUFFER_DESC structure allows us to describe the buffers
	D3D11_BUFFER_DESC	vertexBufferDesc, indexBufferDesc;
	HRESULT hr = S_OK;
	Vertex	square[] =
	{
		vertices[0],
		vertices[1],
		vertices[2],
		vertices[3]
	};
	UINT	indices[]
	{
		0, 1, 2,
		0, 2, 3
	};
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(square);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(indices);
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = NULL;
	indexBufferDesc.MiscFlags = NULL;
	
	//to tell the GPU how to use provided data in indicies
	D3D11_SUBRESOURCE_DATA initData, vertexData;
	ZeroMemory(&vertexData, sizeof(vertexData));
	vertexData.pSysMem = square;
	hr = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
	if (FAILED(hr))
		throw(DirectXException(hr, __FILE__, __LINE__));
	ZeroMemory(&initData, sizeof(initData));

	initData.pSysMem = indices;
	initData.SysMemPitch = NULL;
	initData.SysMemSlicePitch = NULL;
	hr = device->CreateBuffer(&indexBufferDesc, &initData, &indexBuffer);
	if (FAILED(hr))
		throw(DirectXException(hr, __FILE__, __LINE__));
	D3D11_MAPPED_SUBRESOURCE ms;
	hr = devContext->Map(vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	if (FAILED(hr))
		throw(DirectXException(hr, __FILE__, __LINE__));
	memcpy(ms.pData, square, sizeof(square));
	devContext->Unmap(vertexBuffer, NULL);
}

void	GameObject::createInputElements(ID3D10Blob* vertexBlob)
{
	HRESULT hr = S_OK;
	D3D11_INPUT_ELEMENT_DESC inputElmDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	hr = device->CreateInputLayout(inputElmDesc, 1, vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), &layout);
	if (FAILED(hr))
		throw(DirectXException(hr, __FILE__, __LINE__));
	devContext->IASetInputLayout(layout);
}

void	GameObject::render(void)
{
	UINT	stride = sizeof(Vertex);
	UINT	offset = 0;

	devContext->IASetVertexBuffers(NULL, 1, &vertexBuffer, &stride, &offset);
	devContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, NULL);
	devContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	devContext->DrawIndexed(6, 0, 0);
	//devContext->Draw(3, 0);
}

void	GameObject::setDevice(ID3D11Device* device, ID3D11DeviceContext* devContext)
{
	this->device = device;
	this->devContext = devContext;
}