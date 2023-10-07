#pragma once
#include <iostream>
#include "C:\Users\ka\Desktop\Valorant-External-1-master\Valorant\Overlay\render.hpp"

bool cached = false;

auto ESPColor = ImColor(255, 255, 255);

namespace offsets
{
	std::ptrdiff_t dwEntityList = 0x17888D8;
	std::ptrdiff_t dwViewMatrix = 0x1876730;
	std::ptrdiff_t dwLocalPlayer = 0x17D7158; //dwLocalPlayerController offsets.rs

	std::ptrdiff_t dwPawnHealth = 0x808;
	std::ptrdiff_t dwPlayerPawn = 0x7FC; //m_hPlayerPawn client.dll.rs
	std::ptrdiff_t dwSanitizedName = 0x720;
	std::ptrdiff_t m_bDormant = 0xE7;
	std::ptrdiff_t m_iTeamNum = 0x3bf;
	std::ptrdiff_t m_vecOrigin = 0x1214; //m_vOldOrigin client.dll.rs
	std::ptrdiff_t m_iHealth = 0x32C; //m_iHealth client.dll.rs
}

void espLoop()
{
	uintptr_t localPlayer = driver.readv<uintptr_t>(client + offsets::dwLocalPlayer);
	if (!localPlayer) return;

	int localTeam = driver.readv<int>(localPlayer + offsets::m_iTeamNum);

	view_matrix_t view_matrix = driver.readv<view_matrix_t>(client + offsets::dwViewMatrix);

	Vector3 localOrigin = driver.readv<Vector3>(localPlayer + offsets::m_vecOrigin);

	uintptr_t entity_list = driver.readv<uintptr_t>(client + offsets::dwEntityList);

	for (int i = 1; i < 32; i++) {
		uintptr_t list_entry = driver.readv<uintptr_t>(entity_list + (8 * (i & 0x7FFF) >> 9) + 16);
		if (!list_entry) continue;
		uintptr_t player = driver.readv<uintptr_t>(list_entry + 120 * (i & 0x1FF));

		if (!player) continue;

		int playerHealth = driver.readv<int>(player + offsets::dwPawnHealth);
		if (playerHealth <= 0 || playerHealth > 100) continue;

		std::uint32_t playerpawn = driver.readv<std::uint32_t>(player + offsets::dwPlayerPawn);

		uintptr_t list_entry2 = driver.readv<uintptr_t>(entity_list + 0x8 * ((playerpawn & 0x7FFF) >> 9) + 16);
		if (!list_entry2) continue;
		uintptr_t pCSPlayerPawn = driver.readv<uintptr_t>(list_entry2 + 120 * (playerpawn & 0x1FF));

		if (pCSPlayerPawn == localPlayer) continue;

		int playerTeam = driver.readv<int>(player + offsets::m_iTeamNum);

		Vector3 origin = driver.readv<Vector3>(pCSPlayerPawn + offsets::m_vecOrigin);

		Vector3 head;
		head.x = origin.x;
		head.y = origin.y;
		head.z = origin.z + 75.f;

		// feet
		Vector3 screenpos = origin.world_to_screen(view_matrix);

		// head
		Vector3 screenhead = head.world_to_screen(view_matrix);

		if (screenpos.z >= 0.01f) {
			if (localTeam == playerTeam)
				continue;

			float height = screenpos.y - screenhead.y;
			float width = height / 2.4f;

			if (Settings::Visuals::bBox)
				ImGui::GetBackgroundDrawList()->AddRect({ screenhead.x - width, screenhead.y }, { screenhead.x + width, screenpos.y }, ImColor(255, 255, 255), 1.f);
			if (Settings::Visuals::bSnaplines)
				ImGui::GetBackgroundDrawList()->AddLine({ screenpos.x, screenpos.y }, { 1920 / 2, 1080 }, ImColor(255, 255, 255));
			if (Settings::Visuals::headcircle) {
				ImGui::GetForegroundDrawList()->AddCircle({ screenhead.x , screenhead.y }, 2.0f, ImColor(255, 255, 255));
			}
			if (Settings::Visuals::bHealth) {
				char dist[64];
				sprintf_s(dist, "%d", playerHealth);

				ImVec2 TextSize = ImGui::CalcTextSize(dist);
				ImGui::GetForegroundDrawList()->AddText(ImVec2(screenpos.x - TextSize.x / 2, screenpos.y - TextSize.y / 2), ImGui::GetColorU32({ 255, 255, 255, 255 }), dist);

			}

		}
	}
}


