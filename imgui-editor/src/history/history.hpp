#pragma once

#include <memory>

#include "../context.hpp"
#include "../projects/projectSystem.hpp"

class historySystem {
public:
	void RegisterHistoryItem();
	void Undo();
	void Redo();
	void Clear();

private:
	std::size_t historyIterator = 0;
	std::vector<currentProjectData> historyItems;
};

inline auto gHistorySystem = std::make_shared<historySystem>();
