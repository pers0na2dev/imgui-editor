#include "prototypeMananger.hpp"

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

#include "prototypeItems.hpp"

void RenderWidgets(std::vector<widgetPrototype>& prototypes, int padding, int counter = 0)
{
	static bool boleans[10024];
	static float floats[10024];
	static int integers[10024];
	static float colors[10024][4];

	const char* items[] = { "Value 1", "Value 2" };

	for (auto id = 0; id < prototypes.size(); id++)
	{
		counter += 1;

		ImGui::PushID(counter);
		{
			if (prototypes[id].type == elementType::CURSOR_POS)
				ImGui::SetCursorPos(prototypes[id].cursorPos);

			if (prototypes[id].type == elementType::SAMELINE)
				ImGui::SameLine(prototypes[id].fWidth);

			if (prototypes[id].type == elementType::CHECKBOX)
				Prototypes::Checkbox(prototypes[id].name.c_str(), &boleans[counter]);
			
			if (prototypes[id].type == elementType::SLIDER_FLOAT)
				Prototypes::SliderFloat(prototypes[id].name.c_str(), &floats[counter], 0.f, 100.f, "%0.2f", 1);

			if (prototypes[id].type == elementType::SLIDER_INT)
				Prototypes::SliderInt(prototypes[id].name.c_str(), &integers[counter], 0, 100, "%i", 1);

			if (prototypes[id].type == elementType::COMBO)
				Prototypes::Combo(prototypes[id].name.c_str(), &integers[counter], items, 2);

			if (prototypes[id].type == elementType::BUTTON)
				Prototypes::Button(prototypes[id].name.c_str(), prototypes[id].btnSize);
		}
		ImGui::PopID();

		if (prototypes[id].type == elementType::CHILD) {
			ImGui::BeginChild(std::string(prototypes[id].name + std::to_string(counter)).c_str(), prototypes[id].childSize);
			RenderWidgets(prototypes[id].items, padding + 1, counter + 100);
			ImGui::EndChild();
		}

		if (prototypes[id].type == elementType::GROUP) {
			ImGui::BeginGroup();
			RenderWidgets(prototypes[id].items, padding + 1, counter + 100);
			ImGui::EndGroup();
		}
	}
}

void PrototypeManager::Render()
{
	if (gContext.SelectedTab != 3)
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
		RenderWidgets(gPrototypeSystem->prototypes, 1);

		workspaceKeybinds->HandleMouse(ImGui::GetCurrentWindow()->Pos);
	}
	ImGui::End();

	ImGui::PopStyleVar(17);

	ImGui::GetForegroundDrawList()->PopClipRect();
}

void PrototypeManager::Infobar()
{
	if (gContext.SelectedTab != 3)
		return;

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

void PrototypeManager::Sidebar()
{
	if (gContext.SelectedTab != 3)
		return;

	if (currentEditor == nullptr)
		return;

	elements::Child(_S("Naming"), { 260, 85 }, [&]() {
		ImGui::PushItemWidth(250);

		char text[256];
		strcpy_s(text, currentEditor->name.c_str());

		if (ImGui::InputText(_S("Text"), text, 256)) {
			currentEditor->name = text;
		}
	});

	if (currentEditor->type == elementType::CURSOR_POS) {
		elements::Child(_S("Positions"), { 260, 205 }, [&]() {
			ImGui::PushItemWidth(250);
			elements::InputFloat("X", &currentEditor->cursorPos.x, 0.f, 0.f, "%0.f");
			elements::InputFloat("Y", &currentEditor->cursorPos.y, 0.f, 0.f, "%0.f");
		});
	}

	if (currentEditor->type == elementType::CHILD) {
		elements::Child(_S("Sizing"), { 260, 205 }, [&]() {
			ImGui::PushItemWidth(250);
			elements::InputFloat("X", &currentEditor->childSize.x, 0.f, 0.f, "%0.f");
			elements::InputFloat("Y", &currentEditor->childSize.y, 0.f, 0.f, "%0.f");
		});
	}

	if (currentEditor->type == elementType::SAMELINE) {
		elements::Child(_S("Sizing"), { 260, 205 }, [&]() {
			ImGui::PushItemWidth(250);
			elements::InputFloat("X", &currentEditor->fWidth, 0.f, 0.f, "%0.f");
		});
	}

	if (currentEditor->type == elementType::BUTTON) {
		elements::Child(_S("Sizing"), { 260, 205 }, [&]() {
			ImGui::PushItemWidth(250);
			elements::InputFloat("X", &currentEditor->btnSize.x, 0.f, 0.f, "%0.f");
			elements::InputFloat("Y", &currentEditor->btnSize.y, 0.f, 0.f, "%0.f");
		});
	}
}

void RenderWidgetsList(std::vector<widgetPrototype>& prototypes, int padding, int counter = 0) 
{
	int move_from = -5, move_to = -5;

	for (auto id = 0; id < prototypes.size(); id++)
	{
		counter += 1;

		ImGui::PushID(counter);
		elements::PrototypeWidget(std::to_string(counter).c_str(), prototypes[id], padding);

		if (ImGui::BeginDragDropSource())
		{
			elements::PrototypeWidget(std::to_string(counter).c_str(), prototypes[id], padding);
			ImGui::SetDragDropPayload("dnd", &id, sizeof(int));
			ImGui::EndDragDropSource();
		}

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("dnd", ImGuiDragDropFlags_AcceptNoDrawDefaultRect))
			{
				move_from = *(const int*)payload->Data;
				move_to = id;
			}

			ImGui::EndDragDropTarget();
		}

		if (ImGui::IsItemClicked(0))
			prototypeManager->currentEditor = &prototypes[id];

		if (ImGui::BeginPopup(std::string(std::to_string(counter) + std::string("popup1")).c_str()))
		{
			ImGui::Dummy({ 0, 5 });

			if (elements::Selectable("Delete")) { prototypes.erase(prototypes.begin() + id); ImGui::CloseCurrentPopup(); };

			ImGui::Dummy({ 0, 5 });
			ImGui::EndPopup();
		}

		if (ImGui::IsItemClicked(1))
			ImGui::OpenPopup(std::string(std::to_string(counter) + std::string("popup1")).c_str());

		ImGui::PopID();

		if (prototypes[id].type == elementType::CHILD || prototypes[id].type == elementType::GROUP) {
			RenderWidgetsList(prototypes[id].items, padding + 1, counter + 100);
		}
	}

	if (move_from != -5 && move_to != -5)
	{
		widgetPrototype temp = prototypes[move_to];
		prototypes[move_to] = prototypes[move_from];
		prototypes[move_from] = temp;

		ImGui::SetDragDropPayload("dnd", &move_to, sizeof(int));
	}
}

void PrototypeManager::Mainbar()
{
	if (gContext.SelectedTab != 3)
		return;

	elements::WindowWidget(_S("BaseWindowElement"));
	RenderWidgetsList(gPrototypeSystem->prototypes, 1);
}
