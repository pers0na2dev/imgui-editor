#include "Notifies.h"
#include <mmsystem.h>

namespace notifies
{
	std::vector<notify_data_t> items;

	int in = 200;
	int out = 500;
	int duration = 3500;

	ImVec2 block_pos;
	ImVec2 debug_pos;
	ImVec2 notify_size = ImVec2(300.f, 0.f);

	const ImVec4 text_color = ImVec4(1.f, 1.f, 1.f, 1.f);
	const ImVec4 background_color = ImVec4(55 / 255.f, 55 / 255.f, 55 / 255.f, 1.f);

	const ImVec4 info = ImVec4(0.1f, 0.25f, 0.45f, 1.f);
	const ImVec4 success = ImVec4(0.1f, 0.4f, 0.2f, 1.f);
	const ImVec4 danger = ImVec4(0.45f, 0.04f, 0.15f, 1.f);
	const ImVec4 warning = ImVec4(0.85f, 0.6f, 0.05f, 1.f);

	void push(const std::string& message, notify_state_s state)
	{
		const auto end_time = (state == debug_state ? 2500 : 0) + GetTickCount64() + duration;

		items.emplace_back(notify_data_t{ message, state, end_time });
	}

	ImU32 alpha_modulate(const ImVec4& color, const float& alpha = 1.f)
	{
		return ImGui::GetColorU32(ImVec4(color.x, color.y, color.z, alpha));
	}

	void show_block(ImDrawList* draw_list, const notify_data_t& notify)
	{
		float alpha = 1.f;
		if (notify.end_time - out <= GetTickCount64())
		{
			const auto delta = std::clamp<float>(notify.end_time - GetTickCount64(), 0.f, out);
			alpha = std::clamp<float>(delta / out, 0.f, 1.f);
		}

		if (alpha == 0)
			return;

		const auto notify_end_pos = ImVec2(block_pos.x + notify_size.x, block_pos.y + notify_size.y);
		ImGui::GetForegroundDrawList()->AddRectFilled(block_pos, notify_end_pos, alpha_modulate(background_color, alpha), 2.f);

		auto color = info;
		if (notify.state == notify_state_s::danger_state)
			color = danger;
		else if (notify.state == notify_state_s::success_state)
			color = success;
		else if (notify.state == notify_state_s::warning_state)
			color = warning;

		ImGui::GetForegroundDrawList()->AddRectFilled(block_pos, ImVec2(block_pos.x, block_pos.y + notify_size.y), alpha_modulate(color, alpha), 1.f);

		const auto text_size = ImGui::CalcTextSize(notify.message.c_str());
		const auto text_pos = ImVec2(block_pos.x + 5.f + 10.f, block_pos.y + notify_size.y / 2.f - text_size.y / 2.f);

		ImGui::GetForegroundDrawList()->AddText(text_pos, alpha_modulate(text_color, alpha), text_size.x > notify_size.x + 10.f ? notify.message.substr(0, 25).c_str() : notify.message.c_str());

		block_pos.y -= notify_size.y + 10.f;
	}

	void show_text(ImDrawList* draw_list, const notify_data_t& data, const char* icon = NULL) {
		if (icon == NULL)
			draw_list->AddText(NULL, 12, debug_pos, ImColor(255, 255, 255), data.message.c_str());
		else {
			if (data.message.empty())
				return;

			draw_list->AddText(ImVec2(debug_pos.x + 20, debug_pos.y + 0), ImColor(255, 255, 255), data.message.c_str());
		}

		debug_pos.y += 14.f;
	}

	void handle(ImDrawList* draw_list)
	{
		if (items.empty())
			return;

		if (notify_size.y == 0.f)
			notify_size.y = ImGui::CalcTextSize("W").y + 14.f;

		const auto screen_size = ImGui::GetIO().DisplaySize;

		debug_pos = ImVec2(2.f, 2.f);
		block_pos = ImVec2(screen_size.x - notify_size.x - 20.f, screen_size.y - notify_size.y - 20.f);

		for (auto k = items.size(); k > 0; k--)
		{
			const auto& notify = items[k - 1];
			if (notify.end_time < GetTickCount64())
				continue;

			if (notify.state == notify_state_s::debug_state)
				show_text(draw_list, notify);
			else
				show_block(draw_list, notify);
		}
	}
}