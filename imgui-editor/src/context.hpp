#pragma once

#include "../dependencies/imgui/imgui.h"

struct Context 
{
	int SelectedEditor = 0;
	int SelectedLayer = -1;
	int SelectedTab = -1;
	int SelectedWidget = 0;
	int SelectedTarget = 0;

	bool CheckboxState = false;
	int CheckboxLayer = 0;

	bool isCloudAction = false;

	bool RenderSidebar = true;
	bool NeedUpdate;

	bool InResize = false;
	bool InColorPicker = false;
	ImColor* ColorPicker = nullptr;

	float WindowScale = 1.f;
	ImVec2 RenderPos = {};
	ImVec2 WindowSize = {};

	ImVec2 ScaleM(ImVec2 size) {
		return ImVec2(size.x * WindowScale, size.y * WindowScale);
	}
	ImVec2 ScaleD(ImVec2 size) {
		return ImVec2(size.x / WindowScale, size.y / WindowScale);
	}
	float ScaleM(float size) {
		return size * WindowScale;
	}
	float ScaleD(float size) {
		return size / WindowScale;
	}
	bool MouseInWorkspace() {
		return ImGui::IsMouseHoveringRect({ 345, 45 }, { ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y }, false);
	}
	bool MouseInWorkspaceSide() {
		return ImGui::IsMouseHoveringRect({ 345, 45 }, { ImGui::GetIO().DisplaySize.x - 260, ImGui::GetIO().DisplaySize.y }, false);
	}
};

inline Context gContext = Context{};