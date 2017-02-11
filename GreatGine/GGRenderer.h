#pragma once

#include <DirectXMath.h>
#include <vector>
#include <array>
#include <d3d11.h>
#include <wrl.h>

struct GGShader
{
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
};

struct GGMesh
{
	struct GGVertex
	{
		DirectX::XMFLOAT3 position;
	};

	typedef unsigned int GGIndex;

	UINT indexCount = 0;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
};

class GGRenderer
{
public:
	GGRenderer(HWND hWnd, int width, int height);

public:
	GGShader MakeShader();
	GGMesh MakeMesh(std::vector<GGMesh::GGVertex>& vertices, std::vector<GGMesh::GGIndex>& indices);

	void SetShader(const GGShader& shader);
	void SetMesh(GGMesh& mesh);
	void RenderMesh(GGMesh& mesh);

	void StartFrame(const std::array<float, 4> color);
	void EndFrame();

private:
	static std::vector<char> ReadFile(const std::string& fileName);
	Microsoft::WRL::ComPtr<ID3D11Buffer> MakeVertexBuffer(std::vector<GGMesh::GGVertex>& vertices) const;
	Microsoft::WRL::ComPtr<ID3D11Buffer> MakeIndexBuffer(std::vector<GGMesh::GGIndex>& indices) const;

private:
	Microsoft::WRL::ComPtr<ID3D11Device> m_device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
};