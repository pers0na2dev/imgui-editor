#pragma once

#include <memory>

#include <imgui.h>
#include <imgui_internal.h>

#include <string>
#include <functional>

#include "imgui/imgui_tweaker.hpp"

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
