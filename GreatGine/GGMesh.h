#pragma once

#include <vector>
#include <DirectXMath.h>
#include "GGRenderer.h"

class GGMesh
{
public:
	struct GGVertex
	{
		DirectX::XMFLOAT3 position;
	};

	typedef unsigned int GGIndex;

public:
	GGMesh()
	{}

private:
	friend class GGRenderer;

	GGMesh(GGDirectX& directX, std::vector<GGVertex>& vertices, std::vector<GGIndex>& indices);

private:
	void Set(const GGDirectX& directX) const;
	void Render(const GGDirectX& directX) const;

private:
	UINT m_indexCount = 0;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
};