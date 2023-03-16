#pragma once

#include <memory>

#include "dependencies/imgui/imgui.h"
#include "dependencies/imgui/imgui_internal.h"

#include "../../context.hpp"

class CheckboxSettings
{
public:
	void Render();
	void Infobar();
	void Sidebar();
	void Mainbar();
};

inline auto checkboxSettings = std::make_shared<CheckboxSettings>();

