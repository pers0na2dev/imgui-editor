#pragma once

#include <memory>
#include <vector>
#include <string>

#include "../context.hpp"
#include "../utils/utils.hpp"

#include <imgui.h>
#include <imgui_internal.h>

enum class elementType : int {
	CURSOR_POS, SAMELINE,
	CHILD, GROUP,
	TAB, SUBTAB,
	CHECKBOX, SLIDER_INT, SLIDER_FLOAT, COMBO, BUTTON, COLORPICKER
};

struct widgetPrototype {
	elementType type;
	std::string name;

	// checkbox
	bool bVal;

	// combo
	std::vector<std::string> comboNames;

	// slider int, slider float
	int iVal, iMin, iMax;
	float fVal, fMin, fMax;

	// cursor pos
	ImVec2 cursorPos;
	
	// sameline
	float fWidth;

	// button 
	ImVec2 btnSize;

	// child / group
	ImVec2 childSize;
	std::vector<widgetPrototype> items;

	void addCursorPos(ImVec2 size)
	{
		items.push_back(widgetPrototype{
			.type = elementType::CURSOR_POS,
			.name = "SetCursorPos",
			.cursorPos = size
			});
	}

	void addSameline(float width)
	{
		items.push_back(widgetPrototype{
			.type = elementType::SAMELINE,
			.name = "SameLine",
			.fWidth = width,
			});
	}

	void addCheckbox()
	{
		items.push_back(widgetPrototype{
			.type = elementType::CHECKBOX,
			.name = "Checkbox"
			});
	}

	void addSliderInt(int min, int max)
	{
		items.push_back(widgetPrototype{
			.type = elementType::SLIDER_INT,
			.name = "SliderInt",
			.iMin = min,
			.iMax = max
			});
	}

	void addSliderFloat(float min, float max)
	{
		items.push_back(widgetPrototype{
			.type = elementType::SLIDER_FLOAT,
			.name = "SliderFloat",
			.fMin = min,
			.fMax = max
		});
	}

	void addCombo()
	{
		items.push_back(widgetPrototype{
			.type = elementType::COMBO,
			.name = "Combo"
		});
	}

	void addChild(ImVec2 size)
	{
		items.push_back(widgetPrototype{
			.type = elementType::CHILD,
			.name = "Child",
			.childSize = size
		});
	}

	void addGroup()
	{
		items.push_back(widgetPrototype{
			.type = elementType::GROUP,
			.name = "Group"
		});
	}


	void addButton()
	{
		items.push_back(widgetPrototype{
			.type = elementType::BUTTON,
			.name = "Button"
		});
	}

	void addTab()
	{
		items.push_back(widgetPrototype{
			.type = elementType::TAB,
			.name = "Tab"
		});
	}

	void addSubtab()
	{
		items.push_back(widgetPrototype{
			.type = elementType::SUBTAB,
			.name = "Subtab"
		});
	}

	void addColorpicker()
	{
		items.push_back(widgetPrototype{
			.type = elementType::COLORPICKER,
			.name = "ColorPicker"
		});
	}
};

class prototypeSystem {
public:
	void addCursorPos(ImVec2 size);
	void addSameline(float width);

	void addCheckbox();
	void addSliderInt(int min, int max);
	void addSliderFloat(float min, float max);
	void addCombo();

	void addButton();
	void addTab();
	void addSubtab();
	void addColorpicker();

	void addChild(ImVec2 size);
	void addGroup();

	std::vector<widgetPrototype> prototypes;
};

inline auto gPrototypeSystem = std::make_shared<prototypeSystem>();

