#pragma once

#include <functional>

#include <imgui.h>
#include <imgui_internal.h>

#include "prototypeSystem/prototypeSystem.hpp"
#include "layerSystem/layerSystem.hpp"
#include "filesystem/filesystem.hpp"
#include "history/history.hpp"

#include "assets/hashes.h"
#include "transformDrawlist.hpp"

namespace elements
{
	inline ImAnimations::Animator<const char*, float> anim;
	inline ImAnimations::Animator<const char*, float> anim2;
	inline ImAnimations::Animator<const char*, float> animHovered;

	__forceinline bool Selectable(const char* label, const char* bind = "") {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize({ 200, 24 }, 49, 35);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		auto animHoverSize = animHovered.ValueInSine(label, hovered, 0.f, 1.f, 0.1f);
		auto colorHover = ImAnimations::LerpColor(ImColor(0, 166, 255, 0), ImColor(0, 166, 255), animHoverSize);

		window->DrawList->AddRectFilled(bb.Min, bb.Max, colorHover);
		window->DrawList->AddText(bb.Min + ImVec2(10, 5), ImColor(255, 255, 255), label);
		window->DrawList->AddText(bb.Max - ImVec2(10 + ImGui::CalcTextSize(bind).x, 19), ImColor(255, 255, 255), bind);

		return pressed;
	}

	__forceinline bool Link(const char* label, const char* icon) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize({ 290, 32 }, 49, 35);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		auto animHoverSize = animHovered.ValueInSine(label, hovered, 0.f, 1.f, 0.1f);
		auto colorHover = ImAnimations::LerpColor(ImColor(56, 56, 56, 78), ImColor(56, 56, 56), animHoverSize);

		window->DrawList->AddRectFilled(bb.Min, bb.Max, colorHover);

		window->DrawList->AddText(bb.Min + ImVec2(10, 9), ImColor(255, 255, 255), icon);
		window->DrawList->AddText(bb.Min + ImVec2(35, 9), ImColor(255, 255, 255), label);

		return pressed;
	}

	__forceinline bool Expot(const char* label) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize({ 36, 36 }, 49, 35);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		auto animHoverSize = animHovered.ValueInSine(label, hovered, 0.f, 1.f, 0.1f);
		auto colorHover = ImAnimations::LerpColor(ImColor(45, 121, 255, 0), ImColor(45, 121, 255), animHoverSize);

		window->DrawList->AddRectFilled(bb.Min, bb.Max, colorHover, 8);
		window->DrawList->AddText(bb.Min + ImVec2(36, 36) / 2 - ImGui::CalcTextSize((const char*)ICON_FA_DOWNLOAD) / 2, ImColor(255, 255, 255), (const char*)ICON_FA_DOWNLOAD);

		return pressed;
	}

	__forceinline bool Save(const char* label) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize({ 36, 36 }, 49, 35);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		auto animHoverSize = animHovered.ValueInSine(label, hovered, 0.f, 1.f, 0.1f);
		auto colorHover = ImAnimations::LerpColor(ImColor(45, 121, 255, 0), ImColor(45, 121, 255), animHoverSize);

		window->DrawList->AddRectFilled(bb.Min, bb.Max, colorHover, 8);
		window->DrawList->AddText(bb.Min + ImVec2(36, 36) / 2 - ImGui::CalcTextSize((const char*)ICON_FA_DOWNLOAD) / 2, ImColor(255, 255, 255), (const char*)ICON_FA_SAVE);

		return pressed;
	}

	__forceinline void Layer(const char* label, layerStruct& layer, int index) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize({ 290, 30 }, 49, 35);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		auto animShow = anim.ValueInSine(label, layer._show, 0.f, 1.f, 0.1f);
		auto animLock = anim2.ValueInSine(label, layer._locked, 0.f, 1.f, 0.1f);
		auto animHoverSize = animHovered.ValueInSine(label, hovered, 0.f, 1.f, 0.1f);
		auto colorHover = ImAnimations::LerpColor(ImColor(24, 24, 24, 0), ImColor(24, 24, 24, 50), animHoverSize);
		auto colorShow = ImAnimations::LerpColor(ImColor(190, 190, 190, 190), ImColor(255, 255, 255), animShow);
		auto colorLock = ImAnimations::LerpColor(ImColor(190, 190, 190, 190), ImColor(255, 255, 255), animLock);

		auto getType = [](layerStruct layer) {
			if (layer.type == drawType::Line) return "Line";
			if (layer.type == drawType::Rectangle) return "Rectangle";
			if (layer.type == drawType::RectangleFilled) return "Rectangle Filled";
			if (layer.type == drawType::Image) return layer.imageName.c_str();
			if (layer.type == drawType::Text) return "Text";
			if (layer.type == drawType::Circle) return "Circle";
			if (layer.type == drawType::CircleFilled) return "Circle Filled";
		};

		window->DrawList->AddRectFilled(bb.Min, bb.Max, ImColor(47, 47, 47));
		window->DrawList->AddRectFilled(bb.Min, bb.Min + ImVec2(30, 30), ImColor(28, 28, 28));
		window->DrawList->AddRectFilled(bb.Min, bb.Max, colorHover);
		window->DrawList->AddRect(bb.Min, bb.Max, ImColor(50, 50, 51));

		layer._hovered = hovered;

		if (layer._hovered)
			window->DrawList->AddRect(bb.Min, bb.Max, ImColor(0, 166, 255));

		window->DrawList->AddText(bb.Min + ImVec2(265, 8), colorShow, (const char*)ICON_FA_EYE);
		if (pressed && ImGui::IsMouseHoveringRect(bb.Min + ImVec2(260, 0), bb.Max))
			layer._show = !layer._show;

		window->DrawList->AddText(bb.Min + ImVec2(235, 8), colorLock, (const char*)ICON_FA_LOCK);
		if (pressed && ImGui::IsMouseHoveringRect(bb.Min + ImVec2(235, 0), bb.Min + ImVec2(265, 30)))
			layer._locked = !layer._locked;

		window->DrawList->AddText(bb.Min + ImVec2(40, 7), ImColor(255, 255, 255), getType(layer));

		if (layer.type == drawType::Line) {
			window->DrawList->AddLine(bb.Min + ImVec2(10, 15), bb.Min + ImVec2(20, 15), layer.color);
		}
		if (layer.type == drawType::Rectangle) {
			window->DrawList->AddRect(bb.Min + ImVec2(7, 7), bb.Min + ImVec2(23, 23), layer.color, 4);
		}
		if (layer.type == drawType::RectangleFilled) {
			window->DrawList->AddRectFilled(bb.Min + ImVec2(7, 7), bb.Min + ImVec2(23, 23), layer.color, 4);
		}
		if (layer.type == drawType::Image) {
			window->DrawList->AddText(bb.Min + ImVec2(10, 8), ImColor(255, 255, 255), (const char*)ICON_FA_FILE);
		}
		if (layer.type == drawType::Text) {
			window->DrawList->AddText(bb.Min + ImVec2(10, 8), layer.color, (const char*)ICON_FA_TEXT);
		}
		if (layer.type == drawType::Circle) {
			window->DrawList->AddCircle(bb.Min + ImVec2(15, 15), 6, layer.color, 32);
		}
		if (layer.type == drawType::CircleFilled) {
			window->DrawList->AddCircleFilled(bb.Min + ImVec2(15, 15), 6, layer.color, 32);
		}

		if (ImGui::BeginPopup(std::string(label + std::string("popup")).c_str()))
		{
			ImGui::Dummy({ 0, 5 });

			if (Selectable(layer._show ? "Hide" : "Show")) layer._show = !layer._show;
			if (Selectable(layer._locked ? "Unlock" : "Lock")) layer._locked = !layer._locked;

			ImGui::Dummy({ 0, 5 });
			ImGui::Separator();
			ImGui::Dummy({ 0, 5 });

			if (Selectable("Delete", "Hover + Del")) {
				gContext.SelectedLayer = -1;
				gProjectSystem->data.layers.erase(gProjectSystem->data.layers.begin() + index);
			}

			ImGui::Dummy({ 0, 5 });
			ImGui::EndPopup();
		}

		if (hovered && ImGui::IsKeyPressed(ImGuiKey_Delete, false)) {
			gContext.SelectedLayer = -1;
			gProjectSystem->data.layers.erase(gProjectSystem->data.layers.begin() + index);
		}

		if (hovered && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
			ImGui::OpenPopup(std::string(label + std::string("popup")).c_str());
	}

	__forceinline void Tool(const char* label, std::function<void(ImDrawList*, ImVec2, ImVec2)> icon, int& state, int index) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize({ 36, 36 }, 49, 35);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		if (pressed)
			state = index;

		auto animSize = anim.ValueInSine(label, state == index, 0.f, 1.f, 0.1f);
		auto animHoverSize = animHovered.ValueInSine(label, hovered, 0.f, 1.f, 0.1f);

		auto color = ImAnimations::LerpColor(ImColor(45, 121, 255, 0), ImColor(45, 121, 255), animSize);
		auto colorHover = ImAnimations::LerpColor(ImColor(65, 65, 65, 0), ImColor(65, 65, 65), animHoverSize);

		window->DrawList->AddRectFilled(bb.Min, bb.Max, colorHover, 9);
		window->DrawList->AddRectFilled(bb.Min, bb.Max, color, 9);

		icon(window->DrawList, bb.Min, bb.Max);
	}

	__forceinline void Tab(const char* label, const char* icon, int& state, int index) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize({ 38, 38 }, 42, 42);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		if (pressed)
			state = index;

		auto animSize = anim.ValueInSine(label, state == index, 0.f, 1.f, 0.1f);
		auto animHoverSize = animHovered.ValueInSine(label, hovered, 0.f, 1.f, 0.1f);

		auto color = ImAnimations::LerpColor(ImColor(45, 121, 255, 0), ImColor(45, 121, 255), animSize);
		auto colorHover = ImAnimations::LerpColor(ImColor(24, 24, 24, 0), ImColor(24, 24, 24, 25), animHoverSize);

		window->DrawList->AddRectFilled(bb.Min, bb.Max, color, 9);
		window->DrawList->AddRectFilled(bb.Min, bb.Max, colorHover, 9);

		window->DrawList->AddText(bb.Min + ImVec2(38, 38) / 2 - ImGui::CalcTextSize(icon) / 2, ImColor(255, 255, 255), icon);
	}

	__forceinline bool ItemGrouped(const char* label, const char* icon, int& state, int index) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize({ 25, 25 }, 49, 35);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		if (pressed) {
			state = index;
			gHistorySystem->RegisterHistoryItem();
		}

		auto animSize = anim.ValueInSine(label, state == index, 0.f, 1.f, 0.1f);

		auto color = ImAnimations::LerpColor(ImColor(47, 47, 47, 0), ImColor(47, 47, 47), animSize);
		auto color1 = ImAnimations::LerpColor(ImColor(50, 50, 51, 0), ImColor(50, 50, 51), animSize);
		auto color2 = ImAnimations::LerpColor(ImColor(210, 210, 210), ImColor(45, 121, 255), animSize);

		window->DrawList->AddRectFilled(bb.Min, bb.Max, color, 4);
		window->DrawList->AddRect(bb.Min, bb.Max, color1, 4);
		window->DrawList->AddText(bb.Min + ImVec2(25, 25) / 2 - ImGui::CalcTextSize(icon) / 2, color2, icon);

		return pressed;
	}

	__forceinline bool InvisibleInputFloat(const char* label, const char* inputName, float& state, const char* format) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize({ ImGui::CalcTextSize(label).x + 60 , 36 }, 49, 35);

		const ImRect bb(pos, pos + size);

		window->DrawList->AddText(bb.Min + ImVec2(5, 18 - ImGui::CalcTextSize(label).y / 2), ImColor(190, 190, 190), label);
		ImGui::GetForegroundDrawList()->AddLine(bb.Min + ImVec2(size.x, -6), bb.Min + ImVec2(size.x, 41), ImColor(46, 46, 46));

		ImGui::PushItemWidth(55);
		ImGui::SetCursorPos(bb.Min + ImVec2(-10, 8));
		bool ret = ImGui::InputFloat(inputName, &state, 0, 0, format, 0); //ImGuiInputTextFlags_Invisible

		if (ret) gHistorySystem->RegisterHistoryItem();
		return ret;
	}

	__forceinline bool InvisibleInputInt(const char* label, const char* inputName, int& state) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize({ ImGui::CalcTextSize(label).x + 60 , 36 }, 49, 35);

		const ImRect bb(pos, pos + size);

		window->DrawList->AddText(bb.Min + ImVec2(5, 18 - ImGui::CalcTextSize(label).y / 2), ImColor(190, 190, 190), label);
		ImGui::GetForegroundDrawList()->AddLine(bb.Min + ImVec2(size.x, -6), bb.Min + ImVec2(size.x, 41), ImColor(46, 46, 46));

		ImGui::PushItemWidth(55);
		ImGui::SetCursorPos(bb.Min + ImVec2(-10, 8));
		bool ret = ImGui::InputInt(inputName, &state, 0, 0, 0); //ImGuiInputTextFlags_Invisible

		if (ret) gHistorySystem->RegisterHistoryItem();
		return ret;
	}

	__forceinline void Child(const char* label, ImVec2 size, std::function<void()> callback)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 6, 8 });
		ImGui::BeginChild(label, size, false, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
		{
			auto draw = ImGui::GetWindowDrawList();
			auto pos = ImGui::GetWindowPos();

			draw->AddRectFilled(pos + ImVec2(1, 0), pos + ImVec2(size.x, 30), ImColor(25, 25, 25, 200));
			draw->AddText(pos + ImVec2{ 10, 8 }, ImColor(230, 230, 230), label);

			ImGui::SetCursorPos({ 10, 38 });
			ImGui::BeginGroup();
			{
				callback();
			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	__forceinline void DashedRect(ImDrawList* draw, ImVec2 start, ImVec2 end, ImColor col, float thikness) {
		AddLineDashed(draw, start, ImVec2(end.x, start.y), col, thikness);
		AddLineDashed(draw, start, ImVec2(start.x, end.y), col, thikness);
		AddLineDashed(draw, ImVec2(end.x, start.y), ImVec2(end.x, end.y), col, thikness);
		AddLineDashed(draw, ImVec2(start.x, end.y), ImVec2(end.x, end.y), col, thikness);
	}

	inline bool ColorPickerInternal(float col[4])
	{
		static const float HUE_PICKER_WIDTH = 20.0f;
		static const float CROSSHAIR_SIZE = 7.0f;
		static const ImVec2 SV_PICKER_SIZE = ImVec2(250, 155);

		ImColor color(col[0], col[1], col[2]);
		bool value_changed = false;

		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		ImVec2 picker_pos = ImGui::GetCursorScreenPos();

		ImColor colors[] = { ImColor(255, 0, 0),
			ImColor(255, 255, 0),
			ImColor(0, 255, 0),
			ImColor(0, 255, 255),
			ImColor(0, 0, 255),
			ImColor(255, 0, 255),
			ImColor(255, 0, 0) };

		for (int i = 0; i < 6; ++i)
		{
			draw_list->AddRectFilledMultiColor(
				ImVec2(picker_pos.x + i * (SV_PICKER_SIZE.x / 6), picker_pos.y + 200 - 45),
				ImVec2(picker_pos.x + (i + 1) * (SV_PICKER_SIZE.x / 6),
					picker_pos.y + 215 - 45),
				colors[i],
				colors[i + 1],
				colors[i + 1],
				colors[i]);
		}

		float hue, saturation, value;
		ImGui::ColorConvertRGBtoHSV(
			color.Value.x, color.Value.y, color.Value.z, hue, saturation, value);

		{
			const int step = 5;
			ImVec2 pos = ImVec2(0, 0);

			ImVec4 c00(1, 1, 1, 1);
			ImVec4 c10(1, 1, 1, 1);
			ImVec4 c01(1, 1, 1, 1);
			ImVec4 c11(1, 1, 1, 1);
			for (int y = 0; y < step; y++) {
				for (int x = 0; x < step; x++) {
					float s0 = (float)x / (float)step;
					float s1 = (float)(x + 1) / (float)step;
					float v0 = 1.0 - (float)(y) / (float)step;
					float v1 = 1.0 - (float)(y + 1) / (float)step;

					ImGui::ColorConvertHSVtoRGB(hue, s0, v0, c00.x, c00.y, c00.z);
					ImGui::ColorConvertHSVtoRGB(hue, s1, v0, c10.x, c10.y, c10.z);
					ImGui::ColorConvertHSVtoRGB(hue, s0, v1, c01.x, c01.y, c01.z);
					ImGui::ColorConvertHSVtoRGB(hue, s1, v1, c11.x, c11.y, c11.z);

					draw_list->AddRectFilledMultiColor(
						ImVec2(picker_pos.x + pos.x, picker_pos.y + pos.y),
						ImVec2(picker_pos.x + pos.x + SV_PICKER_SIZE.x / step, picker_pos.y + pos.y + SV_PICKER_SIZE.y / step),
						ImGui::ColorConvertFloat4ToU32(c00),
						ImGui::ColorConvertFloat4ToU32(c10),
						ImGui::ColorConvertFloat4ToU32(c11),
						ImGui::ColorConvertFloat4ToU32(c01));

					pos.x += SV_PICKER_SIZE.x / step;
				}
				pos.x = 0;
				pos.y += SV_PICKER_SIZE.y / step;
			}
		}

		float x = saturation * SV_PICKER_SIZE.x;
		float y = (1 - value) * SV_PICKER_SIZE.y;
		ImVec2 p(picker_pos.x + x, picker_pos.y + y);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(p.x - CROSSHAIR_SIZE, p.y), ImVec2(p.x - 2, p.y), ImColor(255, 255, 255));
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(p.x + CROSSHAIR_SIZE, p.y), ImVec2(p.x + 2, p.y), ImColor(255, 255, 255));
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(p.x, p.y + CROSSHAIR_SIZE), ImVec2(p.x, p.y + 2), ImColor(255, 255, 255));
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(p.x, p.y - CROSSHAIR_SIZE), ImVec2(p.x, p.y - 2), ImColor(255, 255, 255));

		ImGui::InvisibleButton("saturation_value_selector", SV_PICKER_SIZE);

		if (ImGui::IsItemActive() && ImGui::GetIO().MouseDown[0])
		{
			ImVec2 mouse_pos_in_canvas = ImVec2(
				ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

			/**/ if (mouse_pos_in_canvas.x < 0) mouse_pos_in_canvas.x = 0;
			else if (mouse_pos_in_canvas.x >= SV_PICKER_SIZE.x - 1) mouse_pos_in_canvas.x = SV_PICKER_SIZE.x - 1;

			/**/ if (mouse_pos_in_canvas.y < 0) mouse_pos_in_canvas.y = 0;
			else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1) mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

			value = 1 - (mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1));
			saturation = mouse_pos_in_canvas.x / (SV_PICKER_SIZE.x - 1);
			value_changed = true;
		}

		ImGui::SetCursorScreenPos(ImVec2(picker_pos.x, picker_pos.y + 200 - 45));
		ImGui::InvisibleButton("hue_selector", ImVec2(250, 15));

		draw_list->AddCircleFilled(
			ImVec2(picker_pos.x + 7 + (hue * (SV_PICKER_SIZE.x - 14)), picker_pos.y + 207 - 45), 8, ImColor(255, 255, 255), 32);

		if ((ImGui::IsItemHovered() || ImGui::IsItemActive()) && ImGui::GetIO().MouseDown[0])
		{
			ImVec2 mouse_pos_in_canvas = ImVec2(
				ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

			/**/ if (mouse_pos_in_canvas.x < 0) mouse_pos_in_canvas.x = 0;
			else if (mouse_pos_in_canvas.x >= SV_PICKER_SIZE.x - 2) mouse_pos_in_canvas.x = SV_PICKER_SIZE.x - 2;

			hue = mouse_pos_in_canvas.x / (SV_PICKER_SIZE.x - 1);
			value_changed = true;
		}

		color = ImColor::HSV(hue > 0 ? hue : 1e-6, saturation > 0 ? saturation : 1e-6, value > 0 ? value : 1e-6);
		col[0] = color.Value.x;
		col[1] = color.Value.y;
		col[2] = color.Value.z;
		return value_changed;
	}

	__forceinline bool ColorBtn(const char* idd, ImColor data) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(idd);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize({ 25, 25 }, 42, 42);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		window->DrawList->AddRectFilled(bb.Min, bb.Max, ImColor(47, 47, 47), 4);
		ImGui::RenderColorRectWithAlphaCheckerboard(window->DrawList, bb.Min + ImVec2(1, 1), bb.Min + ImVec2(24, 24), data, 5, ImVec2(0, 0), 4);
		window->DrawList->AddRectFilled(bb.Min + ImVec2(1, 1), bb.Min + ImVec2(12, 24), ImColor(data.Value.x, data.Value.y, data.Value.z), 4, ImDrawCornerFlags_Left);

		return pressed;
	}

	__forceinline void Colorpicker(const char* label, ImColor& color, float width = 120) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		ImGuiContext& g = *GImGui;

		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		const ImVec2 pos = window->DC.CursorPos;
		const ImVec2 size = ImGui::CalcItemSize({ ImGui::GetWindowSize().x - 20, 30 }, ImGui::GetWindowSize().x - 20, 30);
		ImRect bb(pos, pos + size);

		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, 0);


		window->DrawList->AddRectFilled(bb.Min, bb.Max, ImColor(47, 47, 47), 4);
		ImGui::RenderColorRectWithAlphaCheckerboard(window->DrawList, bb.Min + ImVec2(1, 1), bb.Min + ImVec2(29, 29), color, 5, ImVec2(0, 0), 4);
		window->DrawList->AddRectFilled(bb.Min + ImVec2(1, 1), bb.Min + ImVec2(29, 29), color, 4, ImDrawCornerFlags_All);
		window->DrawList->AddRect(bb.Min, bb.Max, ImColor(50, 50, 51), 4);
		window->DrawList->AddText(bb.Min + ImVec2(36, 8), ImColor(200, 200, 200, 255), label);

		std::string popuplabel = label + std::string("popup");
		std::string popuplabelchild = label + std::string("popup2");
		std::string popuplabelchild3 = label + std::string("popup3");

		if (pressed && !ImGui::IsMouseHoveringRect(bb.Min + ImVec2(ImGui::GetWindowSize().x - 45, 8), bb.Min + ImVec2(ImGui::GetWindowSize().x - 15, 30), false)) {
			ImGui::OpenPopup(popuplabel.c_str());
		}

		if (ImGui::BeginPopup(popuplabel.c_str())) {
			ImGui::SetCursorPos({ 0, 0 });
			ImGui::BeginChild(popuplabelchild.c_str(), { 250, 315 });
			{
				ColorPickerInternal(&color.Value.x);

				int r = std::clamp(int(color.Value.x * 255), 0, 255);
				int g = std::clamp(int(color.Value.y * 255), 0, 255);
				int b = std::clamp(int(color.Value.z * 255), 0, 255);
				int a = std::clamp(int(color.Value.w * 255), 0, 255);

				ImGui::PushItemWidth(79);

				ImGui::SetCursorPos({ 10, 185 });
				if (ImGui::InputInt("R", &r, 0, 0))
					color.Value.x = r / 255.f;
				ImGui::SetCursorPos({ 91, 185 });
				if (ImGui::InputInt("B", &b, 0, 0))
					color.Value.z = b / 255.f;
				ImGui::SetCursorPos({ 188 - 17, 185 });
				if (ImGui::InputInt("G", &g, 0, 0))
					color.Value.y = g / 255.f;

				ImGui::SetCursorPos({ 10, 230 });
				if (ImGui::SliderInt("Alpha", &a, 0, 255))
					color.Value.w = a / 255.f;

				char buf[64];
				int i[4] = { r, g, b, a };
				ImFormatString(buf, IM_ARRAYSIZE(buf), "#%02X%02X%02X%02X", ImClamp(i[0], 0, 255), ImClamp(i[1], 0, 255), ImClamp(i[2], 0, 255), ImClamp(i[3], 0, 255));

				ImGui::PushItemWidth(240);
				ImGui::SetCursorPos({ 10, 270 });
				if (ImGui::InputText("HEX", buf, IM_ARRAYSIZE(buf), ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase))
				{
					char* p = buf;
					while (*p == '#' || ImCharIsBlankA(*p))
						p++;
					i[0] = i[1] = i[2] = 0;
					sscanf(p, "%02X%02X%02X%02X", (unsigned int*)&i[0], (unsigned int*)&i[1], (unsigned int*)&i[2], (unsigned int*)&i[3]); // Treat at unsigned (%X is unsigned)

					color.Value.x = i[0] / 255.f;
					color.Value.y = i[1] / 255.f;
					color.Value.z = i[2] / 255.f;
					color.Value.w = i[3] / 255.f;

					gHistorySystem->RegisterHistoryItem();
				}
			}
			ImGui::EndChild();

			ImGui::SetCursorPos({ 250, 0 });
			ImGui::BeginChild(popuplabelchild3.c_str(), { 45, 315 });
			{
				ImGui::GetWindowDrawList()->AddLine(ImGui::GetWindowPos(), ImGui::GetWindowPos() + ImVec2(0, 315), ImColor(66, 66, 75));

				ImGui::SetCursorPos({ 10, 10 });
				ImGui::BeginGroup();
				{
					for (auto i = 0; i < gProjectSystem->data.layers.size(); i++) {
						if (gProjectSystem->data.layers[i].color == color)
							continue;

						if (ColorBtn(std::to_string(i).c_str(), gProjectSystem->data.layers[i].color))
							color = gProjectSystem->data.layers[i].color;
					}

					ImGui::NewLine();
				}
				ImGui::EndGroup();
			}
			ImGui::EndChild();

			ImGui::EndPopup();
		}
	}

	__forceinline bool Widget(const char* label, const char* desc, const char* icon, ImVec2 sizeBtn) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize(sizeBtn, 42, 42);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		auto animHoverSize = animHovered.ValueInSine(label, hovered || pressed, 0.f, 1.f, 0.05f);
		auto colorHover = ImAnimations::LerpColor(ImColor(56, 56, 56, 0), ImColor(56, 56, 56), animHoverSize);

		window->DrawList->AddRect(bb.Min, bb.Max, ImColor(56, 56, 56), 7);
		window->DrawList->AddRectFilled(bb.Min, bb.Max, colorHover, 7);

		window->DrawList->AddText(bb.Min + ImVec2(48, sizeBtn.y) / 2 - ImGui::CalcTextSize(icon) / 2, ImColor(255, 255, 255), icon);
		window->DrawList->AddText(bb.Min + ImVec2(50, 9), ImColor(255, 255, 255), label);
		window->DrawList->AddText(bb.Min + ImVec2(50, 25), ImColor(190, 190, 190), desc);

		return pressed;
	}

	inline ImAnimations::Animator<std::string, float> animHovered2;

	__forceinline bool Spinner(const char* label, float radius, int thickness, const ImU32& color, ImVec2 pos) {
		auto& g = *GImGui;
		const auto& style = g.Style;
		ImVec2 size{ radius * 2, radius * 2 };
		const ImRect bb{ pos, pos + size };

		auto time = static_cast<float>(g.Time) * 1.8f;
		ImGui::GetForegroundDrawList()->PathClear();

		int start = static_cast<int>(abs(ImSin(time) * (32 - 5)));

		const float a_min = IM_PI * 2.0f * ((float)start) / (float)32;
		const float a_max = IM_PI * 2.0f * ((float)32 - 3) / (float)32;
		const auto&& centre = ImVec2(pos.x + radius, pos.y + radius);

		for (auto i = 0; i < 32; i++)
		{
			const float a = a_min + ((float)i / (float)32) * (a_max - a_min);
			ImGui::GetForegroundDrawList()->PathLineTo(
				{ centre.x + ImCos(a + time * 8) * radius,
				  centre.y + ImSin(a + time * 8) * radius });
		}

		ImGui::GetForegroundDrawList()->PathStroke(ImGui::GetColorU32(color), false, thickness);

		return true;
	}

	__forceinline bool Project(projectData data) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(data.filename.c_str());

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize({ (ImGui::GetWindowSize().x - 30) / 3, ImGui::GetWindowSize().y / 3 + 30 }, 42, 42);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		auto animHoverSize = animHovered2.ValueInSine(data.filename, hovered || pressed, 0.f, 1.f, 0.05f);
		auto colorHover = ImAnimations::LerpColor(ImColor(38, 38, 38, 125), ImColor(56, 56, 56), animHoverSize);

		window->DrawList->AddRectFilled(bb.Min, bb.Max - ImVec2(0, 30), colorHover, 7, ImDrawFlags_RoundCornersTop);
		window->DrawList->AddRectFilled(bb.Max - ImVec2((ImGui::GetWindowSize().x - 30) / 3, 30), bb.Max, ImColor(11, 11, 11), 7, ImDrawFlags_RoundCornersBottom);
		window->DrawList->AddRect(bb.Min, bb.Max, ImColor(68, 68, 68), 6);

		window->DrawList->PushClipRect(bb.Min, bb.Max - ImVec2(0, 30), true);
		transformDrawlist::render(window->DrawList, bb.Min + (bb.Max - ImVec2(0, 30) - bb.Min) / 2, transformDrawlist::parse(data), { (ImGui::GetWindowSize().x - 30) / 3 - 50, ImGui::GetWindowSize().y / 3 - 50});
		window->DrawList->PopClipRect();

		window->DrawList->AddText(bb.Max - ImVec2((ImGui::GetWindowSize().x - 30) / 3 - 10, 22), ImColor(255, 255, 255), data.name.c_str());

		return pressed;
	}

	__forceinline bool InputFloat(const char* label, float* val, float step, float step_fast, const char* format) {
		bool ret = ImGui::InputFloat(label, val, step, step_fast, format);

		if (ret) gHistorySystem->RegisterHistoryItem();

		return ret;
	}

	__forceinline bool SliderFloat(const char* label, float* val, float min, float max, const char* format) {
		bool ret = ImGui::SliderFloat(label, val, min, max, format);

		if (ret) gHistorySystem->RegisterHistoryItem();

		return ret;
	}

	__forceinline void WindowWidget(const char* label) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize({ 290, 30 }, 49, 35);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		window->DrawList->AddRectFilled(bb.Min, bb.Max, ImColor(47, 47, 47));
		window->DrawList->AddRectFilled(bb.Max - ImVec2(30, 30), bb.Max, ImColor(28, 28, 28));
		window->DrawList->AddText(bb.Min + ImVec2(268, 8), ImColor(255, 255, 255), (const char*)ICON_FA_PLUS_CIRCLE);
		window->DrawList->AddRect(bb.Min, bb.Max, ImColor(50, 50, 51));

		window->DrawList->AddText(bb.Min + ImVec2(10, 7), ImColor(255, 255, 255), "Base Window");

		if (ImGui::BeginPopup(std::string(label + std::string("popup")).c_str()))
		{
			ImGui::Dummy({ 0, 5 });

			if (Selectable("Add SetCursorPos"))
				gPrototypeSystem->addCursorPos({ 0, 0 });

			if (Selectable("Add SameLine"))
				gPrototypeSystem->addSameline(0.f);

			ImGui::Dummy({ 0, 5 });
			ImGui::Separator();
			ImGui::Dummy({ 0, 5 });

			if (Selectable("Add Child"))
				gPrototypeSystem->addChild({ 100, 100 });

			if (Selectable("Add Group"))
				gPrototypeSystem->addGroup();

			ImGui::Dummy({ 0, 5 });
			ImGui::Separator();
			ImGui::Dummy({ 0, 5 });

			if (Selectable("Add Checkbox")) gPrototypeSystem->addCheckbox();
			if (Selectable("Add SliderFloat")) gPrototypeSystem->addSliderFloat(0, 100);
			if (Selectable("Add SliderInt")) gPrototypeSystem->addSliderInt(0, 100);
			if (Selectable("Add Combo")) gPrototypeSystem->addCombo();
			if (Selectable("Add Button")) gPrototypeSystem->addButton();
			//if (Selectable("Add Colorpicker")) gPrototypeSystem->addColorpicker("name");

			//ImGui::Dummy({ 0, 5 });
			//ImGui::Separator();
			//ImGui::Dummy({ 0, 5 });

			//if (Selectable("Add Tab")) gPrototypeSystem->addTab("name");
			//if (Selectable("Add Subtab")) gPrototypeSystem->addSubtab("name");

			ImGui::Dummy({ 0, 5 });
			ImGui::EndPopup();
		}

		if (hovered && ImGui::IsMouseHoveringRect(bb.Max - ImVec2(30, 30), bb.Max) && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
			ImGui::OpenPopup(std::string(label + std::string("popup")).c_str());
	}

	__forceinline void PrototypeWidget(const char* label, widgetPrototype& item, int padding) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize({ 290, 30 }, 49, 35);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		auto getType = [](widgetPrototype layer) {
			if (layer.type == elementType::CURSOR_POS) return "SetCursorPos";
			if (layer.type == elementType::SAMELINE) return "SameLine";
			if (layer.type == elementType::CHILD) return "Child";
			if (layer.type == elementType::GROUP) return "Group";
			if (layer.type == elementType::TAB) return "Tab";
			if (layer.type == elementType::SUBTAB) return "Subtab";
			if (layer.type == elementType::CHECKBOX) return "Checkbox";
			if (layer.type == elementType::SLIDER_FLOAT) return "SliderFloat";
			if (layer.type == elementType::SLIDER_INT) return "SliderInt";
			if (layer.type == elementType::COMBO) return "Combo";
			if (layer.type == elementType::BUTTON) return "Button";
			if (layer.type == elementType::COLORPICKER) return "ColorPicker";
		};

		window->DrawList->AddRectFilled(bb.Min, bb.Max, ImColor(47, 47, 47));
		window->DrawList->AddRectFilled(bb.Min, bb.Min + ImVec2(30 * padding, 30), ImColor(28, 28, 28));
	
		window->DrawList->AddText(bb.Min + ImVec2(30 * padding + 10, 7), ImColor(255, 255, 255), item.name.empty() ? getType(item) : item.name.c_str());

		if (item.type == elementType::CHILD || item.type == elementType::GROUP) {
			window->DrawList->AddRectFilled(bb.Max - ImVec2(30, 30), bb.Max, ImColor(28, 28, 28));
			window->DrawList->AddText(bb.Min + ImVec2(268, 8), ImColor(255, 255, 255), (const char*)ICON_FA_PLUS_CIRCLE);

			if (ImGui::BeginPopup(std::string(label + std::string("popup")).c_str()))
			{
				ImGui::Dummy({ 0, 5 });

				if (Selectable("Add SetCursorPos")) item.addCursorPos({ 0, 0 });
				if (Selectable("Add SameLine")) item.addSameline(0.f);

				ImGui::Dummy({ 0, 5 });
				ImGui::Separator();
				ImGui::Dummy({ 0, 5 });

				if (Selectable("Add Child")) item.addChild({ 100, 100 });
				if (Selectable("Add Group")) item.addGroup();

				ImGui::Dummy({ 0, 5 });
				ImGui::Separator();
				ImGui::Dummy({ 0, 5 });

				if (Selectable("Add Checkbox")) item.addCheckbox();
				if (Selectable("Add SliderFloat")) item.addSliderFloat(0, 100);
				if (Selectable("Add SliderInt")) item.addSliderInt(0, 100);
				if (Selectable("Add Combo")) item.addCombo();
				if (Selectable("Add Button")) item.addButton();
				//if (Selectable("Add Colorpicker")) item.addColorpicker("name");

				//ImGui::Dummy({ 0, 5 });
				//ImGui::Separator();
				//ImGui::Dummy({ 0, 5 });

				//if (Selectable("Add Tab")) item.addTab("name");
				//if (Selectable("Add Subtab")) item.addSubtab("name");

				ImGui::Dummy({ 0, 5 });
				ImGui::EndPopup();
			}

			if (hovered && ImGui::IsMouseHoveringRect(bb.Max - ImVec2(30, 30), bb.Max) && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				ImGui::OpenPopup(std::string(label + std::string("popup")).c_str());
		}


		window->DrawList->AddRect(bb.Min + ImVec2(30 * padding, 0), bb.Max, ImColor(50, 50, 51));

		if (hovered) window->DrawList->AddRect(bb.Min + ImVec2(30 * padding, 0), bb.Max, ImColor(0, 166, 255));
	}
}