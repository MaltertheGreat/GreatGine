#pragma once

#include <vector>
#include <DirectXMath.h>
#include "GGRenderer.h"

class GGMesh
{
public:
	friend class GGRenderer;

	struct GGVertex
	{
		DirectX::XMFLOAT3 position;
	};

	typedef unsigned int GGIndex;

	GGMesh();

private:
	GGMesh(GGDirectX& directX, std::vector<GGVertex>& vertices, std::vector<GGIndex>& indices);

	void Set(const GGDirectX& directX) const;
	void Render(const GGDirectX& directX) const;

	UINT m_indexCount = 0;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
};
