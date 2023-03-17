#pragma once

#include <memory>

#include <imgui.h>
#include <imgui_internal.h>

#include "context.hpp"

class WindowSettings
{
public:
	void Render();
	void Infobar();
	void Sidebar();
	void Mainbar();
};

inline auto windowSettings = std::make_shared<WindowSettings>();

