#pragma once

#include "DirectX.hpp"
#include <DirectXMath.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <vector>
#include <iostream>

struct Vertex
{
	Vertex(float x, float y, float z = 0.0f) : x(x), y(y), z(z) {};
	FLOAT x;
	FLOAT y;
	FLOAT z;
	//DirectX::XMFLOAT4 color;
};

class GameObject
{
	public:
		GameObject(std::vector<Vertex>, const char *, const char *);
		~GameObject(void);
		virtual void	loadShaders(void);
		virtual void	update(int &) {};
		virtual bool	deadObstacle(void) const { return (false); };
		void	createVertices(void);
		void	createInputElements(ID3D10Blob*);
		void	render(void);
		void	setDevice(ID3D11Device*, ID3D11DeviceContext*);
		std::vector<Vertex>	getPosition(void) const;
	protected:
		std::vector<Vertex> vertices;
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* devContext = nullptr;
		ID3D11VertexShader* vertexShader = nullptr;
		ID3D11PixelShader* pixelShader = nullptr;
		ID3D11InputLayout* layout = nullptr;
		ID3D11Buffer* vertexBuffer = nullptr;
		ID3D11Buffer* indexBuffer = nullptr;
		const char* vShaderPath = nullptr;
		const char* pShaderPath = nullptr;
};