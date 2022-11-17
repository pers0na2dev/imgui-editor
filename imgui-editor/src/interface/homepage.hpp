#pragma once

#include <memory>

#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_internal.h"

class homepageSystem {
public:
	void Render();

	int selectedTab = 0;
};

inline auto gHomepageSystem = std::make_shared<homepageSystem>();