#pragma once
#include <iostream>
#include "../../Valorant/Overlay/render.hpp"

using namespace ColorStructs;

class Cham
{
public:
	uint8_t red_;
	uint8_t green_;
	uint8_t blue_;
	uint8_t alpha_;

	Cham() = default;
	constexpr Cham(uint8_t new_red, uint8_t new_green, uint8_t new_blue, uint8_t new_alpha) : red_(new_red), green_(new_green), blue_(new_blue), alpha_(new_alpha)
	{
		//empty
	}
};

bool w2s(const Vector3& pos, Vector3& out, view_matrix_t matrix)
{
	out.x = matrix[0][0] * pos.x + matrix[0][1] * pos.y + matrix[0][2] * pos.z + matrix[0][3];
	out.y = matrix[1][0] * pos.x + matrix[1][1] * pos.y + matrix[1][2] * pos.z + matrix[1][3];

	float w = matrix[3][0] * pos.x + matrix[3][1] * pos.y + matrix[3][2] * pos.z + matrix[3][3];

	if (w < 0.01f)
		return false;

	float inv_w = 1.f / w;
	out.x *= inv_w;
	out.y *= inv_w;

	float x = ww * 0.5f;
	float y = wh * 0.5f;

	x += 0.5f * out.x * ww + 0.5f;
	y -= 0.5f * out.y * wh + 0.5f;

	out.x = x;
	out.y = y;

	return true;
}

namespace colors
{
	float chamscol[3] = { 1.0f , 1.0f , 1.0f };
	float espcol[3] = { 1.0f , 1.0f , 1.0f };
	float skelcol[3] = { 1.0f , 1.0f , 1.0f };
	float crosscol[3] = { 1.0f , 10.0f , 0.0f };

	float orecol[3] = { 1.0f , 1.0f , 1.0f };
	float collcol[3] = { 1.0f , 1.0f , 1.0f };
	float cratecol[3] = { 1.0f , 1.0f , 1.0f };
	float scientistcol[3] = { 1.0f , 1.0f , 1.0f };
	float itemscol[3] = { 1.0f , 1.0f , 1.0f };
}

float Calc2D_Distt(const Vector2& Src, const Vector3& Dst)
{
	float dx = Src.x - Dst.x;
	float dy = Src.y - Dst.y;
	return sqrt(dx * dx + dy * dy);
}

float AimFov(Vector3 ScreenPos)
{
	return Calc2D_Distt(Vector2(ScreenCenterX, ScreenCenterY), ScreenPos);
}

auto cacheGame() -> void
{
	while (true)
	{
		std::vector<CS2Entity> temp;

		uintptr_t dwLocalPlayerPawn = driver.readv<uintptr_t>(client + offsets::dwLocalPlayerPawn);
		if (!dwLocalPlayerPawn) continue;

		global_pawn = dwLocalPlayerPawn;

		int localTeam = driver.readv<int>(dwLocalPlayerPawn + offsets::m_iTeamNum);
		view_matrix_t view_matrix = driver.readv<view_matrix_t>(client + offsets::dwViewMatrix);
		Vector3 localOrigin = driver.readv<Vector3>(dwLocalPlayerPawn + offsets::m_vecOrigin);
		uintptr_t entity_list = driver.readv<uintptr_t>(client + offsets::dwEntityList);

		for (int i = 1; i < 32; i++)
		{
			uintptr_t list_entry = driver.readv<uintptr_t>(entity_list + (8 * (i & 0x7FFF) >> 9) + 16);
			if (!list_entry) continue;
			uintptr_t player = driver.readv<uintptr_t>(list_entry + 120 * (i & 0x1FF));
			if (!player) continue;
			std::uint32_t playerpawn = driver.readv<std::uint32_t>(player + offsets::dwPlayerPawn);

			uintptr_t list_entry2 = driver.readv<uintptr_t>(entity_list + 0x8 * ((playerpawn & 0x7FFF) >> 9) + 16);
			if (!list_entry2) continue;
			uintptr_t pCSPlayerPawn = driver.readv<uintptr_t>(list_entry2 + 120 * (playerpawn & 0x1FF));
			int csPlayerHealth = driver.readv<int>(pCSPlayerPawn + offsets::m_iHealth);
			int armorHealth = driver.readv<int>(pCSPlayerPawn + offsets::m_ArmorValue);
			if (csPlayerHealth <= 0 || csPlayerHealth > 100) continue;
			if (pCSPlayerPawn == dwLocalPlayerPawn) continue;
			int playerTeam = driver.readv<int>(player + offsets::m_iTeamNum);
			
			if (localTeam == playerTeam)
				continue;

			CS2Entity Entities;
			Entities.Actor = pCSPlayerPawn;
			Entities.health = csPlayerHealth;
			Entities.armor = armorHealth;
			
			temp.push_back(Entities);
		}
		PlayerList.clear();
		PlayerList = temp;
		Sleep(1000);
	}
}


void espLoop()
{
	ImColor Red = { 250, 92, 255, 255 };
	auto ESPColor = ImColor(255, 255, 255);

	if (global_pawn) {
		view_matrix_t view_matrix = driver.readv<view_matrix_t>(client + offsets::dwViewMatrix);

		if (Settings::misc::bhop)
		{
			const auto on_ground = (driver.readv<uint8_t>(global_pawn + 0x3C8) & 1) != 0;
			if (GetAsyncKeyState(VK_SPACE) < 0 && on_ground)
			{
				driver.write<DWORD>(client + offsets::forceJump, 65537);

			}
			else
			{
				driver.write<DWORD>(client + offsets::forceJump, 256);
			}
		}
		if (Settings::Visuals::nohands) {
			driver.write<int>(global_pawn + 0x40, 0); // no hands
		}
		if (Settings::misc::water)
		{
			ImColor Red = { 250, 92, 255, 255 };
			std::string Watermark = "unknowncheats.me";
			ImGui::GetForegroundDrawList()->AddText(ImVec2(Width / 2 - 45, Height / 2 - 400), Red, Watermark.c_str());
		}
		if (Settings::aimbot::crosshair) {
			DrawCrossNazi(10, Red);
		}
		if (Settings::aimbot::fov_circle) {
			DWORD ScreenCenterX = GetSystemMetrics(SM_CXSCREEN);
			DWORD ScreenCenterY = GetSystemMetrics(SM_CYSCREEN);
			ImGui::GetForegroundDrawList()->AddCircle(ImVec2(ScreenCenterX / 2, ScreenCenterY / 2), Settings::aimbot::aim_fov, Red, 10000);
		}
		if (noFlashEnabled) {
			driver.write<float>(global_pawn + 0x1450, 0.f); // on remember to make this default flash alpha
		}

		// player info reading :
		for (CS2Entity CachePlayers : PlayerList)
		{
			Vector3 origin = driver.readv<Vector3>(CachePlayers.Actor + offsets::m_vecOrigin);

			Vector3 head;
			head.x = origin.x;
			head.y = origin.y;
			head.z = origin.z + 75.f;

			// feet
			Vector3 screenpos = origin.world_to_screen(view_matrix);

			// head
			Vector3 screenhead = head.world_to_screen(view_matrix);
			uint64_t gamescene = driver.readv<uint64_t>(CachePlayers.Actor + 0x310);
			uint64_t bonearray = driver.readv<uint64_t>(gamescene + 0x160 + 0x80);

			uintptr_t pCameraServicesPtr = driver.readv<uintptr_t>(global_pawn + 0x10E0);

			Vector3 playerpos = driver.readv<Vector3>(CachePlayers.Actor + offsets::m_vecOrigin);
			Vector3 pos;

			Vector3 head_pos = Vector3(playerpos.x, playerpos.y, playerpos.z + 63);
			Vector3 heady;

			Vector3 aim_pos = Vector3(playerpos.x, playerpos.y, playerpos.z + 45);
			Vector3 aim;

			Vector3 headHitBox;
			Vector3 heady2 = driver.readv<Vector3>(bonearray + 6 * 32);

			if (!w2s(heady2, headHitBox, view_matrix))
				continue;

			if (!w2s(playerpos, pos, view_matrix))
				continue;

			if (!w2s(head_pos, heady, view_matrix))
				continue;

			if (!w2s(aim_pos, aim, view_matrix))
				continue;

			if (screenpos.z >= 0.01f)
			{
				Vector3 head = driver.readv<Vector3>(bonearray + 6 * 32);
				Vector3 projectHead = head.world_to_screen(view_matrix);

				float height = abs(screenpos.y - screenhead.y);
				float width = height / 2.0f;

				if (Settings::Visuals::bBox)
				{
					if (Settings::Visuals::boxMode == 0) {
						!Settings::Visuals::bBox;   //off
					}

					RGBA ESPColor = { colors::espcol[0] * 255, colors::espcol[1] * 255, colors::espcol[2] * 255, 255 };
					if (Settings::Visuals::boxMode == 1)   //2d box
					{
						DrawNormalBox(screenpos.x - width / 2 + 1, screenhead.y, width, height, 1, &Col.black);
						DrawNormalBox(screenpos.x - width / 2 - 1, screenhead.y, width, height, 1, &Col.black);
						DrawNormalBox(screenpos.x - width / 2, screenhead.y + 1, width, height, 1, &Col.black);
						DrawNormalBox(screenpos.x - width / 2, screenhead.y - 1, width, height, 1, &Col.black);
						DrawNormalBox(screenpos.x - (width / 2), screenhead.y, width, height, 1, &ESPColor);

					}
					if (Settings::Visuals::boxMode == 2) {
						DrawCornerBox(screenpos.x - width / 2 + 1, screenhead.y, width, height, 1, &Col.black);
						DrawCornerBox(screenpos.x - width / 2 - 1, screenhead.y, width, height, 1, &Col.black);
						DrawCornerBox(screenpos.x - width / 2, screenhead.y + 1, width, height, 1, &Col.black);
						DrawCornerBox(screenpos.x - width / 2, screenhead.y - 1, width, height, 1, &Col.black);
						DrawCornerBox(screenpos.x - (width / 2), screenhead.y, width, height, 1, &ESPColor);
					}
					if (Settings::Visuals::boxMode == 3)

					{

						DrawFilledRect(screenpos.x - (width / 2), screenhead.y, width, height, &Col.filled);
						DrawNormalBox(screenpos.x - width / 2 + 1, screenhead.y, width, height, 1, &Col.black);
						DrawNormalBox(screenpos.x - width / 2 - 1, screenhead.y, width, height, 1, &Col.black);
						DrawNormalBox(screenpos.x - width / 2, screenhead.y + 1, width, height, 1, &Col.black);
						DrawNormalBox(screenpos.x - width / 2, screenhead.y - 1, width, height, 1, &Col.black);
						DrawNormalBox(screenpos.x - (width / 2), screenhead.y, width, height, 1, &ESPColor);

					}
				}

				if (Settings::Visuals::bSnaplines)
					ImGui::GetBackgroundDrawList()->AddLine({ screenpos.x, screenpos.y }, ImVec2(Width / 2, Height), ImColor(255, 255, 255));
				if (Settings::Visuals::headcircle)
				{

					ImGui::GetForegroundDrawList()->AddCircle(ImVec2(projectHead.x, projectHead.y), height / 10, (ImU32)&Col.white, 100);
					ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(projectHead.x, projectHead.y), height / 10, (ImU32)&Col.filled, 100);
				}
				if (Settings::Visuals::bHealth)
				{


					int G1 = (255 * CachePlayers.health / 100);
					int R1 = 255 - G1;
					ImColor healthcol = { R1, G1, 0, 255 };
					std::string Out69 = "[H: " + std::to_string(static_cast<int32_t>(CachePlayers.health)) + "]";
					ImVec2 TextSize = ImGui::CalcTextSize(Out69.c_str());

					if (Settings::Visuals::healthtype == 0)
					{
						ImGui::GetForegroundDrawList()->AddText(ImVec2(screenpos.x - TextSize.x / 2, screenpos.y + 5 - TextSize.y / 2), healthcol, Out69.c_str());
					}

					else if (Settings::Visuals::healthtype == 1)
					{
						DrawRightProgressBar(screenpos.x + 30, screenhead.y, width, height, 2, CachePlayers.health);
					}

					else if (Settings::Visuals::healthtype == 2)

					{
						DrawRightProgressBar(screenpos.x + 30, screenhead.y, width, height, 2, CachePlayers.health);
						ImGui::GetForegroundDrawList()->AddText(ImVec2(screenpos.x - TextSize.x / 2, screenpos.y + 5 - TextSize.y / 2), healthcol, Out69.c_str());
					}

				}
				if (Settings::Visuals::armor) {
					DrawArmor(screenpos.x + 35, screenhead.y, width, height, 2, CachePlayers.armor);

				}
				if (Settings::Visuals::distance) {

				}
				if (Settings::Visuals::bones)
				{
					Vector3 head = driver.readv<Vector3>(bonearray + 6 * 32);
					Vector3 cou = driver.readv<Vector3>(bonearray + 5 * 32);
					Vector3 shoulderR = driver.readv<Vector3>(bonearray + 8 * 32);
					Vector3 shoulderL = driver.readv<Vector3>(bonearray + 13 * 32);
					Vector3 brasR = driver.readv<Vector3>(bonearray + 9 * 32);
					Vector3 brasL = driver.readv<Vector3>(bonearray + 14 * 32);
					Vector3 handR = driver.readv<Vector3>(bonearray + 11 * 32);
					Vector3 handL = driver.readv<Vector3>(bonearray + 16 * 32);
					Vector3 cock = driver.readv<Vector3>(bonearray + 0 * 32);
					Vector3 kneesR = driver.readv<Vector3>(bonearray + 23 * 32);
					Vector3 kneesL = driver.readv<Vector3>(bonearray + 26 * 32);
					Vector3 feetR = driver.readv<Vector3>(bonearray + 24 * 32);
					Vector3 feetL = driver.readv<Vector3>(bonearray + 27 * 32);

					Vector3 Ahead;
					Vector3 Acou;
					Vector3 AshoulderR;
					Vector3 AshoulderL;
					Vector3 AbrasR;
					Vector3 AbrasL;
					Vector3 AhandR;
					Vector3 AhandL;
					Vector3 Acock;
					Vector3 AkneesR;
					Vector3 AkneesL;
					Vector3 AfeetR;
					Vector3 AfeetL;

					if (!w2s(head, Ahead, view_matrix))
						continue;
					if (!w2s(cou, Acou, view_matrix))
						continue;
					if (!w2s(shoulderR, AshoulderR, view_matrix))
						continue;
					if (!w2s(shoulderL, AshoulderL, view_matrix))
						continue;
					if (!w2s(brasR, AbrasR, view_matrix))
						continue;
					if (!w2s(brasL, AbrasL, view_matrix))
						continue;
					if (!w2s(handL, AhandL, view_matrix))
						continue;
					if (!w2s(handR, AhandR, view_matrix))
						continue;
					if (!w2s(cock, Acock, view_matrix))
						continue;
					if (!w2s(kneesR, AkneesR, view_matrix))
						continue;
					if (!w2s(kneesL, AkneesL, view_matrix))
						continue;
					if (!w2s(feetR, AfeetR, view_matrix))
						continue;
					if (!w2s(feetL, AfeetL, view_matrix))
						continue;

					ImGui::GetBackgroundDrawList()->AddLine({ Acou.x, Acou.y }, { Ahead.x, Ahead.y }, ImColor(255, 255, 255));
					ImGui::GetBackgroundDrawList()->AddLine({ Acou.x, Acou.y }, { AshoulderR.x, AshoulderR.y }, ImColor(255, 255, 255));
					ImGui::GetBackgroundDrawList()->AddLine({ Acou.x, Acou.y }, { AshoulderL.x, AshoulderL.y }, ImColor(255, 255, 255));
					ImGui::GetBackgroundDrawList()->AddLine({ AbrasL.x, AbrasL.y }, { AshoulderL.x, AshoulderL.y }, ImColor(255, 255, 255));
					ImGui::GetBackgroundDrawList()->AddLine({ AbrasR.x, AbrasR.y }, { AshoulderR.x, AshoulderR.y }, ImColor(255, 255, 255));
					ImGui::GetBackgroundDrawList()->AddLine({ AbrasR.x, AbrasR.y }, { AhandR.x, AhandR.y }, ImColor(255, 255, 255));
					ImGui::GetBackgroundDrawList()->AddLine({ AbrasL.x, AbrasL.y }, { AhandL.x, AhandL.y }, ImColor(255, 255, 255));
					ImGui::GetBackgroundDrawList()->AddLine({ Acou.x, Acou.y }, { Acock.x, Acock.y }, ImColor(255, 255, 255));
					ImGui::GetBackgroundDrawList()->AddLine({ AkneesR.x, AkneesR.y }, { Acock.x, Acock.y }, ImColor(255, 255, 255));
					ImGui::GetBackgroundDrawList()->AddLine({ AkneesL.x, AkneesL.y }, { Acock.x, Acock.y }, ImColor(255, 255, 255));
					ImGui::GetBackgroundDrawList()->AddLine({ AkneesL.x, AkneesL.y }, { AfeetL.x, AfeetL.y }, ImColor(255, 255, 255));
					ImGui::GetBackgroundDrawList()->AddLine({ AkneesR.x, AkneesR.y }, { AfeetR.x, AfeetR.y }, ImColor(255, 255, 255));
				}

				if (isGlow)
				{
					driver.write<float>(CachePlayers.Actor + offsets::m_flDetectedByEnemySensorTime, 86400.f); // on
				}

				if (isFOV)
				{
					driver.write<uint32_t>(pCameraServicesPtr + 0x210, Settings::misc::fov); // need to add checks for scopes or not.
				}

				if (Settings::Visuals::chams) {
					static constexpr Cham kEnemyColor{ 250, 92, 255, 255 }; // rgba, need to add brigtness. this only colors the model purple working cts.
					driver.write(CachePlayers.Actor + 0xA73, kEnemyColor);
					driver.write(CachePlayers.Actor + 0xA73, kEnemyColor);
					driver.write(CachePlayers.Actor + 0xA73, kEnemyColor);
				}


				if (Settings::aimbot::aimbot) {
					if (GetAsyncKeyState(hotkeys::aimkey) && (AimFov(aim) < Settings::aimbot::aim_fov)) {
						if (Settings::aimbot::selectedhitbox == 0) {
							mouse_event(MOUSEEVENTF_MOVE, (headHitBox.x - (ScreenCenterX)) / Settings::aimbot::smooth, (headHitBox.y - (ScreenCenterY)) / Settings::aimbot::smooth, 0, 0);
						}

						if (Settings::aimbot::selectedhitbox == 1) {
							mouse_event(MOUSEEVENTF_MOVE, (aim.x - (ScreenCenterX)) / Settings::aimbot::smooth, (aim.y - (ScreenCenterY)) / Settings::aimbot::smooth, 0, 0);

						}
					}
				}

			}
		}
	}
	
}




