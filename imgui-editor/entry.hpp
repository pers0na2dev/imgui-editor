#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <imgui.h>
#include <console/console.hpp>

#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "layerSystem/layerSystem.hpp"

#include <filesystem>

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

inline LPDIRECT3D9 g_pD3D = NULL;
inline LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;
inline D3DPRESENT_PARAMETERS g_d3dpp = {};

inline bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; 
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

inline void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

inline void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    ImGui_ImplDX9_CreateDeviceObjects();
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    HDROP hDrop;
    POINT pt;
    int cnt;
    char fileName[512];

    switch (msg)
    {
    case WM_CREATE:
        DragAcceptFiles(hWnd, TRUE);
        break;
    case WM_GETMINMAXINFO: {
        MINMAXINFO* minmax = (MINMAXINFO*)lParam;
        minmax->ptMinTrackSize.x = 1280;
        minmax->ptMinTrackSize.y = 800;
        return 0;
    }
    case WM_DROPFILES:
        hDrop = (HDROP)wParam;
        DragQueryPoint(hDrop, &pt);
        cnt = DragQueryFile(hDrop, 0xFFFFFFFF, 0, 0);

        for (int i = 0; i < cnt; i++)
        {
             DragQueryFileA(hDrop, i, fileName, 512);
             if (std::filesystem::path(fileName).extension() == ".png" ||
                 std::filesystem::path(fileName).extension() == ".jpg") 
             {
                 gLayerSystem->RegisterImage(fileName);
             }
        }
  
        DragFinish(hDrop);

        break;
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        exit(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

