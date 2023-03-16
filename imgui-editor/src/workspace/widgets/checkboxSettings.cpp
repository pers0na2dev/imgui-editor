#include "checkboxSettings.hpp"
#include "../../utils/workspaceKeybinds.hpp"

#include "../../utils/utils.hpp"
#include "../../layerSystem/layerSystem.hpp"
#include "../../layerSystem/layerManagement.hpp"
#include "../../interface/interface.hpp"
#include "../../interface/elements.hpp"
#include "../../projects/projectSystem.hpp"

#include "dependencies/assets/hashes.h"
#include "dependencies/security/XorStr.hpp"
#include "dependencies/console/console.hpp"

bool Checkbox(const char* label, bool* v)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	const ImRect total_bb(
		window->DC.CursorPos, 
		window->DC.CursorPos + gContext.ScaleM(gProjectSystem->data.checkbox.TotalSize)
	);
	const ImRect frame_bb(
		window->DC.CursorPos + gContext.ScaleM(gProjectSystem->data.checkbox.FramePos), 
		window->DC.CursorPos + gContext.ScaleM(gProjectSystem->data.checkbox.FrameSize)
	);

	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);

	layerManagement->Render(window->DrawList, drawTarget::Checkbox);
	layerManagement->Render(window->DrawList, *v ? drawTarget::CheckboxActive : drawTarget::CheckboxInactive);

	window->DrawList->AddText(
		gProjectSystem->data.checkbox.Font,
		gContext.ScaleM(gProjectSystem->data.checkbox.FontSize),
		total_bb.Min + gContext.ScaleM(gProjectSystem->data.checkbox.LabelPos),
		ImColor(255, 255, 255),
		"Checkbox"
	);

	return pressed;
}

void CheckboxSettings::Render()
{
	if (gContext.SelectedTab != 2)
		return;

	ImGui::GetForegroundDrawList()->PushClipRect({ 345, 45 }, { ImGui::GetIO().DisplaySize.x - (gContext.SelectedLayer != -1 ? 260 : 0), ImGui::GetIO().DisplaySize.y });

	utils::PushWidgetSettings();

	ImGui::Begin(_S("BaseWindow"), 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	{
		auto pos = ImGui::GetWindowPos();
		auto draw = ImGui::GetWindowDrawList();
		gContext.RenderPos = pos;

		ImGui::SetWindowPos(ImGui::GetIO().DisplaySize / 2 - gProjectSystem->data.checkbox.TotalSize / 2, ImGuiCond_Once);
		ImGui::SetWindowSize(gContext.ScaleM(gProjectSystem->data.checkbox.TotalSize));

		gContext.WindowSize = gProjectSystem->data.checkbox.TotalSize;

		ImGui::GetCurrentWindow()->FontWindowScale = round(ImGui::GetCurrentWindow()->FontWindowScale * 10000) / 10000;
		gContext.WindowScale = round(ImGui::GetCurrentWindow()->FontWindowScale * 10000) / 10000;

		Checkbox(_S("Checkbox"), &gContext.CheckboxState);

		layerManagement->Resize(gContext.SelectedLayer);
		layerManagement->Select(gContext.SelectedLayer);
		layerManagement->Drag(gContext.SelectedLayer);

		if (gContext.CheckboxLayer == 0) {
			layerManagement->AddLayer(drawTarget::Checkbox, true);
		} else if (gContext.CheckboxLayer == 1) {
			layerManagement->AddLayer(drawTarget::CheckboxActive, true);
		} else if (gContext.CheckboxLayer == 2) {
			layerManagement->AddLayer(drawTarget::CheckboxInactive, true);
		}

		workspaceKeybinds->HandleMouse(ImGui::GetCurrentWindow()->Pos);
	}
	ImGui::End();

	ImGui::PopStyleVar(17);

	ImGui::GetForegroundDrawList()->PopClipRect();
}

void CheckboxSettings::Infobar()
{
	if (gContext.SelectedTab == 2)
	{
		float zoom = gContext.WindowScale * 100.f;

		ImGui::SetCursorPos({ 5, 5 });
		if (elements::InvisibleInputFloat(_S("Zoom:"), _S("search"), zoom, "%0.f%%")) {
			zoom = std::clamp(zoom, 25.f, 1000.f);
			ImGui::FindWindowByName(_S("BaseWindow"))->FontWindowScale = zoom / 100.f;
		}

		ImGui::SetCursorPos({ ImGui::GetIO().DisplaySize.x - 100, 5 });
		if (elements::Save(_S("Save")))
			gFileSystem->SaveProject();

		ImGui::SetCursorPos({ 110, 5 });
		ImGui::BeginGroup();
		{
			layerManagement->Tools();
		}
		ImGui::EndGroup();
	}
}

void CheckboxSettings::Sidebar()
{
	if (gContext.SelectedTab == 2 && gContext.SelectedLayer != -1) {
		layerManagement->Edit(gContext.SelectedLayer);
	}
	
	if (gContext.SelectedTab == 2 && gContext.SelectedLayer == -1) {

		elements::Child("Widget Selection", { 260, 95 }, [&]() {
			ImGui::PushItemWidth(250);
			ImGui::Combo(_S("Widget"), &gContext.SelectedWidget, { "Checkbox" }, 1);
			ImGui::Checkbox(_S("Checkbox State"), &gContext.CheckboxState);
		});

		elements::Child("Total Size (total_bb)", { 260, 113 }, [&]() {
			ImGui::PushItemWidth(250);
			ImGui::InputFloat("Total Size X", &gProjectSystem->data.checkbox.TotalSize.x, 0.f, 0.f, "%0.f");
			ImGui::InputFloat("Total Size Y", &gProjectSystem->data.checkbox.TotalSize.y, 0.f, 0.f, "%0.f");
		});

		elements::Child("Active Zone Size (frame_bb)", { 260, 200 }, [&]() {
			ImGui::PushItemWidth(250);
			ImGui::InputFloat("Active Zone Size X", &gProjectSystem->data.checkbox.FrameSize.x, 0.f, 0.f, "%0.f");
			if (ImGui::IsItemActive()) {
				ImGui::GetForegroundDrawList()->AddRect(
					gContext.RenderPos + gContext.ScaleM(gProjectSystem->data.checkbox.FramePos),
					gContext.RenderPos + gContext.ScaleM(gProjectSystem->data.checkbox.FramePos) + gContext.ScaleM(gProjectSystem->data.checkbox.FrameSize),
					ImColor(255, 255, 153)
				);
			}
			ImGui::InputFloat("Active Zone Size Y", &gProjectSystem->data.checkbox.FrameSize.y, 0.f, 0.f, "%0.f");
			if (ImGui::IsItemActive()) {
				ImGui::GetForegroundDrawList()->AddRect(
					gContext.RenderPos + gContext.ScaleM(gProjectSystem->data.checkbox.FramePos),
					gContext.RenderPos + gContext.ScaleM(gProjectSystem->data.checkbox.FramePos) + gContext.ScaleM(gProjectSystem->data.checkbox.FrameSize),
					ImColor(255, 255, 153)
				);
			}
			ImGui::InputFloat("Position X", &gProjectSystem->data.checkbox.FramePos.x, 0.f, 0.f, "%0.f");
			if (ImGui::IsItemActive()) {
				ImGui::GetForegroundDrawList()->AddRect(
					gContext.RenderPos + gContext.ScaleM(gProjectSystem->data.checkbox.FramePos),
					gContext.RenderPos + gContext.ScaleM(gProjectSystem->data.checkbox.FramePos) + gContext.ScaleM(gProjectSystem->data.checkbox.FrameSize),
					ImColor(255, 255, 153)
				);
			}
			ImGui::InputFloat("Position Y", &gProjectSystem->data.checkbox.FramePos.y, 0.f, 0.f, "%0.f");
			if (ImGui::IsItemActive()) {
				ImGui::GetForegroundDrawList()->AddRect(
					gContext.RenderPos + gContext.ScaleM(gProjectSystem->data.checkbox.FramePos),
					gContext.RenderPos + gContext.ScaleM(gProjectSystem->data.checkbox.FramePos) + gContext.ScaleM(gProjectSystem->data.checkbox.FrameSize),
					ImColor(255, 255, 153)
				);
			}
		});

		elements::Child(_S("Label"), { 260, 405 }, [&]() {
			ImGui::PushItemWidth(250);
			elements::InputFloat(_S("Position X"), &gProjectSystem->data.checkbox.LabelPos.x, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Position Y"), &gProjectSystem->data.checkbox.LabelPos.y, 0.f, 0.f, _S("%0.f"));

			if (ImGui::BeginCombo(_S("Font"), gProjectSystem->data.checkbox.FontName.c_str())) {
				for (auto item : gLayerSystem->systemFonts) {
					if (ImGui::Selectable(item.name.c_str(), item.name == gProjectSystem->data.checkbox.FontName)) {
						gProjectSystem->data.checkbox.FontName = item.name;
						gProjectSystem->data.checkbox.FontFile = item.file;
						gProjectSystem->data.checkbox.Font = nullptr;
						gProjectSystem->data.checkbox._shouldRebuild = true;
					}
				}
				ImGui::EndCombo();
			}
			if (elements::SliderFloat(_S("Text Size"), &gProjectSystem->data.checkbox.FontSize, 1.f, 128.f, _S("%0.fpx"))) {
				gProjectSystem->data.checkbox.Font = nullptr;
				gProjectSystem->data.checkbox._shouldRebuild = true;
			}
		});
	}
}

void CheckboxSettings::Mainbar()
{
	if (gContext.SelectedTab == 2) 
	{
		elements::Child("Layer Selection", { 290, 70 }, [&]() {
			ImGui::PushItemWidth(280);
			const char* check[] = { "Background", "Active", "Inactive" };
			ImGui::Combo(_S("Layer Type"), &gContext.CheckboxLayer, check, 3);
		});

		if (gContext.CheckboxLayer == 0) {
			layerManagement->List(drawTarget::Checkbox);
		} else if (gContext.CheckboxLayer == 1) {
			layerManagement->List(drawTarget::CheckboxActive);
		} else if (gContext.CheckboxLayer == 2) {
			layerManagement->List(drawTarget::CheckboxInactive);
		}

		ImGui::NewLine();
		ImGui::NewLine();
	}
}
