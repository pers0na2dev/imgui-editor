#pragma once

#include <memory>

#include <imgui.h>
#include <imgui_internal.h>

#include "context.hpp"
#include "prototypeSystem/prototypeSystem.hpp"

class PrototypeManager
{
public:
	void Render();
	void Infobar();
	void Sidebar();
	void Mainbar();

	widgetPrototype* currentEditor;
};

inline auto prototypeManager = std::make_shared<PrototypeManager>();

