#pragma once

#include <Windows.h>

#include "GGInput.h"
#include "GGGraphics.h"

class GGApplication
{
public:
	GGApplication(HINSTANCE hInstance, const std::wstring& title);

	void Run(int nCmdShow);

private:
	void Update();
	static HWND MakeWindow(HINSTANCE hInstance, const std::wstring& title, int width, int height);
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	int m_width;
	int m_height;
	HWND m_hwnd;
	GGInput m_input;
	GGGraphics m_graphics;
};
