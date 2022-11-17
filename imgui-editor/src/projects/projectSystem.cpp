#include "projectSystem.hpp"

#include "../projects/projectSystem.hpp"

#include "../../dependencies/console/console.hpp"
#include "../../dependencies/security/XorStr.hpp"
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
			JSON(json[a], _S("Target"), layer[a].target, save);
			JSON(json[a], _S("Type"), layer[a].type, save);
			JSON(json[a], _S("Pos"), layer[a].pos, save);
			JSON(json[a], _S("Size"), layer[a].size, save);
			JSON(json[a], _S("Color"), layer[a].color, save);
			JSON(json[a], _S("Thickness"), layer[a].thickness, save);
			JSON(json[a], _S("Rounding"), layer[a].rounding, save);
			JSON(json[a], _S("Radius"), layer[a].radius, save);
			JSON(json[a], _S("RoundFlags"), layer[a].roundFlags, save);
			JSON(json[a], _S("TextValue"), layer[a].textValue, save);
			JSON(json[a], _S("FontName"), layer[a].fontName, save);
			JSON(json[a], _S("FontFile"), layer[a].fontFile, save);
			JSON(json[a], _S("FontSize"), layer[a].fontSize, save);
			JSON(json[a], _S("TextAlignX"), layer[a].textAlignX, save);
			JSON(json[a], _S("TextAlignY"), layer[a].textAlignY, save);
			JSON(json[a], _S("TextSize"), layer[a].textSize, save);
			JSON(json[a], _S("ImagePath"), layer[a].imagePath, save);
			JSON(json[a], _S("ImageName"), layer[a].imageName, save);

			JSON(json[a], _S("_locked"), layer[a]._locked, save);
			JSON(json[a], _S("_show"), layer[a]._show, save);
		}
	}
	else {
		if (json.is_null())
			return;

		for (auto a = 0; a < json.size(); a++)
		{
			layerStruct layerStr = layerStruct{};

			layerStr._shouldRebuild = true;

			if(!json[a][_S("_locked")].is_null())
				layerStr._locked = json[a][_S("_locked")].get<bool>();

			if (!json[a][_S("_show")].is_null())
				layerStr._show = json[a][_S("_show")].get<bool>();

			if (!json[a][_S("Radius")].is_null())
				layerStr.radius = json[a][_S("Radius")].get<float>();

			if (!json[a][_S("Target")].is_null())
				layerStr.target = json[a][_S("Target")].get<drawTarget>();

			if (!json[a][_S("Type")].is_null())
				layerStr.type = json[a][_S("Type")].get<drawType>();

			if (!json[a][_S("Pos")].is_null())
				layerStr.pos.x = json[a][_S("Pos")][0].get<float>(),
				layerStr.pos.y = json[a][_S("Pos")][1].get<float>();

			if (!json[a][_S("Size")].is_null())
				layerStr.size.x = json[a][_S("Size")][0].get<float>(),
				layerStr.size.y = json[a][_S("Size")][1].get<float>();

			if (!json[a][_S("Color")].is_null())
				layerStr.color.Value.x = json[a][_S("Color")][0].get<float>(),
				layerStr.color.Value.y = json[a][_S("Color")][1].get<float>(),
				layerStr.color.Value.z = json[a][_S("Color")][2].get<float>(),
				layerStr.color.Value.w = json[a][_S("Color")][3].get<float>();

			if (!json[a][_S("Thickness")].is_null())
				layerStr.thickness = json[a][_S("Thickness")].get<float>();

			if (!json[a][_S("Rounding")].is_null())
				layerStr.rounding = json[a][_S("Rounding")].get<float>();

			if (!json[a][_S("RoundFlags")].is_null())
				layerStr.roundFlags = json[a][_S("RoundFlags")].get<ImDrawCornerFlags>();

			if (!json[a][_S("TextValue")].is_null())
				layerStr.textValue = json[a][_S("TextValue")].get<std::string>();

			if (!json[a][_S("FontName")].is_null())
				layerStr.fontName = json[a][_S("FontName")].get<std::string>();

			if (!json[a][_S("FontFile")].is_null())
				layerStr.fontFile = json[a][_S("FontFile")].get<std::string>();

			if (!json[a][_S("FontSize")].is_null())
				layerStr.fontSize = json[a][_S("FontSize")].get<float>();

			if (!json[a][_S("TextAlignX")].is_null())
				layerStr.textAlignX = json[a][_S("TextAlignX")].get<int>();

			if (!json[a][_S("TextAlignY")].is_null())
				layerStr.textAlignY = json[a][_S("TextAlignY")].get<int>();

			if (!json[a][_S("TextSize")].is_null())
				layerStr.textSize[0] = json[a][_S("TextSize")][0].get<float>(),
				layerStr.textSize[1] = json[a][_S("TextSize")][1].get<float>();

			if (!json[a][_S("ImagePath")].is_null())
				layerStr.imagePath = escaped(json[a][_S("ImagePath")].get<std::string>());

			if (!json[a][_S("ImageName")].is_null())
				layerStr.imageName = json[a][_S("ImageName")].get<std::string>();

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

			if (!input[a][_S("Type")].is_null()) proto.type = input[a][_S("Type")].get<elementType>();
			if (!input[a][_S("Name")].is_null()) proto.name = input[a][_S("Name")].get<std::string>();
			if (!input[a][_S("CursorPos")].is_null()) {
				proto.cursorPos[0] = input[a][_S("CursorPos")][0] .get<float>();
				proto.cursorPos[1] = input[a][_S("CursorPos")][1].get<float>();
			}
			if (!input[a][_S("Width")].is_null()) proto.fWidth = input[a][_S("Width")].get<float>();
			if (!input[a][_S("BtnSize")].is_null()) {
				proto.btnSize[0] = input[a][_S("BtnSize")][0].get<float>();
				proto.btnSize[1] = input[a][_S("BtnSize")][1].get<float>();
			}
			if (!input[a][_S("ChildSize")].is_null()) {
				proto.childSize[0] = input[a][_S("ChildSize")][0].get<float>();
				proto.childSize[1] = input[a][_S("ChildSize")][1].get<float>();
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

	JSON(input[_S("Window")], _S("Alpha"), data.window.Alpha, save);
	JSON(input[_S("Window")], _S("DisabledAlpha"), data.window.DisabledAlpha, save);
	JSON(input[_S("Window")], _S("WindowRounding"), data.window.WindowRounding, save);
	JSON(input[_S("Window")], _S("WindowBorderSize"), data.window.WindowBorderSize, save);
	JSON(input[_S("Window")], _S("ChildRounding"), data.window.ChildRounding, save);
	JSON(input[_S("Window")], _S("ChildBorderSize"), data.window.ChildBorderSize, save);
	JSON(input[_S("Window")], _S("PopupRounding"), data.window.PopupRounding, save);
	JSON(input[_S("Window")], _S("PopupBorderSize"), data.window.PopupBorderSize, save);
	JSON(input[_S("Window")], _S("FrameRounding"), data.window.FrameRounding, save);
	JSON(input[_S("Window")], _S("FrameBorderSize"), data.window.FrameBorderSize, save);
	JSON(input[_S("Window")], _S("IndentSpacing"), data.window.IndentSpacing, save);
	JSON(input[_S("Window")], _S("WindowMinSize"), data.window.WindowMinSize, save);
	JSON(input[_S("Window")], _S("WindowPadding"), data.window.WindowPadding, save);
	JSON(input[_S("Window")], _S("WindowSize"), data.window.WindowSize, save);
	JSON(input[_S("Window")], _S("WindowTitleAlign"), data.window.WindowTitleAlign, save);
	JSON(input[_S("Window")], _S("ItemSpacing"), data.window.ItemSpacing, save);
	JSON(input[_S("Window")], _S("ItemInnerSpacing"), data.window.ItemInnerSpacing, save);
	JSON(input[_S("Window")], _S("FramePadding"), data.window.FramePadding, save);
	JSON(input[_S("Window")], _S("Size"), data.window.WindowSize, save);

	JSON(input[_S("Checkbox")], _S("FramePos"), data.checkbox.FramePos, save);
	JSON(input[_S("Checkbox")], _S("FrameSize"), data.checkbox.FrameSize, save);
	JSON(input[_S("Checkbox")], _S("TotalSize"), data.checkbox.TotalSize, save);

	JSONLayer(input[_S("Layers")], data.layers, save);

	Prototyping(input[_S("Prototyping")], gPrototypeSystem->prototypes, save);
}

void projectSystem::ActionTransform(nlohmann::json& input, currentProjectData& data)
{
	JSON(input[_S("Window")], _S("Alpha"), data.window.Alpha, false);
	JSON(input[_S("Window")], _S("DisabledAlpha"), data.window.DisabledAlpha, false);
	JSON(input[_S("Window")], _S("WindowRounding"), data.window.WindowRounding, false);
	JSON(input[_S("Window")], _S("WindowBorderSize"), data.window.WindowBorderSize, false);
	JSON(input[_S("Window")], _S("ChildRounding"), data.window.ChildRounding, false);
	JSON(input[_S("Window")], _S("ChildBorderSize"), data.window.ChildBorderSize, false);
	JSON(input[_S("Window")], _S("PopupRounding"), data.window.PopupRounding, false);
	JSON(input[_S("Window")], _S("PopupBorderSize"), data.window.PopupBorderSize, false);
	JSON(input[_S("Window")], _S("FrameRounding"), data.window.FrameRounding, false);
	JSON(input[_S("Window")], _S("FrameBorderSize"), data.window.FrameBorderSize, false);
	JSON(input[_S("Window")], _S("IndentSpacing"), data.window.IndentSpacing, false);
	JSON(input[_S("Window")], _S("WindowMinSize"), data.window.WindowMinSize, false);
	JSON(input[_S("Window")], _S("WindowPadding"), data.window.WindowPadding, false);
	JSON(input[_S("Window")], _S("WindowSize"), data.window.WindowSize, false);
	JSON(input[_S("Window")], _S("WindowTitleAlign"), data.window.WindowTitleAlign, false);
	JSON(input[_S("Window")], _S("ItemSpacing"), data.window.ItemSpacing, false);
	JSON(input[_S("Window")], _S("ItemInnerSpacing"), data.window.ItemInnerSpacing, false);
	JSON(input[_S("Window")], _S("FramePadding"), data.window.FramePadding, false);
	JSON(input[_S("Window")], _S("Size"), data.window.WindowSize, false);

	JSONLayer(input[_S("Layers")], data.layers, false);
}