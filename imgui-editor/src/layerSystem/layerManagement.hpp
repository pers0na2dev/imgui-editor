#pragma once

#include <memory>

#include "layerSystem.hpp"

class LayerManagement {
public:
	void List(drawTarget target);
	void Render(ImDrawList* draw, drawTarget target);
	void Edit(int index);
	void AddLayer(drawTarget target, bool sideWorkspace);

	void Drag(int index);
	void Resize(int index);
	void Select(int index);
	void Tools();
};

inline auto layerManagement = std::make_shared<LayerManagement>();