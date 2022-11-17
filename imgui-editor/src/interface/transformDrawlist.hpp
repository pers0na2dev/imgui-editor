#pragma once

#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_internal.h"

#include "../projects/projectSystem.hpp"
#include "../filesystem/filesystem.hpp"

namespace transformDrawlist {
	inline currentProjectData parse(projectData project) {
		currentProjectData data = currentProjectData{};

		if (nlohmann::json::accept(project.data))
		{
			nlohmann::json j = nlohmann::json::parse(project.data);
			gProjectSystem->ActionTransform(j, data);
		}

		return data;
	}

	inline void render(ImDrawList* draw, ImVec2 start, currentProjectData data, ImVec2 windowSize) 
	{
		float ratio = min(windowSize.x / data.window.WindowSize.x, windowSize.y / data.window.WindowSize.y);
		start = start - (data.window.WindowSize * ratio) / 2;

		draw->AddRectFilled(start, start + data.window.WindowSize * ratio, ImColor(16, 16, 16), data.window.WindowRounding * ratio);

		draw->PushClipRect(start, start + data.window.WindowSize * ratio, true);
		for (auto& layer : data.layers) 
		{
			if (layer.type == drawType::Line) {
				draw->AddLine(start + layer.pos * ratio, start + layer.pos * ratio + layer.size * ratio, layer.color, layer.thickness * ratio);
			}

			if (layer.type == drawType::Rectangle) {
				draw->AddRect(start + layer.pos * ratio, start + layer.pos * ratio + layer.size * ratio, layer.color, layer.rounding * ratio, layer.roundFlags, layer.thickness * ratio);
			}

			if (layer.type == drawType::RectangleFilled){
				draw->AddRectFilled(start + layer.pos * ratio, start + layer.pos * ratio + layer.size * ratio, layer.color, layer.rounding * ratio, layer.roundFlags);
			}

			if (layer.type == drawType::Circle)
			{
				if (layer.size.x < layer.size.y) layer.radius = layer.size.x / 2;
				else layer.radius = layer.size.y / 2;

				draw->AddCircle(start + layer.pos * ratio + (layer.size * ratio) / 2, layer.radius * ratio, layer.color, layer.rounding * ratio, layer.thickness * ratio);
			}

			if (layer.type == drawType::CircleFilled)
			{
				if (layer.size.x < layer.size.y) layer.radius = layer.size.x / 2;
				else layer.radius = layer.size.y / 2;

				draw->AddCircleFilled(start + layer.pos * ratio + (layer.size * ratio) / 2, layer.radius * ratio, layer.color, layer.rounding * ratio);
			}

			if (layer.type == drawType::Text)
			{
					float xAppend = 0;
					float yAppend = 0;

					if (layer.textAlignX == 0)
						xAppend = 0;
					else if (layer.textAlignX == 1)
						xAppend = layer.size.x / 2 - layer.textSize.x / 2;
					else if (layer.textAlignX == 2)
						xAppend = layer.size.x - layer.textSize.x;

					if (layer.textAlignY == 0)
						yAppend = 0;
					else if (layer.textAlignY == 1)
						yAppend = layer.size.y / 2 - layer.textSize.y / 2;
					else if (layer.textAlignY == 2)
						yAppend = layer.size.y - layer.textSize.y;

					draw->AddText(
							NULL, layer.fontSize * ratio,
							start + layer.pos * ratio + ImVec2(xAppend, yAppend) * ratio,
							layer.color, layer.textValue.c_str(), 0, layer.size.x * ratio
					);
			}
		}
		draw->PopClipRect();
	}
}
