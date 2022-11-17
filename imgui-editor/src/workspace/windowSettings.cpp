#include "windowSettings.hpp"

#include "../utils/workspaceKeybinds.hpp"
#include "../utils/utils.hpp"
#include "../layerSystem/layerSystem.hpp"
#include "../layerSystem/layerManagement.hpp"
#include "../interface/interface.hpp"
#include "../interface/elements.hpp"
#include "../projects/projectSystem.hpp"

#include "../../dependencies/assets/hashes.h"
#include "../../dependencies/security/XorStr.hpp"
#include "../../dependencies/console/console.hpp"

void WindowSettings::Render()
{
	if (gContext.SelectedTab != 0 && gContext.SelectedTab != 1)
		return;

	ImGui::GetForegroundDrawList()->PushClipRect({ 345, 45 }, { ImGui::GetIO().DisplaySize.x - (gContext.SelectedLayer != -1 ? 260 : 0), ImGui::GetIO().DisplaySize.y });

	utils::PushSettings();

	ImGui::Begin(_S("BaseWindow"), 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	{
		auto pos = ImGui::GetWindowPos();
		auto draw = ImGui::GetWindowDrawList();
		gContext.RenderPos = pos;

		ImGui::SetWindowPos(ImGui::GetIO().DisplaySize / 2 - gProjectSystem->data.window.WindowSize / 2, ImGuiCond_Once);
		ImGui::SetWindowSize(gContext.ScaleM(gProjectSystem->data.window.WindowSize));

		gContext.WindowSize = gProjectSystem->data.window.WindowSize;

		ImGui::GetCurrentWindow()->FontWindowScale = round(ImGui::GetCurrentWindow()->FontWindowScale * 10000) / 10000;
		gContext.WindowScale = round(ImGui::GetCurrentWindow()->FontWindowScale * 10000) / 10000;

		layerManagement->Render(draw, drawTarget::Window);

		layerManagement->Resize(gContext.SelectedLayer);
		layerManagement->Select(gContext.SelectedLayer);
		layerManagement->Drag(gContext.SelectedLayer);
		layerManagement->AddLayer(drawTarget::Window, true);

		workspaceKeybinds->HandleMouse(ImGui::GetCurrentWindow()->Pos);
	}
	ImGui::End();

	ImGui::PopStyleVar(17);

	ImGui::GetForegroundDrawList()->PopClipRect();
}

void WindowSettings::Infobar()
{
	if (gContext.SelectedTab == 0 || gContext.SelectedTab == 1)
	{
		float zoom = gContext.WindowScale * 100.f;

		ImGui::SetCursorPos({ 5, 5 });
		if (elements::InvisibleInputFloat(_S("Zoom:"), _S("search"), zoom, "%0.f%%")) {
			zoom = std::clamp(zoom, 25.f, 1000.f);
			ImGui::FindWindowByName(_S("BaseWindow"))->FontWindowScale = zoom / 100.f;
		}

		ImGui::SetCursorPos({ 110, 5 });
		elements::InvisibleInputFloat(_S("Width:"), _S("second"), gProjectSystem->data.window.WindowSize.x, "%0.fpx");

		ImGui::SetCursorPos({ 215, 5 });
		elements::InvisibleInputFloat(_S("Height:"), _S("third"), gProjectSystem->data.window.WindowSize.y, "%0.fpx");

		ImGui::SetCursorPos({ ImGui::GetIO().DisplaySize.x - 100, 5 });
		if (elements::Save(_S("Save")))
			gFileSystem->SaveProject();
	}

	if (gContext.SelectedTab == 0)
	{
		ImGui::SetCursorPos({ 325, 5 });
		ImGui::BeginGroup();
		{
			layerManagement->Tools();
		}
		ImGui::EndGroup();
	}
}

void WindowSettings::Sidebar()
{
	if (gContext.SelectedTab == 0 && gContext.SelectedLayer != -1)
		layerManagement->Edit(gContext.SelectedLayer);
}

void WindowSettings::Mainbar()
{
	if (gContext.SelectedTab == 0) 
	{
		layerManagement->List(drawTarget::Window);
	}
	if (gContext.SelectedTab == 1) 
	{
		elements::Child(_S("Alpha"), { 286, 110 }, [&]() {
			ImGui::SliderFloat(_S("Alpha"), &gProjectSystem->data.window.Alpha, 0.f, 1.f, _S("%.02f"));
			ImGui::SliderFloat(_S("Disabled"), &gProjectSystem->data.window.DisabledAlpha, 0.f, 1.f, _S("%.02f"));
		});
		elements::Child(_S("Window"), { 286, 370 }, [&]() {
			ImGui::SliderFloat(_S("Rounding"), &gProjectSystem->data.window.WindowRounding, 0.f, 24, _S("%.0fpx"));
			ImGui::SliderFloat(_S("Border Size"), &gProjectSystem->data.window.WindowBorderSize, 0.f, 5.f, _S("%.0fpx"));
			ImGui::PushItemWidth(276);
			ImGui::InputFloat(_S("Minimal Size X"), &gProjectSystem->data.window.WindowMinSize.x, 0, 0, _S("%.0fpx"));
			ImGui::InputFloat(_S("Minimal Size Y"), &gProjectSystem->data.window.WindowMinSize.y, 0, 0, _S("%.0fpx"));
			ImGui::InputFloat(_S("Padding X"), &gProjectSystem->data.window.WindowPadding.x, 0, 0, _S("%.0fpx"));
			ImGui::InputFloat(_S("Padding Y"), &gProjectSystem->data.window.WindowPadding.y, 0, 0, _S("%.0fpx"));
			ImGui::InputFloat(_S("Title Align X"), &gProjectSystem->data.window.WindowTitleAlign.x, 0, 0, _S("%.02fpx"));
			ImGui::InputFloat(_S("Title Align Y"), &gProjectSystem->data.window.WindowTitleAlign.y, 0, 0, _S("%.02fpx"));
		});
		elements::Child(_S("Child"), { 286, 110 }, []() {
			ImGui::SliderFloat(_S("Rounding"), &gProjectSystem->data.window.ChildRounding, 0.f, 24, _S("%.0fpx"));
			ImGui::SliderFloat(_S("Border Size"), &gProjectSystem->data.window.ChildBorderSize, 0.f, 5.f, _S("%.0fpx"));
		});
		elements::Child(_S("Popup"), { 286, 110 }, []() {
			ImGui::SliderFloat(_S("Rounding"), &gProjectSystem->data.window.PopupRounding, 0.f, 24, _S("%.0fpx"));
			ImGui::SliderFloat(_S("Border Size"), &gProjectSystem->data.window.PopupBorderSize, 0.f, 5.f, _S("%.0fpx"));
		});
		elements::Child(_S("Widget"), { 286, 410 }, []() {
			ImGui::SliderFloat(_S("Frame Round"), &gProjectSystem->data.window.FrameRounding, 0.f, 24, _S("%.0fpx"));
			ImGui::SliderFloat(_S("Frame Border"), &gProjectSystem->data.window.FrameBorderSize, 0.f, 5.f, _S("%.0fpx"));
			ImGui::SliderFloat(_S("Indent Size"), &gProjectSystem->data.window.IndentSpacing, 0.f, 5.f, _S("%.0fpx"));
			ImGui::PushItemWidth(276);
			ImGui::InputFloat(_S("Item Inner Spacing X"), &gProjectSystem->data.window.ItemInnerSpacing.x, 0, 0, _S("%.0fpx"));
			ImGui::InputFloat(_S("Item Inner Spacing Y"), &gProjectSystem->data.window.ItemInnerSpacing.y, 0, 0, _S("%.0fpx"));
			ImGui::InputFloat(_S("Item Spacing X"), &gProjectSystem->data.window.ItemSpacing.x, 0, 0, _S("%.0fpx"));
			ImGui::InputFloat(_S("Item Spacing Y"), &gProjectSystem->data.window.ItemSpacing.y, 0, 0, _S("%.0fpx"));
			ImGui::InputFloat(_S("Frame Padding X"), &gProjectSystem->data.window.FramePadding.x, 0, 0, _S("%.0fpx"));
			ImGui::InputFloat(_S("Frame Padding Y"), &gProjectSystem->data.window.FramePadding.y, 0, 0, _S("%.0fpx"));
		});

		ImGui::NewLine();
		ImGui::NewLine();
	}
}
