#pragma once

#include <memory>

#include <imgui.h>
#include <imgui_internal.h>

class homepageSystem {
public:
	void Render();

	int selectedTab = 0;
};

inline auto gHomepageSystem = std::make_shared<homepageSystem>();