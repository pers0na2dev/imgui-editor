#include "layerManagement.hpp"

#include "../interface/elements.hpp"
#include "../utils/utils.hpp"
#include "../context.hpp"

void LayerManagement::Render(ImDrawList* draw, drawTarget target)
{
	for (auto a = 0; a < gProjectSystem->data.layers.size(); a++)
	{
		if (gProjectSystem->data.layers[a].target == target)
		{
			gProjectSystem->data.layers[a].Render(draw, gContext.WindowScale, a);
		}
	}
}

void LayerManagement::List(drawTarget target)
{
	int move_from = -5, move_to = -5;

	for (auto a = 0; a < gProjectSystem->data.layers.size(); a++)
	{
		if (gProjectSystem->data.layers[a].target != target)
		{
			continue;
		}

		ImGui::PushID(a);
		elements::Layer(gProjectSystem->data.layers[a].name.c_str(), gProjectSystem->data.layers[a], a);
		ImGui::PopID();

		if (ImGui::IsItemClicked())
		{
			gContext.SelectedLayer = a;
		}

		if (ImGui::BeginDragDropSource())
		{
			elements::Layer(gProjectSystem->data.layers[a].name.c_str(), gProjectSystem->data.layers[a], a);
			ImGui::SetDragDropPayload("dnd", &a, sizeof(int));
			ImGui::EndDragDropSource();
		}

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("dnd", ImGuiDragDropFlags_AcceptNoDrawDefaultRect))
			{
				move_from = *(const int*)payload->Data;
				move_to = a;
			}

			ImGui::EndDragDropTarget();
		}
	}

	if (move_from != -5 && move_to != -5)
	{
		layerStruct temp = gProjectSystem->data.layers[move_to];
		gProjectSystem->data.layers[move_to] = gProjectSystem->data.layers[move_from];
		gProjectSystem->data.layers[move_from] = temp;

		ImGui::SetDragDropPayload("dnd", &move_to, sizeof(int));
	}
}

void LayerManagement::Edit(int index)
{
	const char* roundingTypes[] = {
		"None", "Top Left", "Top Right", "Bot Left", "Bot Right", "All", "Top", "Bot", "Left", "Right"
	};

	if (gProjectSystem->data.layers[index].type == drawType::Line)
	{
		elements::Child(_S("Positions"), { 260, 205 }, [&]() {
			ImGui::PushItemWidth(250);
			elements::InputFloat(_S("Start Position X"), &gProjectSystem->data.layers[index].pos.x, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Start Position Y"), &gProjectSystem->data.layers[index].pos.y, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Size X"), &gProjectSystem->data.layers[index].size.x, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Size Y"), &gProjectSystem->data.layers[index].size.y, 0.f, 0.f, _S("%0.f"));
			});

		elements::Child(_S("Styles"), { 260, 118 }, [&]() {
			ImGui::PushItemWidth(250);
			elements::SliderFloat(_S("Thikness"), &gProjectSystem->data.layers[index].thickness, 1.f, 5.f, _S("%0.fpx"));
			elements::Colorpicker(_S("Color"), gProjectSystem->data.layers[index].color);
			});
	}
	else if (gProjectSystem->data.layers[index].type == drawType::Rectangle)
	{
		elements::Child(_S("Positions"), { 260, 205 }, [&]() {
			ImGui::PushItemWidth(250);
			elements::InputFloat(_S("Start Position X"), &gProjectSystem->data.layers[index].pos.x, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Start Position Y"), &gProjectSystem->data.layers[index].pos.y, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Size X"), &gProjectSystem->data.layers[index].size.x, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Size Y"), &gProjectSystem->data.layers[index].size.y, 0.f, 0.f, _S("%0.f"));
			});

		elements::Child(_S("Styles"), { 260, 212 }, [&]() {
			ImGui::PushItemWidth(250);
			elements::SliderFloat(_S("Thikness"), &gProjectSystem->data.layers[index].thickness, 1.f, 5.f, _S("%0.fpx"));
			elements::SliderFloat(_S("Rounding"), &gProjectSystem->data.layers[index].rounding, 0.f, 24.f, _S("%0.fpx"));

			if (ImGui::Combo(_S("Round Corners"), &gProjectSystem->data.layers[index]._round, roundingTypes, 10)) {
				if (gProjectSystem->data.layers[index]._round == 0) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_None;
				if (gProjectSystem->data.layers[index]._round == 1) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_TopLeft;
				if (gProjectSystem->data.layers[index]._round == 2) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_TopRight;
				if (gProjectSystem->data.layers[index]._round == 3) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_BotLeft;
				if (gProjectSystem->data.layers[index]._round == 4) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_BotRight;
				if (gProjectSystem->data.layers[index]._round == 5) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_All;
				if (gProjectSystem->data.layers[index]._round == 6) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_Top;
				if (gProjectSystem->data.layers[index]._round == 7) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_Bot;
				if (gProjectSystem->data.layers[index]._round == 8) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_Left;
				if (gProjectSystem->data.layers[index]._round == 9) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_Right;
			}
			elements::Colorpicker(_S("Color"), gProjectSystem->data.layers[index].color);
			});
	}
	else if (gProjectSystem->data.layers[index].type == drawType::Circle || gProjectSystem->data.layers[index].type == drawType::CircleFilled)
	{
		elements::Child(_S("Positions"), { 260, 205 }, [&]() {
			ImGui::PushItemWidth(250);
			elements::InputFloat(_S("Start Position X"), &gProjectSystem->data.layers[index].pos.x, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Start Position Y"), &gProjectSystem->data.layers[index].pos.y, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Size X"), &gProjectSystem->data.layers[index].size.x, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Size Y"), &gProjectSystem->data.layers[index].size.y, 0.f, 0.f, _S("%0.f"));
			});

		elements::Child(_S("Styles"), { 260, 140 }, [&]() {
			elements::Colorpicker(_S("Color"), gProjectSystem->data.layers[index].color);
			if(gProjectSystem->data.layers[index].type == drawType::Circle)
				elements::SliderFloat(_S("Thikness"), &gProjectSystem->data.layers[index].thickness, 1.f, 5.f, _S("%0.fpx"));
		});
	}
	else if (gProjectSystem->data.layers[index].type == drawType::RectangleFilled)
	{
		elements::Child(_S("Positions"), { 260, 205 }, [&]() {
			ImGui::PushItemWidth(250);
			elements::InputFloat(_S("Start Position X"), &gProjectSystem->data.layers[index].pos.x, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Start Position Y"), &gProjectSystem->data.layers[index].pos.y, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Size X"), &gProjectSystem->data.layers[index].size.x, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Size Y"), &gProjectSystem->data.layers[index].size.y, 0.f, 0.f, _S("%0.f"));
			});

		elements::Child(_S("Styles"), { 260, 162 }, [&]() {
			ImGui::PushItemWidth(250);
			ImGui::SliderFloat(_S("Rounding"), &gProjectSystem->data.layers[index].rounding, 0.f, 24.f, _S("%0.fpx"));
			if (ImGui::Combo(_S("Round Corners"), &gProjectSystem->data.layers[index]._round, roundingTypes, 10)) {
				if (gProjectSystem->data.layers[index]._round == 0) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_None;
				if (gProjectSystem->data.layers[index]._round == 1) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_TopLeft;
				if (gProjectSystem->data.layers[index]._round == 2) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_TopRight;
				if (gProjectSystem->data.layers[index]._round == 3) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_BotLeft;
				if (gProjectSystem->data.layers[index]._round == 4) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_BotRight;
				if (gProjectSystem->data.layers[index]._round == 5) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_All;
				if (gProjectSystem->data.layers[index]._round == 6) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_Top;
				if (gProjectSystem->data.layers[index]._round == 7) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_Bot;
				if (gProjectSystem->data.layers[index]._round == 8) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_Left;
				if (gProjectSystem->data.layers[index]._round == 9) gProjectSystem->data.layers[index].roundFlags = ImDrawCornerFlags_Right;
			}

			elements::Colorpicker(_S("Color"), gProjectSystem->data.layers[index].color);
			});
	}
	else if (gProjectSystem->data.layers[index].type == drawType::Image)
	{
		elements::Child(_S("Positions"), { 260, 205 }, [&]() {
			ImGui::PushItemWidth(250);
			elements::InputFloat(_S("Start Position X"), &gProjectSystem->data.layers[index].pos.x, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Start Position Y"), &gProjectSystem->data.layers[index].pos.y, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Size X"), &gProjectSystem->data.layers[index].size.x, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Size Y"), &gProjectSystem->data.layers[index].size.y, 0.f, 0.f, _S("%0.f"));
			});
	}
	else if (gProjectSystem->data.layers[index].type == drawType::Text)
	{
		gProjectSystem->data.layers[index].textSize = gProjectSystem->data.layers[index].font->CalcTextSizeA(
			gProjectSystem->data.layers[index].fontSize, FLT_MAX,
			gProjectSystem->data.layers[index].size.x, gProjectSystem->data.layers[index].textValue.c_str()
		);

		elements::Child(_S("Positions"), { 260, 205 }, [&]() {
			ImGui::PushItemWidth(250);
			elements::InputFloat(_S("Start Position X"), &gProjectSystem->data.layers[index].pos.x, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Start Position Y"), &gProjectSystem->data.layers[index].pos.y, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Size X"), &gProjectSystem->data.layers[index].size.x, 0.f, 0.f, _S("%0.f"));
			elements::InputFloat(_S("Size Y"), &gProjectSystem->data.layers[index].size.y, 0.f, 0.f, _S("%0.f"));
			});

		elements::Child(_S("Text"), { 260, 245 }, [&]() {
			ImGui::PushItemWidth(250);

			char text[256];
			strcpy_s(text, gProjectSystem->data.layers[index].textValue.c_str());

			if (ImGui::InputText(_S("Text"), text, 256)) {
				gProjectSystem->data.layers[index].textValue = text;
				gProjectSystem->data.layers[index].textSize = gProjectSystem->data.layers[index].font->CalcTextSizeA(
					gProjectSystem->data.layers[index].fontSize, FLT_MAX, 0, gProjectSystem->data.layers[index].textValue.c_str()
				);

				gHistorySystem->RegisterHistoryItem();
			}
			if (ImGui::BeginCombo(_S("Font"), gProjectSystem->data.layers[index].fontName.c_str())) {
				for (auto item : gLayerSystem->systemFonts) {
					if (ImGui::Selectable(item.name.c_str(), item.name == gProjectSystem->data.layers[index].fontName)) {
						gProjectSystem->data.layers[index].fontName = item.name;
						gProjectSystem->data.layers[index].fontFile = item.file;
						gProjectSystem->data.layers[index].font = nullptr;
						gProjectSystem->data.layers[index]._shouldRebuild = true;
						
						gHistorySystem->RegisterHistoryItem();
					}
				}
				ImGui::EndCombo();
			}
			if (elements::SliderFloat(_S("Text Size"), &gProjectSystem->data.layers[index].fontSize, 1.f, 128.f, _S("%0.fpx"))) {
				gProjectSystem->data.layers[index].font = nullptr;
				gProjectSystem->data.layers[index]._shouldRebuild = true;
			}

			elements::Colorpicker(_S("Color"), gProjectSystem->data.layers[index].color);

			ImGui::BeginGroup();
			{
				elements::ItemGrouped("Align Left", (const char*)ICON_FA_ALIGN_LEFT, gProjectSystem->data.layers[index].textAlignX, 0);
				ImGui::SameLine();
				elements::ItemGrouped("Align Center", (const char*)ICON_FA_ALIGN_CENTER, gProjectSystem->data.layers[index].textAlignX, 1);
				ImGui::SameLine();
				elements::ItemGrouped("Align Right", (const char*)ICON_FA_ALIGN_RIGHT, gProjectSystem->data.layers[index].textAlignX, 2);
			}
			ImGui::EndGroup();
			ImGui::SameLine(150);
			ImGui::BeginGroup();
			{
				elements::ItemGrouped("Align Top", (const char*)ICON_FA_ARROW_TO_TOP, gProjectSystem->data.layers[index].textAlignY, 0);
				ImGui::SameLine();
				elements::ItemGrouped("Align Center 2", (const char*)ICON_FA_HORIZONTAL_RULE, gProjectSystem->data.layers[index].textAlignY, 1);
				ImGui::SameLine();
				elements::ItemGrouped("Align Bot", (const char*)ICON_FA_ARROW_TO_BOTTOM, gProjectSystem->data.layers[index].textAlignY, 2);
			}
			ImGui::EndGroup();
			});
	}
}

void LayerManagement::AddLayer(drawTarget target, bool sideWorkspace)
{
	if (sideWorkspace && !gContext.MouseInWorkspaceSide())
		return;

	if (!sideWorkspace && !gContext.MouseInWorkspace())
		return;

	if (ImGui::IsPopupOpen("", ImGuiPopupFlags_AnyPopup) || gContext.InResize || gContext.SelectedEditor == 0)
		return;

	static layerStruct layerData;

	layerData.target = target;
	layerData.color = ImColor(255, 255, 255);

	if (gContext.SelectedEditor == 1)
	{
		layerData.type = drawType::Line;
	}
	else if (gContext.SelectedEditor == 2)
	{
		layerData.type = drawType::Rectangle;
	}
	else if (gContext.SelectedEditor == 3)
	{
		layerData.type = drawType::RectangleFilled;
	}
	else if (gContext.SelectedEditor == 4)
	{
		layerData.type = drawType::Text;
		layerData.textValue = "Sample Text";
		layerData.fontFile = gLayerSystem->systemFonts[0].file;
		layerData.fontName = gLayerSystem->systemFonts[0].name;
		layerData.fontSize = 13.f;
		layerData._shouldRebuild = true;
	}
	else if (gContext.SelectedEditor == 5)
	{
		layerData.type = drawType::Circle;
	}
	else if (gContext.SelectedEditor == 6)
	{
		layerData.type = drawType::CircleFilled;
	}

	if (ImGui::IsMouseClicked(0))
	{
		layerData.pos = gContext.ScaleD(ImGui::GetIO().MousePos - gContext.RenderPos);
	}

	if (ImGui::IsMouseReleased(0))
	{
		layerData.size = gContext.ScaleD(ImGui::GetIO().MousePos - ImGui::GetWindowPos()) - layerData.pos;

		if (layerData.pos.x != layerData.pos.x + layerData.size.x && layerData.pos.y != layerData.pos.y + layerData.size.y)
		{
			if (gContext.SelectedEditor != 1)
			{
				if (layerData.size.x < 0)
				{
					layerData.pos.x = layerData.pos.x - abs(layerData.size.x);
					layerData.size.x = abs(layerData.size.x);
				}
				if (layerData.size.y < 0)
				{
					layerData.pos.y = layerData.pos.y - abs(layerData.size.y);
					layerData.size.y = abs(layerData.size.y);
				}
			}

			gLayerSystem->RegisterItem(layerData);
			gContext.SelectedLayer = gProjectSystem->data.layers.size() - 1;

			layerData = layerStruct{};
			gContext.SelectedEditor = 0;

			gHistorySystem->RegisterHistoryItem();
		}
	}
	if (ImGui::IsMouseDown(0))
	{
		if (gContext.SelectedEditor == 1)
		{
			ImGui::GetForegroundDrawList()->AddLineDashed(
				gContext.RenderPos + gContext.ScaleM(layerData.pos),
				gContext.RenderPos + ImGui::GetIO().MousePos - ImGui::GetWindowPos(),
				ImColor(255, 255, 255), 1.f
			);
		}
		else if (gContext.SelectedEditor == 5 || gContext.SelectedEditor == 6)
		{
			auto size = gContext.ScaleD(ImGui::GetIO().MousePos - ImGui::GetWindowPos()) - layerData.pos;
			float radius;

			if (size.x < size.y)
				radius = size.x / 2;
			else
				radius = size.y / 2;

			ImGui::GetForegroundDrawList()->AddCircleDashed(
				gContext.RenderPos + gContext.ScaleM(layerData.pos) + size / 2,
				gContext.ScaleM(radius),
				ImColor(255, 255, 255), 32
			);
		}
		else
		{
			elements::DashedRect(ImGui::GetForegroundDrawList(),
				gContext.RenderPos + gContext.ScaleM(layerData.pos),
				gContext.RenderPos + ImGui::GetIO().MousePos - ImGui::GetWindowPos(),
				ImColor(255, 255, 255), 1.f
			);
		}
	}
}

void LayerManagement::Drag(int index)
{
	if (gContext.SelectedLayer == -1 || gContext.SelectedEditor != 0 || gContext.SelectedTab == 1)
		return;

	if (gContext.InResize)
		return;

	if (ImGui::IsPopupOpen("", ImGuiPopupFlags_AnyPopup))
		return;

	if (!ImGui::IsMouseHoveringRect(
		gContext.RenderPos + gContext.ScaleM(gProjectSystem->data.layers[index].pos) + ImGui::GetIO().MouseDelta,
		gContext.RenderPos + gContext.ScaleM(gProjectSystem->data.layers[index].pos + gProjectSystem->data.layers[index].size) + ImGui::GetIO().MouseDelta,
		false))
		return;

	if (ImGui::IsMouseReleased(0)) {
		gHistorySystem->RegisterHistoryItem();
	}

	if (!ImGui::GetIO().MouseDown[ImGuiMouseButton_Left])
		return;

	if (gProjectSystem->data.layers[index]._locked)
		return;

	ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);

	gProjectSystem->data.layers[index].pos += gContext.ScaleD(ImGui::GetIO().MouseDelta);

	if (gContext.SelectedTab == 2)
		return;

	if (sqrtf(powf(ImGui::GetIO().MouseDelta.x, 2) + powf(ImGui::GetIO().MouseDelta.y, 2)) < gContext.ScaleD(8) && ImGui::IsMouseDragging(0))
	{
		if (gProjectSystem->data.layers[index].pos.x < 2 && gProjectSystem->data.layers[index].pos.x > -2)
			ImGui::GetForegroundDrawList()->AddLine({ gContext.RenderPos.x - 1, 0 }, { gContext.RenderPos.x - 1, 5000 }, ImColor(255, 71, 10)),
			gProjectSystem->data.layers[index].pos.x = 0;

		if (gProjectSystem->data.layers[index].pos.y < 2 && gProjectSystem->data.layers[index].pos.y > -2)
			ImGui::GetForegroundDrawList()->AddLine({ 0, gContext.RenderPos.y - 1 }, { 5000, gContext.RenderPos.y - 1 }, ImColor(255, 71, 10)),
			gProjectSystem->data.layers[index].pos.y = 0;

		if (gContext.WindowSize.x - gProjectSystem->data.layers[index].pos.x - gProjectSystem->data.layers[index].size.x < 2 &&
			gContext.WindowSize.x - gProjectSystem->data.layers[index].pos.x - gProjectSystem->data.layers[index].size.x > -2)
			ImGui::GetForegroundDrawList()->AddLine({ gContext.RenderPos.x + gContext.ScaleM(gContext.WindowSize.x) + 1, 0 },
				{ gContext.RenderPos.x + gContext.ScaleM(gContext.WindowSize.x) + 1, 5000 }, ImColor(255, 71, 10)),
			gProjectSystem->data.layers[index].pos.x = gContext.WindowSize.x - gProjectSystem->data.layers[index].size.x;

		if (gContext.WindowSize.y - gProjectSystem->data.layers[index].pos.y - gProjectSystem->data.layers[index].size.y < 2 &&
			gContext.WindowSize.y - gProjectSystem->data.layers[index].pos.y - gProjectSystem->data.layers[index].size.y > -2)
			ImGui::GetForegroundDrawList()->AddLine({ 0, gContext.RenderPos.y + gContext.ScaleM(gContext.WindowSize.y) + 1 },
				{ 5000, gContext.RenderPos.y + gContext.ScaleM(gContext.WindowSize.y) + 1 }, ImColor(255, 71, 10)),
			gProjectSystem->data.layers[index].pos.y = gContext.WindowSize.y - gProjectSystem->data.layers[index].size.y;

		if (gContext.ScaleD(gProjectSystem->data.layers[index].pos.x) + gContext.ScaleD(gProjectSystem->data.layers[index].size.x) / 2 < gContext.ScaleD(gContext.WindowSize.x) / 2 + 2 &&
			gContext.ScaleD(gProjectSystem->data.layers[index].pos.x) + gContext.ScaleD(gProjectSystem->data.layers[index].size.x) / 2 > gContext.ScaleD(gContext.WindowSize.x) / 2 - 2) {
			ImGui::GetForegroundDrawList()->AddLine(
				{ gContext.RenderPos.x + gContext.ScaleM(gContext.WindowSize.x) / 2, gContext.RenderPos.y },
				{ gContext.RenderPos.x + gContext.ScaleM(gContext.WindowSize.x) / 2, gContext.RenderPos.y + gContext.ScaleM(gContext.WindowSize.y) },
				ImColor(255, 71, 10)
			);
			gProjectSystem->data.layers[index].pos.x = gContext.WindowSize.x / 2 - gProjectSystem->data.layers[index].size.x / 2;
		}

		if (gContext.ScaleD(gProjectSystem->data.layers[index].pos.y) + gContext.ScaleD(gProjectSystem->data.layers[index].size.y) / 2 < gContext.ScaleD(gContext.WindowSize.y) / 2 + 2 &&
			gContext.ScaleD(gProjectSystem->data.layers[index].pos.y) + gContext.ScaleD(gProjectSystem->data.layers[index].size.y) / 2 > gContext.ScaleD(gContext.WindowSize.y) / 2 - 2) {
			ImGui::GetForegroundDrawList()->AddLine(
				{ gContext.RenderPos.x, gContext.RenderPos.y + gContext.ScaleM(gContext.WindowSize.y) / 2 },
				{ gContext.RenderPos.x + gContext.ScaleM(gContext.WindowSize.x), gContext.RenderPos.y + gContext.ScaleM(gContext.WindowSize.y) / 2 },
				ImColor(255, 71, 10)
			);
			gProjectSystem->data.layers[index].pos.y = gContext.WindowSize.y / 2 - gProjectSystem->data.layers[index].size.y / 2;
		}
	}
}

void LayerManagement::Resize(int index)
{
	if (gContext.SelectedLayer == -1 || gContext.SelectedTab == 1 || gContext.SelectedEditor != 0)
		return;

	if (ImGui::IsPopupOpen("", ImGuiPopupFlags_AnyPopup))
		return;

	if (!gProjectSystem->data.layers[index]._show)
		return;

	auto lockBackup = gProjectSystem->data.layers[index]._locked;

	utils::RenderMiniRect(gProjectSystem->data.layers[index].pos);
	utils::RenderMiniRect(gProjectSystem->data.layers[index].pos + gProjectSystem->data.layers[index].size);
	utils::RenderMiniRect(ImVec2(gProjectSystem->data.layers[index].pos.x, gProjectSystem->data.layers[index].pos.y + gProjectSystem->data.layers[index].size.y));
	utils::RenderMiniRect(ImVec2(gProjectSystem->data.layers[index].pos.x + gProjectSystem->data.layers[index].size.x, gProjectSystem->data.layers[index].pos.y));

	if (utils::HandleMiniRect(gProjectSystem->data.layers[index].pos))
	{
		if (ImGui::IsMouseDown(0))
		{
			gProjectSystem->data.layers[index]._locked = true;
			gProjectSystem->data.layers[index].pos += gContext.ScaleD(ImGui::GetIO().MouseDelta);
			gProjectSystem->data.layers[index].size -= gContext.ScaleD(ImGui::GetIO().MouseDelta);
			gProjectSystem->data.layers[index]._locked = lockBackup;
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNWSE);
		}

		if (ImGui::IsMouseReleased(0)) {
			gHistorySystem->RegisterHistoryItem();
		}
	}
	else if (utils::HandleMiniRect(gProjectSystem->data.layers[index].pos + gProjectSystem->data.layers[index].size))
	{
		if (ImGui::IsMouseDown(0))
		{
			gProjectSystem->data.layers[index]._locked = true;
			gProjectSystem->data.layers[index].size += gContext.ScaleD(ImGui::GetIO().MouseDelta);
			gProjectSystem->data.layers[index]._locked = lockBackup;
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNWSE);
		}


		if (ImGui::IsMouseReleased(0)) {
			gHistorySystem->RegisterHistoryItem();
		}
	}
	else if (utils::HandleMiniRect(ImVec2(gProjectSystem->data.layers[index].pos.x, gProjectSystem->data.layers[index].pos.y + gProjectSystem->data.layers[index].size.y)))
	{
		if (ImGui::IsMouseDown(0))
		{
			gProjectSystem->data.layers[index]._locked = true;
			gProjectSystem->data.layers[index].pos.x += gContext.ScaleD(ImGui::GetIO().MouseDelta.x);
			gProjectSystem->data.layers[index].size.x -= gContext.ScaleD(ImGui::GetIO().MouseDelta.x);
			gProjectSystem->data.layers[index].size.y += gContext.ScaleD(ImGui::GetIO().MouseDelta.y);
			gProjectSystem->data.layers[index]._locked = lockBackup;
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNESW);
		}

		if (ImGui::IsMouseReleased(0)) {
			gHistorySystem->RegisterHistoryItem();
		}
	}
	else if (utils::HandleMiniRect(ImVec2(gProjectSystem->data.layers[index].pos.x + gProjectSystem->data.layers[index].size.x, gProjectSystem->data.layers[index].pos.y)))
	{
		if (ImGui::IsMouseDown(0))
		{
			gProjectSystem->data.layers[index]._locked = true;
			gProjectSystem->data.layers[index].size.x += gContext.ScaleD(ImGui::GetIO().MouseDelta.x);
			gProjectSystem->data.layers[index].size.y -= gContext.ScaleD(ImGui::GetIO().MouseDelta.y);
			gProjectSystem->data.layers[index].pos.y += gContext.ScaleD(ImGui::GetIO().MouseDelta.y);
			gProjectSystem->data.layers[index]._locked = lockBackup;
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNESW);
		}

		if (ImGui::IsMouseReleased(0)) {
			gHistorySystem->RegisterHistoryItem();
		}
	}

	if (gProjectSystem->data.layers[index].type != drawType::Line)
	{
		if (gProjectSystem->data.layers[index].size.x < 0)
		{
			gProjectSystem->data.layers[index].pos.x = gProjectSystem->data.layers[index].pos.x - abs(gProjectSystem->data.layers[index].size.x);
			gProjectSystem->data.layers[index].size.x = abs(gProjectSystem->data.layers[index].size.x);
		}

		if (gProjectSystem->data.layers[index].size.y < 0)
		{
			gProjectSystem->data.layers[index].pos.y = gProjectSystem->data.layers[index].pos.y - abs(gProjectSystem->data.layers[index].size.y);
			gProjectSystem->data.layers[index].size.y = abs(gProjectSystem->data.layers[index].size.y);
		}
	}
}

void LayerManagement::Select(int index)
{
	if (gContext.SelectedLayer == -1)
		return;

	if (ImGui::IsPopupOpen("", ImGuiPopupFlags_AnyPopup))
		return;

	if (gContext.SelectedEditor != 0)
		return;

	if (!gProjectSystem->data.layers[index]._show)
		return;

	ImGui::GetForegroundDrawList()->AddRect(
		gContext.RenderPos + gContext.ScaleM(gProjectSystem->data.layers[index].pos) - ImVec2(1, 1),
		gContext.RenderPos + gContext.ScaleM(gProjectSystem->data.layers[index].pos + gProjectSystem->data.layers[index].size) + ImVec2(1, 1),
		ImColor(0, 166, 255)
	);
}

void LayerManagement::Tools()
{
	auto Mouse = [](ImDrawList* draw, ImVec2 min, ImVec2 max) {
		draw->AddText(min + ImVec2(36, 36) / 2 - ImGui::CalcTextSize((const char*)ICON_FA_MOUSE) / 2, ImColor(255, 255, 255), (const char*)ICON_FA_MOUSE);
	};
	auto Line = [](ImDrawList* draw, ImVec2 min, ImVec2 max) {
		draw->AddLine(min + ImVec2(11, 17), max - ImVec2(11, 19), ImColor(255, 255, 255));
	};
	auto Rect = [](ImDrawList* draw, ImVec2 min, ImVec2 max) {
		draw->AddRect(min + ImVec2(11, 11), max - ImVec2(11, 11), ImColor(255, 255, 255), 4);
	};
	auto RectFilled = [](ImDrawList* draw, ImVec2 min, ImVec2 max) {
		draw->AddRectFilled(min + ImVec2(11, 11), max - ImVec2(11, 11), ImColor(255, 255, 255), 4);
	};
	auto Text = [](ImDrawList* draw, ImVec2 min, ImVec2 max) {
		draw->AddText(min + ImVec2(36, 36) / 2 - ImGui::CalcTextSize((const char*)ICON_FA_TEXT) / 2, ImColor(255, 255, 255), (const char*)ICON_FA_TEXT);
	};
	auto Circle = [](ImDrawList* draw, ImVec2 min, ImVec2 max) {
		draw->AddCircle(min + ImVec2(36, 36) / 2, 8, ImColor(255, 255, 255), 32);
	};
	auto CircleFilled = [](ImDrawList* draw, ImVec2 min, ImVec2 max) {
		draw->AddCircleFilled(min + ImVec2(36, 36) / 2, 8, ImColor(255, 255, 255), 32);
	};

	elements::Tool("Mouse", Mouse, gContext.SelectedEditor, 0);
	ImGui::SameLine();
	elements::Tool("Line", Line, gContext.SelectedEditor, 1);
	ImGui::SameLine();
	elements::Tool("Rect", Rect, gContext.SelectedEditor, 2);
	ImGui::SameLine();
	elements::Tool("Rect Filled", RectFilled, gContext.SelectedEditor, 3);
	ImGui::SameLine();
	elements::Tool("Text", Text, gContext.SelectedEditor, 4);
	ImGui::SameLine();
	elements::Tool("Circle", Circle, gContext.SelectedEditor, 5);
	ImGui::SameLine();
	elements::Tool("Circle Filled", CircleFilled, gContext.SelectedEditor, 6);
}