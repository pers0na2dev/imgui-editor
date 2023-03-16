#pragma once

#include <memory>
#include <filesystem>
#include <windows.h>

#include "defines.h"
#include "dependencies/console/console.hpp"
#include <imgui.h>

#include "../filesystem/filesystem.hpp"

class installerSystem {
public:
	void SetStyles();
	void GenerateDirectories();
};

inline auto gInstallerSystem = std::make_shared<installerSystem>();