// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once

#include <memory>

#include <any>
#include <cstddef>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include "interface/interface.hpp"
#include "workspace/windowSettings.hpp"
#include "console/console.hpp"
#include <imgui.h>
#include <imgui_internal.h>

enum class drawType : int 
{
	Line, Rectangle, RectangleFilled, Image, Text, Circle, CircleFilled
};

enum class drawTarget : int 
{
	Window, Checkbox, CheckboxActive, CheckboxInactive
};

struct systemFont {
	std::string name;
	std::string file;
};

struct layerStruct 
{
	// technical info
	std::string name;
	bool _hovered = false;
	bool _locked = false;
	bool _show = true;
	bool _shouldRebuild = false;
	int _round = 0;

	drawTarget target;
	drawType type;

	// base info
	ImVec2 pos, size;
	ImColor color;

	// rect + rect filled + line
	float thickness = 1.f;
	float rounding = 0.f;
	ImDrawCornerFlags roundFlags = ImDrawCornerFlags_None;
	
	// circle
	float radius;

	// text
	std::string textValue;
	std::string fontName;
	std::string fontFile;
	float fontSize = 13.f;
	int textAlignX = 1;
	int textAlignY = 1;
	ImVec2 textSize;
	ImFont* font = nullptr;

	// image
	IDirect3DTexture9* texture = nullptr;
	std::string imagePath;
	std::string imageName;

	void SwapSelection(ImVec2 start, ImVec2 end, int id) 
	{
		if (gContext.SelectedTab == 2 && gContext.CheckboxLayer == 0 && target != drawTarget::Checkbox)
			return;
		if (gContext.SelectedTab == 2 && gContext.CheckboxLayer == 1 && target != drawTarget::CheckboxActive)
			return;
		if (gContext.SelectedTab == 2 && gContext.CheckboxLayer == 2 && target != drawTarget::CheckboxInactive)
			return;

		if (!ImGui::IsMouseDragging(0) && !gContext.InResize && !_locked && !gContext.InColorPicker) 
		{
			if (ImGui::IsMouseHoveringRect(start, end, false) && ImGui::IsMouseDown(0))
			{
				gContext.SelectedLayer = id;
			}
		}
	}

	void Render(ImDrawList* draw, float scale, int id);
};

class layerSystem 
{
public:
	void RegisterItem(layerStruct data);
	void RegisterImage(std::string path);
	void Rebuild(LPDIRECT3DDEVICE9 device);

	std::vector<systemFont> systemFonts;
};

inline auto gLayerSystem = std::make_shared<layerSystem>();