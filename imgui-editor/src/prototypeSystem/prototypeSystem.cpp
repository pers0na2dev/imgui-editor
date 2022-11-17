#include "prototypeSystem.hpp"
#include "../utils/utils.hpp"

void prototypeSystem::addCursorPos(ImVec2 size)
{
	prototypes.push_back(widgetPrototype{
		.type = elementType::CURSOR_POS,
		.name = "SetCursorPos",
		.cursorPos = size
	});
}

void prototypeSystem::addSameline(float width)
{
	prototypes.push_back(widgetPrototype{
		.type = elementType::SAMELINE,
		.name = "SameLine",
		.fWidth = width,
	});
}

void prototypeSystem::addCheckbox()
{
	prototypes.push_back(widgetPrototype{
		.type = elementType::CHECKBOX,
		.name = "Checkbox",
	});
}

void prototypeSystem::addSliderInt(int min, int max)
{
	prototypes.push_back(widgetPrototype{
		.type = elementType::SLIDER_INT,
		.name = "SliderInt",
		.iMin = min,
		.iMax = max
	});
}

void prototypeSystem::addSliderFloat(float min, float max)
{
	prototypes.push_back(widgetPrototype{
		.type = elementType::SLIDER_FLOAT,
		.name = "SliderFloat",
		.fMin = min,
		.fMax = max
	});
}

void prototypeSystem::addCombo()
{
	prototypes.push_back(widgetPrototype{
		.type = elementType::COMBO,
		.name = "Combo",
	});
}

void prototypeSystem::addButton()
{
	prototypes.push_back(widgetPrototype{
		.type = elementType::BUTTON,
		.name = "Button",
	});
}

void prototypeSystem::addTab()
{
	prototypes.push_back(widgetPrototype{
		.type = elementType::TAB,
		.name = "Tab",
	});
}

void prototypeSystem::addSubtab()
{
	prototypes.push_back(widgetPrototype{
		.type = elementType::SUBTAB,
		.name = "Subtab"
	});
}

void prototypeSystem::addColorpicker()
{
	prototypes.push_back(widgetPrototype{
		.type = elementType::COLORPICKER,
		.name = "ColorPicker",
	});
}

void prototypeSystem::addChild(ImVec2 size)
{
	prototypes.push_back(widgetPrototype{
		.type = elementType::CHILD,
		.name = "Child",
		.childSize = size
	});
}

void prototypeSystem::addGroup()
{
	prototypes.push_back(widgetPrototype{
		.type = elementType::GROUP,
		.name = "Group",
	});
}
