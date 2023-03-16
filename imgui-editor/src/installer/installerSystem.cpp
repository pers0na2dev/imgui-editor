#include "installerSystem.hpp"

#include "../../dependencies/assets/faprolight.hpp"
#include "../../dependencies/assets/hashes.h"
#include "../../dependencies/assets/SFUIDisplay.hpp"

void installerSystem::SetStyles()
{
	static const ImWchar ranges[] = {
		0x0020, 0x00FF,0x2000, 0x206F, 0x3000,
		0x30FF,0x31F0, 0x31FF,0xFF00, 0xFFEF,0x4e00, 0x9FAF,0x0400,
		0x052F,0x2DE0, 0x2DFF,0xA640, 0xA69F, 0
	};

	ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF((void*)sfpro_compressed_data, sfpro_compressed_size, 14, nullptr, ranges);

	static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;

	ImGui::GetIO().Fonts->AddFontFromMemoryTTF(faprolight, sizeof faprolight, 14, &icons_config, icon_ranges);

	ImGui::GetStyle().Alpha = 1.f;
	ImGui::GetStyle().AntiAliasedFill = 1.f;
	ImGui::GetStyle().AntiAliasedLines = 1.f;
	ImGui::GetStyle().AntiAliasedLinesUseTex = 1.f;
	ImGui::GetStyle().Alpha = 1.f;
	ImGui::GetStyle().Colors[ImGuiCol_PopupBg] = ImColor(30, 30, 30);
	ImGui::GetStyle().Colors[ImGuiCol_Border] = ImColor(55, 55, 55);

	ImGui::GetIO().IniFilename = "";
}

void installerSystem::GenerateDirectories()
{
	auto path = std::filesystem::path("C:/imgui.tech");

	if (!std::filesystem::exists(path))
		std::filesystem::create_directories(path);
}
