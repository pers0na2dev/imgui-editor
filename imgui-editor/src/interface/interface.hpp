#pragma once

#include <memory>

#include <imgui.h>
#include <imgui_internal.h>

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