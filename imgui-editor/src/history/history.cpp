#include "history.hpp"

void historySystem::RegisterHistoryItem() {
	//historyIterator = historyItems.size() - 1;
	//historyItems.push_back(gProjectSystem->data);
}

void historySystem::Undo() {
	//if (historyItems.size() == 1)
	//	return;

	//gProjectSystem->data = historyItems[historyIterator];

	//if (historyIterator > 0) 
	//	historyIterator -= 1;
}

void historySystem::Redo() {
	//if (historyItems.size() == 1)
	//	return;

	//if (historyIterator < historyItems.size() - 1)
	//	historyIterator += 1;

	//gProjectSystem->data = historyItems[historyIterator];
}

void historySystem::Clear()
{
	//historyItems.clear();
}
