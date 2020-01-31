#pragma once
#include "headers.h"
typedef BOOL(__stdcall* wglSwapBuffers)(_In_ HDC hdc);
typedef uintptr_t PTR;
extern PTR SwapBuffersAddr;
extern wglSwapBuffers oSwapBuffers;

namespace PHook
{
	void Init();
	void Shutdown();
	void SetupOrtho();
	void Restore();
	BOOL __stdcall hkSwapBuffers(_In_ HDC hdc);
}