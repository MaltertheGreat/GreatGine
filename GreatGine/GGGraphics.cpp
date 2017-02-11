#include "GGGraphics.h"
#include <exception>
#include <array>
using DirectX::XMFLOAT3;
using Microsoft::WRL::ComPtr;
using std::vector;
using std::array;

GGGraphics::GGGraphics(HWND hWnd, int width, int height)
	:
	m_renderer(hWnd, width, height)
{
	m_testShader = m_renderer.MakeShader();

	vector<GGMesh::GGVertex> vertices = {
		{ { 0.5f, 0.5f, 0.5f } },
		{ { 0.5f, -0.5f, 0.5f } },
		{ { -0.5f, -0.5f, 0.5f } }
	};
	vector<GGMesh::GGIndex> indices =
	{
		0, 1, 2
	};

	m_testMesh = m_renderer.MakeMesh(vertices, indices);
}

void GGGraphics::Update()
{
	Render();
}

void GGGraphics::Render()
{
	array<float, 4> color = { 0.2f, 0.2f, 0.8f, 1.0f };
	m_renderer.StartFrame(color);

	m_renderer.SetShader(m_testShader);
	m_renderer.SetMesh(m_testMesh);
	m_renderer.RenderMesh(m_testMesh);

	m_renderer.EndFrame();
}