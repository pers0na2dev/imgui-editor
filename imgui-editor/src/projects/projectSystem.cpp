#include "projectSystem.hpp"

#include "../projects/projectSystem.hpp"

#include "dependencies/console/console.hpp"
#include "../prototypeSystem/prototypeSystem.hpp"

template <class T>
void projectSystem::JSON(nlohmann::json& j, std::string name, T& value, bool save) {
	if (save) {
		j[name] = value;
	}
	else {
		if (j[name].is_null())
			return;

		value = j[name].get<T>();
	}
}

void projectSystem::JSON(nlohmann::json& j, std::string name, std::string& value, bool save) {
	if (save) {
		j[name] = value;
	}
	else {
		if (j[name].is_null())
			return;

		value = j[name].get<std::string>();
	}
}

void projectSystem::JSON(nlohmann::json& j, std::string name, ImVec2& value, bool save) {
	if (save) {
		j[name][0] = value.x;
		j[name][1] = value.y;
	}
	else {
		if (j[name].is_null())
			return;

		value.x = j[name][0].get<float>();
		value.y = j[name][1].get<float>();
	}
}

void projectSystem::JSON(nlohmann::json& j, std::string name, ImColor& value, bool save) {
	if (save) {
		j[name][0] = value.Value.x;
		j[name][1] = value.Value.y;
		j[name][2] = value.Value.z;
		j[name][3] = value.Value.w;
	}
	else {
		if (j[name].is_null())
			return;

		value.Value.x = j[name][0].get<float>();
		value.Value.y = j[name][1].get<float>();
		value.Value.z = j[name][2].get<float>();
		value.Value.w = j[name][3].get<float>();
	}
}

std::string escaped(const std::string& input)
{
	std::string output;
	output.reserve(input.size());
	for (const char c : input) {
		switch (c) {
		case '\a':  output += "\\a";        break;
		case '\b':  output += "\\b";        break;
		case '\f':  output += "\\f";        break;
		case '\n':  output += "\\n";        break;
		case '\r':  output += "\\r";        break;
		case '\t':  output += "\\t";        break;
		case '\v':  output += "\\v";        break;
		default:    output += c;            break;
		}
	}

	return output;
}

void projectSystem::JSONLayer(nlohmann::json& json, std::vector<layerStruct>& layer, bool save)
{
	if (save) 
	{
		for (auto a = 0; a < layer.size(); a++)
		{
			JSON(json[a], "Target", layer[a].target, save);
			JSON(json[a], "Type", layer[a].type, save);
			JSON(json[a], "Pos", layer[a].pos, save);
			JSON(json[a], "Size", layer[a].size, save);
			JSON(json[a], "Color", layer[a].color, save);
			JSON(json[a], "Thickness", layer[a].thickness, save);
			JSON(json[a], "Rounding", layer[a].rounding, save);
			JSON(json[a], "Radius", layer[a].radius, save);
			JSON(json[a], "RoundFlags", layer[a].roundFlags, save);
			JSON(json[a], "TextValue", layer[a].textValue, save);
			JSON(json[a], "FontName", layer[a].fontName, save);
			JSON(json[a], "FontFile", layer[a].fontFile, save);
			JSON(json[a], "FontSize", layer[a].fontSize, save);
			JSON(json[a], "TextAlignX", layer[a].textAlignX, save);
			JSON(json[a], "TextAlignY", layer[a].textAlignY, save);
			JSON(json[a], "TextSize", layer[a].textSize, save);
			JSON(json[a], "ImagePath", layer[a].imagePath, save);
			JSON(json[a], "ImageName", layer[a].imageName, save);

			JSON(json[a], "_locked", layer[a]._locked, save);
			JSON(json[a], "_show", layer[a]._show, save);
		}
	}
	else {
		if (json.is_null())
			return;

		for (auto a = 0; a < json.size(); a++)
		{
			layerStruct layerStr = layerStruct{};

			layerStr._shouldRebuild = true;

			if(!json[a]["_locked"].is_null())
				layerStr._locked = json[a]["_locked"].get<bool>();

			if (!json[a]["_show"].is_null())
				layerStr._show = json[a]["_show"].get<bool>();

			if (!json[a]["Radius"].is_null())
				layerStr.radius = json[a]["Radius"].get<float>();

			if (!json[a]["Target"].is_null())
				layerStr.target = json[a]["Target"].get<drawTarget>();

			if (!json[a]["Type"].is_null())
				layerStr.type = json[a]["Type"].get<drawType>();

			if (!json[a]["Pos"].is_null())
				layerStr.pos.x = json[a]["Pos"][0].get<float>(),
				layerStr.pos.y = json[a]["Pos"][1].get<float>();

			if (!json[a]["Size"].is_null())
				layerStr.size.x = json[a]["Size"][0].get<float>(),
				layerStr.size.y = json[a]["Size"][1].get<float>();

			if (!json[a]["Color"].is_null())
				layerStr.color.Value.x = json[a]["Color"][0].get<float>(),
				layerStr.color.Value.y = json[a]["Color"][1].get<float>(),
				layerStr.color.Value.z = json[a]["Color"][2].get<float>(),
				layerStr.color.Value.w = json[a]["Color"][3].get<float>();

			if (!json[a]["Thickness"].is_null())
				layerStr.thickness = json[a]["Thickness"].get<float>();

			if (!json[a]["Rounding"].is_null())
				layerStr.rounding = json[a]["Rounding"].get<float>();

			if (!json[a]["RoundFlags"].is_null())
				layerStr.roundFlags = json[a]["RoundFlags"].get<ImDrawCornerFlags>();

			if (!json[a]["TextValue"].is_null())
				layerStr.textValue = json[a]["TextValue"].get<std::string>();

			if (!json[a]["FontName"].is_null())
				layerStr.fontName = json[a]["FontName"].get<std::string>();

			if (!json[a]["FontFile"].is_null())
				layerStr.fontFile = json[a]["FontFile"].get<std::string>();

			if (!json[a]["FontSize"].is_null())
				layerStr.fontSize = json[a]["FontSize"].get<float>();

			if (!json[a]["TextAlignX"].is_null())
				layerStr.textAlignX = json[a]["TextAlignX"].get<int>();

			if (!json[a]["TextAlignY"].is_null())
				layerStr.textAlignY = json[a]["TextAlignY"].get<int>();

			if (!json[a]["TextSize"].is_null())
				layerStr.textSize[0] = json[a]["TextSize"][0].get<float>(),
				layerStr.textSize[1] = json[a]["TextSize"][1].get<float>();

			if (!json[a]["ImagePath"].is_null())
				layerStr.imagePath = escaped(json[a]["ImagePath"].get<std::string>());

			if (!json[a]["ImageName"].is_null())
				layerStr.imageName = json[a]["ImageName"].get<std::string>();

			layer.push_back(layerStr);

		}
	}
}

void Prototyping(nlohmann::json& input, std::vector<widgetPrototype>& prototypes, bool save)
{
	if (save)
	{
		for (auto id = 0; id < prototypes.size(); id++)
		{
			gProjectSystem->JSON(input[id], "Type", prototypes[id].type, save);
			gProjectSystem->JSON(input[id], "Name", prototypes[id].name, save);
			gProjectSystem->JSON(input[id], "CursorPos", prototypes[id].cursorPos, save);
			gProjectSystem->JSON(input[id], "Width", prototypes[id].fWidth, save);
			gProjectSystem->JSON(input[id], "BtnSize", prototypes[id].btnSize, save);
			gProjectSystem->JSON(input[id], "ChildSize", prototypes[id].childSize, save);

			if (prototypes[id].type == elementType::CHILD || prototypes[id].type == elementType::GROUP) {
				Prototyping(input[id]["Items"], prototypes[id].items, save);
			}
		}
	}
	else {
		if (input.is_null())
			return;

		for (auto a = 0; a < input.size(); a++)
		{
			widgetPrototype proto = widgetPrototype{};

			if (!input[a]["Type"].is_null()) proto.type = input[a]["Type"].get<elementType>();
			if (!input[a]["Name"].is_null()) proto.name = input[a]["Name"].get<std::string>();
			if (!input[a]["CursorPos"].is_null()) {
				proto.cursorPos[0] = input[a]["CursorPos"][0] .get<float>();
				proto.cursorPos[1] = input[a]["CursorPos"][1].get<float>();
			}
			if (!input[a]["Width"].is_null()) proto.fWidth = input[a]["Width"].get<float>();
			if (!input[a]["BtnSize"].is_null()) {
				proto.btnSize[0] = input[a]["BtnSize"][0].get<float>();
				proto.btnSize[1] = input[a]["BtnSize"][1].get<float>();
			}
			if (!input[a]["ChildSize"].is_null()) {
				proto.childSize[0] = input[a]["ChildSize"][0].get<float>();
				proto.childSize[1] = input[a]["ChildSize"][1].get<float>();
			}

			if (proto.type == elementType::CHILD || proto.type == elementType::GROUP) {
				Prototyping(input[a]["Items"], proto.items, save);
			}

			prototypes.push_back(proto);
		}
	}
}

void projectSystem::Action(nlohmann::json& input, bool save)
{
	if (!save) gProjectSystem->data.layers.clear();

	JSON(input["Window"], "Alpha", data.window.Alpha, save);
	JSON(input["Window"], "DisabledAlpha", data.window.DisabledAlpha, save);
	JSON(input["Window"], "WindowRounding", data.window.WindowRounding, save);
	JSON(input["Window"], "WindowBorderSize", data.window.WindowBorderSize, save);
	JSON(input["Window"], "ChildRounding", data.window.ChildRounding, save);
	JSON(input["Window"], "ChildBorderSize", data.window.ChildBorderSize, save);
	JSON(input["Window"], "PopupRounding", data.window.PopupRounding, save);
	JSON(input["Window"], "PopupBorderSize", data.window.PopupBorderSize, save);
	JSON(input["Window"], "FrameRounding", data.window.FrameRounding, save);
	JSON(input["Window"], "FrameBorderSize", data.window.FrameBorderSize, save);
	JSON(input["Window"], "IndentSpacing", data.window.IndentSpacing, save);
	JSON(input["Window"], "WindowMinSize", data.window.WindowMinSize, save);
	JSON(input["Window"], "WindowPadding", data.window.WindowPadding, save);
	JSON(input["Window"], "WindowSize", data.window.WindowSize, save);
	JSON(input["Window"], "WindowTitleAlign", data.window.WindowTitleAlign, save);
	JSON(input["Window"], "ItemSpacing", data.window.ItemSpacing, save);
	JSON(input["Window"], "ItemInnerSpacing", data.window.ItemInnerSpacing, save);
	JSON(input["Window"], "FramePadding", data.window.FramePadding, save);
	JSON(input["Window"], "Size", data.window.WindowSize, save);

	JSON(input["Checkbox"], "FramePos", data.checkbox.FramePos, save);
	JSON(input["Checkbox"], "FrameSize", data.checkbox.FrameSize, save);
	JSON(input["Checkbox"], "TotalSize", data.checkbox.TotalSize, save);

	JSONLayer(input["Layers"], data.layers, save);

	Prototyping(input["Prototyping"], gPrototypeSystem->prototypes, save);
}

void projectSystem::ActionTransform(nlohmann::json& input, currentProjectData& data)
{
	JSON(input["Window"], "Alpha", data.window.Alpha, false);
	JSON(input["Window"], "DisabledAlpha", data.window.DisabledAlpha, false);
	JSON(input["Window"], "WindowRounding", data.window.WindowRounding, false);
	JSON(input["Window"], "WindowBorderSize", data.window.WindowBorderSize, false);
	JSON(input["Window"], "ChildRounding", data.window.ChildRounding, false);
	JSON(input["Window"], "ChildBorderSize", data.window.ChildBorderSize, false);
	JSON(input["Window"], "PopupRounding", data.window.PopupRounding, false);
	JSON(input["Window"], "PopupBorderSize", data.window.PopupBorderSize, false);
	JSON(input["Window"], "FrameRounding", data.window.FrameRounding, false);
	JSON(input["Window"], "FrameBorderSize", data.window.FrameBorderSize, false);
	JSON(input["Window"], "IndentSpacing", data.window.IndentSpacing, false);
	JSON(input["Window"], "WindowMinSize", data.window.WindowMinSize, false);
	JSON(input["Window"], "WindowPadding", data.window.WindowPadding, false);
	JSON(input["Window"], "WindowSize", data.window.WindowSize, false);
	JSON(input["Window"], "WindowTitleAlign", data.window.WindowTitleAlign, false);
	JSON(input["Window"], "ItemSpacing", data.window.ItemSpacing, false);
	JSON(input["Window"], "ItemInnerSpacing", data.window.ItemInnerSpacing, false);
	JSON(input["Window"], "FramePadding", data.window.FramePadding, false);
	JSON(input["Window"], "Size", data.window.WindowSize, false);

	JSONLayer(input["Layers"], data.layers, false);
}