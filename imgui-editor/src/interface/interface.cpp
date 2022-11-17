#include "interface.hpp"

#include <format>

#include "elements.hpp"

#include "../workspace/windowSettings.hpp"
#include "../workspace/widgets/checkboxSettings.hpp"
#include "../workspace/prototypeMananger.hpp"

#include "../layerSystem/layerSystem.hpp"
#include "../projects/projectSystem.hpp"

#include "../../dependencies/assets/hashes.h"
#include "../../dependencies/security/XorStr.hpp"
#include "../../dependencies/console/console.hpp"
#include "../filesystem/filesystem.hpp"
#include "homepage.hpp"

void interfaceSystem::Navigation()
{
	auto flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

	ImGui::Begin(_S("Navigation"), 0, flags);
	{
		ImGui::SetWindowPos({ 0, 0 });
		ImGui::SetWindowSize({ 55, ImGui::GetIO().DisplaySize.y });

		auto pos = ImGui::GetWindowPos();
		auto draw = ImGui::GetWindowDrawList();

		draw->AddRectFilled(pos, pos + ImGui::GetWindowSize(), ImColor(85, 85, 90));

		ImGui::SetCursorPos({8, 8});
		ImGui::BeginGroup(); 
		{
			elements::Tab("Homepage", (const char*)ICON_FA_COMPRESS_ALT, gContext.SelectedTab, -1);
			if (ImGui::IsItemClicked()) 
			{
				if (gFileSystem->selectedProject != _S(""))
					gFileSystem->SaveProject();
			}

			if (gFileSystem->selectedProject != "")
			{
				elements::Tab("Edit", (const char*)ICON_FA_BORDER_ALL, gContext.SelectedTab, 0);
				elements::Tab("Window Settings", (const char*)ICON_FA_WINDOW, gContext.SelectedTab, 1);
				elements::Tab("Prototype System", (const char*)ICON_FA_CONTAINER_STORAGE, gContext.SelectedTab, 3);

				if (ImGui::IsItemClicked(0)) {
					gContext.SelectedLayer = -1;
				}
			}
		}
		ImGui::EndGroup();
	}
	ImGui::End();
}

void interfaceSystem::Infobar()
{
	auto flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

	ImGui::Begin(_S("Infobar"), 0, flags);
	{
		ImGui::SetWindowPos({ 55, 0 });
		ImGui::SetWindowSize({ ImGui::GetIO().DisplaySize.x - 55, 46});

		auto pos = ImGui::GetWindowPos();
		auto draw = ImGui::GetWindowDrawList();

		draw->AddRectFilled(pos, pos + ImGui::GetWindowSize(), ImColor(36, 36, 36));
		draw->AddLine(pos + ImVec2(0, 45), pos + ImVec2(ImGui::GetIO().DisplaySize.x, 45), ImColor(46, 46, 46));

		windowSettings->Infobar();
		checkboxSettings->Infobar();
		prototypeManager->Infobar();
	}
	ImGui::End();
}

void interfaceSystem::Mainbar()
{
	auto flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

	ImGui::Begin(_S("Tools"), 0, flags);
	{
		ImGui::SetWindowPos({ 55, 46 });
		ImGui::SetWindowSize({ 290, ImGui::GetIO().DisplaySize.y - 35 });

		auto pos = ImGui::GetWindowPos();
		auto draw = ImGui::GetWindowDrawList();

		draw->AddRectFilled(pos, pos + ImGui::GetWindowSize(), ImColor(36, 36, 36));

		ImGui::SetCursorPos({ 0, 0 });
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0, 0});
		ImGui::BeginChild(_S("ToolbarChild"), { 290, ImGui::GetIO().DisplaySize.y - 35 });
		{
			windowSettings->Mainbar();
			checkboxSettings->Mainbar();
			prototypeManager->Mainbar();

			if (gContext.SelectedTab != 0 && gContext.SelectedTab != 3) {
				auto alphaTop = elements::anim.Value("alphaTop", (ImGui::GetScrollY() / ImGui::GetScrollMaxY()) < 0.9, 0.f, 1.f, 0.05f);
				auto alphaBot = elements::anim.Value("alphaBot", (ImGui::GetScrollY() / ImGui::GetScrollMaxY()) > 0.1, 0.f, 1.f, 0.05f);

				ImGui::GetForegroundDrawList()->AddRectFilledMultiColor(pos + ImVec2(0, ImGui::GetWindowSize().y - 60), pos + ImVec2(290, ImGui::GetWindowSize().y),
					ImColor(25, 25, 25, 0), ImColor(25, 25, 25, 0), ImColor(25, 25, 25, int(alphaTop * 255)), ImColor(25, 25, 25, int(alphaTop * 255)));

				ImGui::GetForegroundDrawList()->AddRectFilledMultiColor(pos, pos + ImVec2(290, 60),
					ImColor(25, 25, 25, int(alphaBot * 255)), ImColor(25, 25, 25, int(alphaBot * 255)), ImColor(25, 25, 25, 0), ImColor(25, 25, 25, 0));
			}
		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}
	ImGui::End();
}

void interfaceSystem::Sidebar()
{
	if (!gContext.RenderSidebar)
		return;

	auto flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

	ImGui::Begin(_S("Edit Layer"), 0, flags);
	{
		ImGui::SetWindowPos({ ImGui::GetIO().DisplaySize.x - 260, 46 });
		ImGui::SetWindowSize({ 260, ImGui::GetIO().DisplaySize.y - 46 });

		auto pos = ImGui::GetWindowPos();
		auto draw = ImGui::GetWindowDrawList();

		draw->AddRectFilled(pos, pos + ImGui::GetWindowSize(), ImColor(36, 36, 36));

		ImGui::SetCursorPos({ 0, 0 });
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
		ImGui::BeginChild(_S("ToolbarChild"), { 260, ImGui::GetIO().DisplaySize.y - 46 });
		{
			windowSettings->Sidebar();
			checkboxSettings->Sidebar();
			prototypeManager->Sidebar();
		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}
	ImGui::End();
}

void interfaceSystem::Render()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 4);
	{
		Navigation();

		if (gContext.SelectedTab != -1)
		{
			Mainbar();
			Sidebar();
			Infobar();

			windowSettings->Render();
			checkboxSettings->Render();
			prototypeManager->Render();
		}
		else {
			gHomepageSystem->Render();
		}
	}
	ImGui::PopStyleVar(4);
}
