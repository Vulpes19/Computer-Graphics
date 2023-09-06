#pragma once

#include "DirectX.hpp"
#include <DirectXMath.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <vector>

struct Vertex
{
	FLOAT x;
	FLOAT y;
	FLOAT z;
	DirectX::XMFLOAT4 color;
};

class GameObject
{
	public:
		GameObject(std::vector<Vertex>);
		~GameObject(void);
		void	loadShaders(void);
		void	createVertices(void);
		void	createInputElements(ID3D10Blob*);
		void	render(void);
	protected:
		std::vector<Vertex> points;
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* devContext = nullptr;
		ID3D11VertexShader* vertexShader = nullptr;
		ID3D11PixelShader* pixelShader = nullptr;
		ID3D11InputLayout* layout = nullptr;
		ID3D11Buffer* vertexBuffer = nullptr;
};