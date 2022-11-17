#pragma once

#include <memory>

#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_internal.h"

class interfaceSystem {
public:
	void Render();

private:
	void Mainbar();
	void Sidebar();
	void Navigation();
	void Infobar();
};

inline auto gInterfaceSystem = std::make_shared<interfaceSystem>();