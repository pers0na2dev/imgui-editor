#include "layerSystem.hpp"

#include "imgui/imgui_impl_dx9.h"
#include "utils/utils.hpp"

void layerSystem::RegisterImage(std::string path) {
    layerStruct baseData;
    baseData.target = drawTarget::Window;
    baseData.type = drawType::Image;
    baseData.imagePath = path;
	baseData.imageName = std::filesystem::path(path).filename().string();

	gProjectSystem->data.layers.emplace_back(baseData);
}

void layerSystem::RegisterItem(layerStruct data)
{
    data.name = utils::genName(12);
	gProjectSystem->data.layers.emplace_back(data);
}

void layerSystem::Rebuild(LPDIRECT3DDEVICE9 device) {
	for (auto a = 0; a < gProjectSystem->data.layers.size(); a++) {
		if (gProjectSystem->data.layers[a].type == drawType::Image) {
			if (gProjectSystem->data.layers[a].texture == nullptr) {
				D3DXCreateTextureFromFileA(device, gProjectSystem->data.layers[a].imagePath.c_str(), &gProjectSystem->data.layers[a].texture);
				int x, y;
				utils::GetImageSizeEx(gProjectSystem->data.layers[a].imagePath.c_str(), &x, &y);
				gProjectSystem->data.layers[a].size = { (float)x, (float)y };
			}
		}

		if (gProjectSystem->data.layers[a].type == drawType::Text)
		{
			if (gProjectSystem->data.layers[a]._shouldRebuild) {
				ImFontConfig cfg;
				cfg.FontDataOwnedByAtlas = false;
				cfg.RasterizerMultiply = 1;
				cfg.OversampleH = cfg.OversampleV = 1;

				gProjectSystem->data.layers[a].font = ImGui::GetIO().Fonts->AddFontFromFileTTF(
					std::string("C:\\Windows\\Fonts\\" + gProjectSystem->data.layers[a].fontFile).c_str(),
					gProjectSystem->data.layers[a].fontSize,
					&cfg,
					ImGui::GetIO().Fonts->GetGlyphRangesDefault()
				);

				gProjectSystem->data.layers[a]._shouldRebuild = false;

				ImGui_ImplDX9_DestroyFontsTexture();
				ImGui::GetIO().Fonts->Build();
			}
		}
	}

	if (gProjectSystem->data.checkbox._shouldRebuild) {
		ImFontConfig cfg;
		cfg.FontDataOwnedByAtlas = false;
		cfg.RasterizerMultiply = 1;
		cfg.OversampleH = cfg.OversampleV = 1;

		gProjectSystem->data.checkbox.Font = ImGui::GetIO().Fonts->AddFontFromFileTTF(
			std::string("C:\\Windows\\Fonts\\" + gProjectSystem->data.checkbox.FontFile).c_str(),
			gProjectSystem->data.checkbox.FontSize, &cfg, ImGui::GetIO().Fonts->GetGlyphRangesDefault()
		);

		ImGui_ImplDX9_DestroyFontsTexture();
		ImGui::GetIO().Fonts->Build();

		gProjectSystem->data.checkbox._shouldRebuild = false;
	}
}

void layerStruct::Render(ImDrawList* draw, float scale, int id)
{
	if (!_show)
		return;

	auto winPos = ImGui::GetWindowPos();

	if (type == drawType::Line) {
		if (_hovered)
			ImGui::GetForegroundDrawList()->AddLine(winPos + pos * scale, winPos + (pos + size) * scale, ImColor(0, 166, 255), 3 * scale);

		draw->AddLine(winPos + pos * scale, winPos + (pos + size) * scale, color, thickness * scale);
		SwapSelection(winPos + pos * scale, winPos + (pos + size) * scale, id);
	}

	if (type == drawType::Rectangle) {
		if (_hovered) {
			ImGui::GetForegroundDrawList()->AddRect(winPos + pos * scale - ImVec2(1, 1), winPos + (pos + size) * scale + ImVec2(1, 1), ImColor(0, 166, 255));
		}

		draw->AddRect(winPos + pos * scale, winPos + (pos + size) * scale, color, rounding * scale, roundFlags, thickness * scale);
		SwapSelection(winPos + pos * scale, winPos + (pos + size) * scale, id);
	}

	if (type == drawType::RectangleFilled)
	{
		if (_hovered) {
			ImGui::GetForegroundDrawList()->AddRect(winPos + pos * scale - ImVec2(1, 1), winPos + (pos + size) * scale + ImVec2(1, 1), ImColor(0, 166, 255));
		}

		draw->AddRectFilled(winPos + pos * scale, winPos + (pos + size) * scale, color, rounding * scale, roundFlags);
		SwapSelection(winPos + pos * scale, winPos + (pos + size) * scale, id);
	}

	if (type == drawType::Circle)
	{
		if (_hovered) {
			ImGui::GetForegroundDrawList()->AddRect(winPos + pos * scale - ImVec2(1, 1), winPos + (pos + size) * scale + ImVec2(1, 1), ImColor(0, 166, 255));
		}

		if (size.x < size.y) radius = size.x / 2;
		else radius = size.y / 2;

		draw->AddCircle(winPos + pos * scale + (size * scale) / 2, radius * scale, color, rounding * scale, thickness * scale);
		SwapSelection(winPos + pos * scale, winPos + (pos + size) * scale, id);
	}

	if (type == drawType::CircleFilled)
	{
		if (_hovered) {
			ImGui::GetForegroundDrawList()->AddRect(winPos + pos * scale - ImVec2(1, 1), winPos + (pos + size) * scale + ImVec2(1, 1), ImColor(0, 166, 255));
		}

		if (size.x < size.y) radius = size.x / 2;
		else radius = size.y / 2;

		draw->AddCircleFilled(winPos + pos * scale + (size * scale) / 2, radius * scale, color, rounding * scale);
		SwapSelection(winPos + pos * scale, winPos + (pos + size) * scale, id);
	}

	if (type == drawType::Text)
	{
		if (_hovered) {
			ImGui::GetForegroundDrawList()->AddRect(winPos + pos * scale - ImVec2(1, 1), winPos + (pos + size) * scale + ImVec2(1, 1), ImColor(0, 166, 255));
		}

		if (font != nullptr)
		{
			float xAppend = 0;
			float yAppend = 0;

			if (textAlignX == 0)
				xAppend = 0;
			else if (textAlignX == 1)
				xAppend = size.x / 2 - textSize.x / 2;
			else if (textAlignX == 2)
				xAppend = size.x - textSize.x;

			if (textAlignY == 0)
				yAppend = 0;
			else if (textAlignY == 1)
				yAppend = size.y / 2 - textSize.y / 2;
			else if (textAlignY == 2)
				yAppend = size.y - textSize.y;

			if (font != nullptr)
				draw->AddText(
					font, fontSize * scale,
					winPos + pos * scale + ImVec2(xAppend, yAppend) * scale,
					color, textValue.c_str(), 0, size.x * scale
				);

			SwapSelection(winPos + pos * scale, winPos + (pos + size) * scale, id);
		}
	}

	if (type == drawType::Image)
	{
		if (_hovered) {
			ImGui::GetForegroundDrawList()->AddRect(winPos + pos * scale - ImVec2(1, 1), winPos + (pos + size) * scale + ImVec2(1, 1), ImColor(0, 166, 255));
		}

		if (texture != nullptr)
			draw->AddImage(texture, winPos + pos * scale, winPos + (pos + size) * scale);

		SwapSelection(winPos + pos * scale, winPos + (pos + size) * scale, id);
	}
}