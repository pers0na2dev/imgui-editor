#include <windows.h>

#include "entry.hpp"

#include "src/interface/elements.hpp"
#include "src/interface/interface.hpp"
#include "src/filesystem/filesystem.hpp"
#include "src/utils/workspaceKeybinds.hpp"
#include "src/utils/utils.hpp"

#include "dependencies/console/console.hpp"
#include "dependencies/notifies/notifies.h"

#include "defines.h"
#include "src/installer/installerSystem.hpp"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
#if DEBUG_MODE
	conManager->init();
#endif

	gInstallerSystem->GenerateDirectories();
	gFileSystem->FetchProjects();

	utils::EnumerateSubKeys(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts");

	std::thread([]() {
		for (;;) 
		{
			if (gFileSystem->selectedProject != "" &&
				gContext.SelectedTab != -1) 
			{
				gFileSystem->SaveProject();
			}
			std::this_thread::sleep_for(std::chrono::seconds(60));
		}
	}).detach();

	WNDCLASSEX wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "imgui.tech", NULL };
	::RegisterClassEx(&wc);

	HWND hwnd = ::CreateWindow(wc.lpszClassName, "imgui.tech", WS_OVERLAPPEDWINDOW, 100, 100, 1400, 900, NULL, NULL, wc.hInstance, NULL);

	if (!CreateDeviceD3D(hwnd))
	{
		CleanupDeviceD3D();
		::UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
	}

	::ShowWindow(hwnd, 10);
	::UpdateWindow(hwnd);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	gInstallerSystem->SetStyles();

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX9_Init(g_pd3dDevice);

	while (true)
	{
		MSG msg;
		while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();
		{
			gInterfaceSystem->Render();

			workspaceKeybinds->Layer();
			workspaceKeybinds->Tools();
			workspaceKeybinds->History();
			workspaceKeybinds->Save();

			if (gContext.isCloudAction) {
				elements::Spinner("Action", 8, 2, ImColor(190, 190, 190), ImGui::GetIO().DisplaySize - ImVec2(26, 26));
			}

			if (gContext.NeedUpdate) {
				ImGui::GetForegroundDrawList()->AddRectFilled({ 0, ImGui::GetIO().DisplaySize.y - 25 }, ImGui::GetIO().DisplaySize, ImColor(45, 121, 255));
				ImGui::GetForegroundDrawList()->AddText(
					{ ImGui::GetIO().DisplaySize.x / 2 - ImGui::CalcTextSize("The new version is available").x / 2,ImGui::GetIO().DisplaySize.y - 19},
					ImColor(255, 255, 255), 
					"The new version is available"
				);
			}

			notifies::handle(ImGui::GetForegroundDrawList());
		}
		ImGui::EndFrame();

		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(25, 25, 25, 255), 1.0f, 0);

		if (g_pd3dDevice->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			g_pd3dDevice->EndScene();
		}

		gLayerSystem->Rebuild(g_pd3dDevice);

		if (
			g_pd3dDevice->Present(NULL, NULL, NULL, NULL) == D3DERR_DEVICELOST &&
			g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET
			)
		ResetDevice();
	}

	return 0;
}