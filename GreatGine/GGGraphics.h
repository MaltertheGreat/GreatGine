#pragma once

#include "GGRenderer.h"

class GGGraphics
{
public:
	GGGraphics(HWND hWnd, int width, int height);

public:
	void Update();

private:
	void Render();

private:
	GGRenderer m_renderer;
	GGShader m_testShader;
	GGMesh m_testMesh;
};