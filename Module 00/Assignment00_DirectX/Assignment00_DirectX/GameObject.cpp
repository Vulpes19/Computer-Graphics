#include "GameObject.hpp"

GameObject::GameObject(std::vector<Vertex> points) : points(points)
{}

GameObject::~GameObject(void)
{}

void	GameObject::loadShaders(void)
{
	ID3D10Blob* vertexBlob, * pixelBlob;
	HRESULT hr = S_OK;

	hr = D3DCompileFromFile(L"VertexShader.hlsl", nullptr, nullptr, "main", "vs_4_0", 0, 0, &vertexBlob, nullptr);

	hr = D3DCompileFromFile(L"PixelShader.hlsl", nullptr, nullptr, "main", "ps_4_0", 0, 0, &pixelBlob, nullptr);
	
	hr = device->CreateVertexShader(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), nullptr, &vertexShader);
	hr = device->CreatePixelShader(pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), nullptr, &pixelShader);
	devContext->VSSetShader(vertexShader, 0, 0);
	devContext->PSSetShader(pixelShader, 0, 0);
	createInputElements(vertexBlob);
}

void	GameObject::createVertices(void)
{
	D3D11_BUFFER_DESC	bd;
	HRESULT hr = S_OK;
	Vertex	triangle[] =
	{
		points[0],
		points[1],
		points[2],
		points[3]
	};
	int	indices[]
	{
		0, 1, 2,
		0, 2, 3
	};
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * 3;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	hr = device->CreateBuffer(&bd, nullptr, &vertexBuffer);
	D3D11_MAPPED_SUBRESOURCE ms;

}

void	GameObject::createInputElements(ID3D10Blob* bl)
{

}

void	GameObject::render(void)
{}