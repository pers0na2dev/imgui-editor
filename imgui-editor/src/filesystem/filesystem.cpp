#include "filesystem.hpp"

#include "../../dependencies/console/console.hpp"
#include "../context.hpp"

#include <fstream>

void fileSystem::FetchProjects()
{
	std::thread([&]() {
		gContext.isCloudAction = true;

		for (auto& p : std::filesystem::recursive_directory_iterator("C:\\imgui.tech")) {
			std::ifstream stream(p.path().string().c_str(), std::ios::binary);
			nlohmann::json jf = nlohmann::json::parse(stream);

			projects.push_back(projectData{
				.filename = p.path().string(),
				.name = jf["Name"].get<std::string>(),
				.data = jf["Data"].dump(),
				});

			std::this_thread::sleep_for(std::chrono::milliseconds(10));

			conManager->print("FetchProject::DirList - %s", p.path().string().c_str());
		}

		gContext.isCloudAction = false;
	}).detach();
}

void fileSystem::CreateProject(std::string name)
{
	gContext.isCloudAction = true;

	nlohmann::json jf;
	jf["Name"] = name;

	gProjectSystem->Action(jf["Data"], true);

	std::ofstream project;
	project.open("C:\\imgui.tech\\" + name + ".json");
	project << jf.dump().c_str();
	project.close();

	gContext.isCloudAction = false;

	projects.clear();
	FetchProjects();
}

void fileSystem::SaveProject()
{
	std::thread([&]() {
		gContext.isCloudAction = true;

		nlohmann::json jf;
		jf["Name"] = gFileSystem->selectedProject;

		gProjectSystem->Action(jf["Data"], true);

		std::ofstream project;
		project.open(gFileSystem->selectedProject);
		project << jf.dump().c_str();
		project.close();

		gContext.isCloudAction = false;
	}).detach();
}