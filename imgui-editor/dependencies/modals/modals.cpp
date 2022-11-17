#include "modals.hpp"

void modalManager::Run(std::function<void()> func, ImVec2 size, std::string naming)
{
	m_bShow = true;
	m_v2Size = size;
	m_fContent = func;
	name = naming;
}

void modalManager::Instance()
{
	if (!m_bShow)
		return;

	ImGui::Begin(_S("MODAL"), 0, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
	{
		ImGui::SetWindowPos(ImVec2(0, 0));
		ImGui::SetWindowSize(ImGui::GetIO().DisplaySize);

		auto pos = ImGui::GetWindowPos();
		auto draw = ImGui::GetWindowDrawList();
		auto windowSize = ImGui::GetWindowSize();

		draw->AddRectFilled(pos, pos + windowSize, ImColor(35, 35, 35, int(210)));

		ImGui::SetCursorPos(ImVec2(windowSize / 2 - ImVec2((m_v2Size.x) / 2, (m_v2Size.y) / 2)));
		ImGui::BeginChild(_S("MODAL_CONTENT"), ImVec2(m_v2Size.x, m_v2Size.y), false, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
		{
			auto pos_internal = ImGui::GetWindowPos();
			auto draw_internal = ImGui::GetWindowDrawList();

			draw_internal->AddRectFilled(pos_internal, pos_internal + ImVec2(m_v2Size.x, m_v2Size.y), ImColor(65, 65, 65, 255), 6);
			draw_internal->AddRectFilled(pos_internal, pos_internal + ImVec2(m_v2Size.x, 30), ImColor(45, 45, 45, 255), 6, ImDrawCornerFlags_Top);
			draw_internal->AddText(pos_internal + ImVec2(10, 8), ImColor(240, 240, 240), name.c_str());

			ImGui::SetCursorPos({ 10, 40 });
			ImGui::BeginGroup();
			{
					m_fContent();
			}
			ImGui::EndGroup();

			if (!ImGui::IsMouseHoveringRect(
				pos + windowSize / 2 - m_v2Size / 2 - ImVec2(15, 15),
				pos + windowSize / 2 + m_v2Size / 2 + ImVec2(15, 15)
			) && ImGui::IsMouseClicked(0) && !ImGui::IsPopupOpen("", ImGuiPopupFlags_AnyPopupId))
				m_bShow = false;
		}
		ImGui::End();
	}
	ImGui::End();
}