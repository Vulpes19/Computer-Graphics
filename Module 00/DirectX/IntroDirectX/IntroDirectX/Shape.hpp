#pragma once

#include "DirectX.hpp"
#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include "ErrorHandling.hpp"

struct Vertex
{
	FLOAT x;
	FLOAT y;
	FLOAT z;
	DirectX::XMFLOAT4 color;
};

class Shape
{
	public:
		Shape(void);
		~Shape(void);
		void	setDev(ID3D11Device *, ID3D11DeviceContext *);
		void	loadShaders(void);
		void	createVertices(void);
		void	createInputElements(ID3D10Blob *);
		void	render(void);
	private:
		ID3D11VertexShader*  vertexShader;
		ID3D11PixelShader*	 pixelShader;
		ID3D11Device*		 device;
		ID3D11DeviceContext* devContext;
		ID3D11InputLayout* layout;
		ID3D11Buffer* vertexBuffer;
};
