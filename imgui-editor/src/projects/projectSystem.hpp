#pragma once

#include <memory>
#include <vector>

#include <nlohmann/json.hpp>
#include <imgui.h>
#include <imgui_internal.h>
#include "layerSystem/layerSystem.hpp"

struct WindowStruct
{
	ImVec2 WindowSize;
	float Alpha = 1.f;
	float DisabledAlpha;
	float WindowRounding;
	float WindowBorderSize;
	ImVec2 WindowMinSize;
	ImVec2 WindowPadding;
	ImVec2 WindowTitleAlign = {0.5F, 0.5f};
	float ChildRounding;
	float ChildBorderSize;
	float PopupRounding;
	float PopupBorderSize;
	float FrameRounding;
	float FrameBorderSize;
	float IndentSpacing;
	ImVec2 ItemSpacing;
	ImVec2 ItemInnerSpacing;
	ImVec2 FramePadding = { 3, 3 };
};

struct CheckboxStruct
{
	bool _shouldRebuild = true;

	ImVec2 TotalSize = {100, 20};
	ImVec2 FrameSize = {20, 20};
	ImVec2 FramePos  = {0, 0};

	float FontSize = 13.f;
	ImFont* Font = nullptr;
	ImVec2 LabelPos = { 0, 0 };
	std::string TextValue = "Checkbox";
	std::string FontName = "Arial (True Type)";
	std::string FontFile = "arial.ttf";
};

struct currentProjectData {
	WindowStruct window;
	CheckboxStruct checkbox;
	std::vector<layerStruct> layers;
};

class projectSystem
{
public:
	template<class T>
	void JSON(nlohmann::json& j, std::string name, T& value, bool save);
	void JSON(nlohmann::json& j, std::string name, ImVec2& value, bool save);
	void JSON(nlohmann::json& j, std::string name, ImColor& value, bool save);
	void JSON(nlohmann::json& j, std::string name, std::string& value, bool save);
	void JSONLayer(nlohmann::json& json, std::vector<layerStruct>& layer, bool save);

	void Action(nlohmann::json& input, bool save);
	void ActionTransform(nlohmann::json& input, currentProjectData& data);

	currentProjectData data;
};

inline auto gProjectSystem = std::make_shared<projectSystem>();

