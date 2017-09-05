#include "GGMesh.h"
using Microsoft::WRL::ComPtr;
using namespace std;
using namespace DirectX;

GGMesh::GGMesh()
{}

GGMesh::GGMesh(GGDirectX& directX, vector<GGVertex>& vertices, vector<GGIndex>& indices)
{
	m_indexCount = indices.size();

	// Index buffer
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = indices.size() * sizeof(GGIndex);
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = indices.data();
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	auto hr = directX.device->CreateBuffer(&bufferDesc, &initData, m_indexBuffer.GetAddressOf());
	if (FAILED(hr))
		throw exception();

	// Vertex buffer
	bufferDesc.ByteWidth = vertices.size() * sizeof(GGVertex);
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	initData.pSysMem = vertices.data();

	hr = directX.device->CreateBuffer(&bufferDesc, &initData, m_vertexBuffer.GetAddressOf());
	if (FAILED(hr))
		throw exception();
}

void GGMesh::Set(const GGDirectX& directX) const
{
	UINT stride = sizeof(GGVertex);
	UINT offset = 0;
	directX.deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	directX.deviceContext->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, offset);
}

void GGMesh::Render(const GGDirectX& directX) const
{
	directX.deviceContext->DrawIndexed(m_indexCount, 0, 0);
}
