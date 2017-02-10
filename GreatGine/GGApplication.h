#pragma once

#include <Windows.h>
#include <exception>
#include <string>


class GGApplication
{
public:
	GGApplication(HINSTANCE hInstance, const std::wstring& title);

public:
	void Run(int nCmdShow);

private:
	void MakeWindow(HINSTANCE hInstance, const std::wstring& title, int width, int height);
	void Update();
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND m_hwnd = NULL;
};