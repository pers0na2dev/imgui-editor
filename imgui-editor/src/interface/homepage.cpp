#include "homepage.hpp"

#include <format>

#include "elements.hpp"

#include "../filesystem/filesystem.hpp"
#include "../projects/projectSystem.hpp"

#include "../../dependencies/assets/hashes.h"
#include "../../dependencies/security/XorStr.hpp"
#include "../../dependencies/console/console.hpp"
#include "../../dependencies/modals/modals.hpp"

void homepageSystem::Render()
{
	auto flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

	ImGui::Begin(_S("Homepage"), 0, flags);
	{
		ImGui::SetWindowPos({ 55, 0 });
		ImGui::SetWindowSize({ ImGui::GetIO().DisplaySize.x - 54, ImGui::GetIO().DisplaySize.y });

		auto pos = ImGui::GetWindowPos();
		auto draw = ImGui::GetWindowDrawList();

		draw->AddRectFilled(pos, pos + ImGui::GetWindowSize(), ImColor(36, 36, 36));
		draw->AddLine(pos + ImVec2(290, 46), pos +ImVec2(ImGui::GetWindowSize().x, 46), ImColor(56, 56, 56));
		draw->AddLine(pos + ImVec2(290, 0), pos + ImVec2(290, ImGui::GetWindowSize().y), ImColor(56, 56, 56));

		ImGui::SetCursorPos(ImVec2(10, 10));
		if (elements::Widget(_S("Telegram Channel"), _S("Application development blog."), (const char*)ICON_FA_PAPER_PLANE, { 270, 50 })) 
		{
			ShellExecuteA(NULL, "open", "https://t.me/imguitech", 0, 0, SW_SHOWNORMAL);
		}


		static char search[64];
		ImGui::PushItemWidth(400);
		ImGui::SetCursorPos(ImVec2(308, 13));
		ImGui::InputTextWithHint(_S("Search"), _S("Find your project by name"), search, 64, ImGuiInputTextFlags_Invisible);

		ImGui::SetCursorPos({308, 64});
		if (elements::Widget(_S("New design file"), _S("Design and prototype"), (const char*)ICON_FA_FILE_PLUS, { 300, 50 })) {
			gModalManager->Run([]() { 
				static char name[64];

				ImGui::PushItemWidth(390);
				ImGui::InputText(_S("Project name"), name, 64);
				ImGui::Spacing();
				ImGui::PushItemWidth(196);
				ImGui::InputFloat(_S("Window Size X"), &gProjectSystem->data.window.WindowSize.x, 0, 0, "%0.f");
				ImGui::SameLine();
				ImGui::PushItemWidth(196);
				ImGui::InputFloat(_S("Window Size Y"), &gProjectSystem->data.window.WindowSize.y, 0, 0, "%0.f");
				ImGui::Spacing();
				if (ImGui::Button(_S("Create"), ImVec2(380, 35))) {
					gProjectSystem->data.layers.clear();
					ImVec2 backup = gProjectSystem->data.window.WindowSize;
					gProjectSystem->data.window = WindowStruct{};
					gProjectSystem->data.window.WindowSize = backup;
					gContext.SelectedTab = 0;
					gContext.SelectedLayer = -1;

					gFileSystem->CreateProject(name);
					gModalManager->m_bShow = false;
				}

			}, { 400, 168 }, _S("New design file"));
		}

		draw->AddLine(pos + ImVec2(290, 128), pos + ImVec2(ImGui::GetWindowSize().x, 128), ImColor(56, 56, 56));

		ImGui::SetCursorPos({ 305, 145 });
		ImGui::BeginChild(_S("Projects"), {ImGui::GetWindowSize().x - 318, ImGui::GetWindowSize().y - 170});
		{
			int counter = 0;

			for (auto project : gFileSystem->projects) 
			{
				if (project.name.find(std::string(search)))
					continue;

				counter += 1;

				if (elements::Project(project)) 
				{
					if (nlohmann::json::accept(project.data))
					{
						gHistorySystem->Clear();

						gFileSystem->selectedProject = project.filename;
						gProjectSystem->data.layers.clear();
						gProjectSystem->data.window = WindowStruct{};

						nlohmann::json j = nlohmann::json::parse(project.data);

						gProjectSystem->Action(j, false);
						gContext.SelectedTab = 0;
						gContext.SelectedLayer = -1;

						gHistorySystem->RegisterHistoryItem();
					}
				}

				if (counter * (ImGui::GetWindowSize().x - 30) / 3 > ImGui::GetWindowSize().x - (ImGui::GetWindowSize().x - 30) / 3 + 10) ImGui::Spacing(), counter = 0; 
				else ImGui::SameLine(counter * (ImGui::GetWindowSize().x) / 3);
			}

			ImGui::NewLine();
			ImGui::NewLine();
		}
		ImGui::EndChild();
	}
	ImGui::End();

	gModalManager->Instance();
}
