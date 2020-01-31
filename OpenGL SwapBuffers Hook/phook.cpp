#include "phook.h"

#pragma comment(lib, "OpenGL32.lib")

void PHook::Init()
{
	SwapBuffersAddr = NULL;
	while (SwapBuffersAddr == NULL)
		SwapBuffersAddr = (PTR)(GetProcAddress(GetModuleHandle("opengl32.dll"), "wglSwapBuffers"));
	MH_Initialize();
	MH_CreateHook((LPVOID)SwapBuffersAddr, (LPVOID)hkSwapBuffers, (LPVOID*)& oSwapBuffers);
	MH_EnableHook((LPVOID)SwapBuffersAddr);
}

void PHook::Shutdown()
{
	MH_DisableHook((LPVOID)SwapBuffersAddr);
	MH_RemoveHook((LPVOID)SwapBuffersAddr);
	MH_Uninitialize();
}

void PHook::SetupOrtho()
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
}

void PHook::Restore()
{
	glEnable(GL_DEPTH_TEST);
}