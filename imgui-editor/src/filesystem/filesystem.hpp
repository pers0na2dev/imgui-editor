#pragma once

#include <memory>
#include <string>
#include <vector>
#include <thread>

#include "../projects/projectSystem.hpp"
#include "../installer/installerSystem.hpp"

#include "../../defines.h"
#include "../../dependencies/security/XorStr.hpp"
#include "../../dependencies/modals/modals.hpp"
#include "../../dependencies/notifies/notifies.h"

struct projectData {
	std::string filename;
	std::string name;
	std::string data;
};

class fileSystem
{
public:
	void FetchProjects();
	void CreateProject(std::string name);
	void SaveProject();

public:
	std::string selectedProject;

	std::vector<projectData> projects;
};

inline auto gFileSystem = std::make_shared<fileSystem>();

