#pragma once

#include <memory>

#include <imgui.h>
#include <imgui_internal.h>

#include "context.hpp"

class CheckboxSettings
{
public:
	void Render();
	void Infobar();
	void Sidebar();
	void Mainbar();
};

inline auto checkboxSettings = std::make_shared<CheckboxSettings>();

