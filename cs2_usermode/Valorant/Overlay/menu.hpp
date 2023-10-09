#pragma once

auto drawmenu() -> void
{
	if (GetAsyncKeyState(VK_INSERT) & 1) { Settings::bMenu = !Settings::bMenu; }

	if (Settings::bMenu)
	{
		ImGui::Begin("Counter Strike 2", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

		ImGui::SetWindowSize("Counter Strike 2", ImVec2(210, 150));

		ImGui::Spacing();

		ImGui::Checkbox("box", &Settings::Visuals::bBox);
		if (Settings::Visuals::bBox) Settings::Visuals::bBoxOutlined = false;

		ImGui::Checkbox("snaplines", &Settings::Visuals::bSnaplines);
		ImGui::Checkbox("head cirlce", &Settings::Visuals::headcircle);
		ImGui::Checkbox("health", &Settings::Visuals::bHealth);

		ImGui::End();
	}
}