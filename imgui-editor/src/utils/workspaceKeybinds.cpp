#include "workspaceKeybinds.hpp"
#include "../filesystem/filesystem.hpp"
#include "../history/history.hpp"

void WorkspaceKeybinds::Layer()
{
	if (gContext.SelectedLayer == -1)
		return;

	if (ImGui::GetIO().WantCaptureKeyboard)
		return;

	if (ImGui::IsKeyDown(ImGuiKey_Delete))
	{
		gProjectSystem->data.layers.erase(gProjectSystem->data.layers.begin() + gContext.SelectedLayer);
		gContext.SelectedLayer = -1;
	}
}

void WorkspaceKeybinds::Tools()
{
	if (ImGui::GetIO().WantCaptureKeyboard)
		return;

	if (ImGui::IsKeyPressed(ImGuiKey_0)) gContext.SelectedEditor = 0;
	if (ImGui::IsKeyPressed(ImGuiKey_1)) gContext.SelectedEditor = 1;
	if (ImGui::IsKeyPressed(ImGuiKey_2)) gContext.SelectedEditor = 2;
	if (ImGui::IsKeyPressed(ImGuiKey_3)) gContext.SelectedEditor = 3;
	if (ImGui::IsKeyPressed(ImGuiKey_4)) gContext.SelectedEditor = 4;
	if (ImGui::IsKeyPressed(ImGuiKey_5)) gContext.SelectedEditor = 5;
	if (ImGui::IsKeyPressed(ImGuiKey_6)) gContext.SelectedEditor = 6;
}

void WorkspaceKeybinds::Save() {
	if (ImGui::GetIO().KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_S))
		gFileSystem->SaveProject();
}

void WorkspaceKeybinds::HandleMouse(ImVec2& pos)
{
	if (ImGui::IsMouseDown(ImGuiMouseButton_Middle))
	{
		pos += ImGui::GetIO().MouseDelta;
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}
	else if (ImGui::IsMouseReleased(ImGuiMouseButton_Middle))
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
	}

	if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && gContext.MouseInWorkspaceSide())
		gContext.SelectedLayer = -1;
}

void WorkspaceKeybinds::History() {
	if (ImGui::GetIO().KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_Z))
		gHistorySystem->Undo();

	if (ImGui::GetIO().KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_Y))
		gHistorySystem->Redo();
}
