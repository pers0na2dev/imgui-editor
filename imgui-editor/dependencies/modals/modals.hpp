#pragma once

#include <memory>

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "../imgui/imgui_tweaker.hpp"
#include "../security/XorStr.hpp"

#include <functional>

class modalManager {
public:
	void Instance();
	void Run(std::function<void()> func, ImVec2 size, std::string naming);

	bool m_bShow = false;
	std::string name = "";

private:
	ImAnimations::Animator<const char*, float> m_animator;

	ImVec2 m_v2Size;
	std::function<void()> m_fContent;
};

inline auto gModalManager = std::make_shared<modalManager>();