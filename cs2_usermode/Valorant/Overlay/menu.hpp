#pragma once
namespace hotkeys
{
	int aimkey;
}
static int keystatus = 0;
static int realkey = 0;

bool GetKey(int key)
{
	realkey = key;
	return true;
}
void ChangeKey(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::aimkey = i;
				keystatus = 0;
				return;
			}
		}
	}
}

static const char* keyNames[] =
{
	"Press any key..",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};

static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}
void HotkeyButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);

	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = "Select Key";
	else
		aimkeys = preview_value;

	if (status == 1)
	{

		aimkeys = "Press the Key";
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 20)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}

int tab = 0;
class GradientLine {
public:

	static bool Render(ImVec2 size)
	{
		static ImColor gradient_colors[] =
		{
			//https://txwes.libguides.com/c.php?g=978475&p=7075536

			//Red
			ImColor(255, 0, 0),
			//Yellow
			ImColor(255,255,0),
			//Lime
			ImColor(0, 255, 0),
			//Cyan / Aqua
			ImColor(0, 255, 255),
			//Blue
			ImColor(0, 0, 255),
			//Magenta / Fuchsia
			ImColor(255, 0, 255),
			//Red
			ImColor(255, 0, 0)
		};

		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImVec2      screen_pos = ImGui::GetCursorScreenPos();

		static int pos = 0;

		if (size.x - pos == 0)
			pos = 0;
		else
			pos++;

		for (int i = 0; i < 6; ++i)
		{
			ImVec2 item_spacing = ImGui::GetStyle().ItemSpacing;

			auto render = [&](int displacement)
				{
					draw_list->AddRectFilledMultiColor
					(
						ImVec2((screen_pos.x - item_spacing.x - displacement) + (i) * (size.x / 6), (screen_pos.y - item_spacing.y)),
						ImVec2((screen_pos.x - item_spacing.x + (item_spacing.x * 2) - displacement) + (i + 1) * (size.x / 6), (screen_pos.y - item_spacing.y) + (size.y)),

						//add one to color to create a skuffed blend
						gradient_colors[i], gradient_colors[i + 1], gradient_colors[i + 1], gradient_colors[i]
					);
				};

			render((pos)); render((pos - size.x));
		}
		return true;
	}
};


void drawmenu() {
	// menu made by aware :)
	if (GetAsyncKeyState(VK_INSERT) & 1) { Settings::bMenu = !Settings::bMenu; }

	if (Settings::bMenu) {
		ImGui::GetForegroundDrawList()->AddRectFilled(ImGui::GetIO().MousePos, ImVec2(ImGui::GetIO().MousePos.x + 5.f,
			ImGui::GetIO().MousePos.y + 5.f), ImColor(255, 255, 255));

		ImGuiStyle* style = &ImGui::GetStyle();

		ImVec4* colors = style->Colors;

		style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
		style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.0f, 0.0263f, 0.0357f, 1.00f);
		style->Colors[ImGuiCol_WindowBg] = ImColor(25, 25, 25);
		style->Colors[ImGuiCol_ChildBg] = ImColor(20, 20, 20);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.080f, 0.080f, 0.080f, 0.940f);
		style->Colors[ImGuiCol_Border] = ImColor(57, 57, 57);
		style->Colors[ImGuiCol_BorderShadow] = ImColor(1, 1, 1);
		style->Colors[ImGuiCol_FrameBg] = ImColor(40, 40, 40);
		style->Colors[ImGuiCol_FrameBgHovered] = ImColor(40, 40, 40);
		style->Colors[ImGuiCol_FrameBgActive] = ImColor(40, 40, 40);
		style->Colors[ImGuiCol_TitleBg] = ImVec4(0.102f, 0.090f, 0.122f, 1.000f);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.102f, 0.090f, 0.122f, 1.000f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.102f, 0.090f, 0.122f, 1.000f);
		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.263f, 0.357f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		//style->Colors[ImGuiCol_CheckMark] = ImColor(MenuColor);
		style->Colors[ImGuiCol_SliderGrab] = ImColor(111, 0, 255);
		style->Colors[ImGuiCol_SliderGrabActive] = ImColor(111, 0, 255);
		style->Colors[ImGuiCol_Button] = ImColor(20, 20, 20);
		style->Colors[ImGuiCol_ButtonHovered] = ImColor(20, 20, 20);
		style->Colors[ImGuiCol_ButtonActive] = ImColor(20, 20, 20);
		style->Colors[ImGuiCol_Header] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		//style->Colors[ImGuiCol_Column] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		//style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	//	style->Colors[ImGuiCol] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style->Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
		//style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
		style->Colors[ImGuiCol_Separator] = ImColor(105, 0, 255);

		style->WindowRounding = 0;

		static int tabb = 0;

		ImGui::SetNextWindowSize(ImVec2(450.000f, 550.000f), ImGuiCond_Once);


		ImGui::Begin(("cheat"), 0, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar);

		GradientLine::Render(ImVec2(ImGui::GetContentRegionAvail().x * 2, 3));
		ImGui::BeginChild(("##backround"), ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar);
		{
			if (ImGui::Button("aimbot", ImVec2(77, 20)))
			{
				tabb = 1;
			}


			ImGui::SameLine();


			if (ImGui::Button("visuals", ImVec2(77, 20)))
			{
				tabb = 2;
			}

			ImGui::SameLine();

			if (ImGui::Button("misc", ImVec2(77, 20)))
			{
				tabb = 3;
			}

			ImGui::SameLine();

			if (ImGui::Button("config", ImVec2(77, 20)))
			{
				tabb = 4;
			}

			ImGui::SameLine();

			if (ImGui::Button("colors", ImVec2(77, 20)))
			{
				tabb = 5;
			}



			// BOTTOM BAR BELOW TAB BUTTONS
			if (tabb == 1)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(111, 0, 255, 255)));


				ImGui::Button(" ", ImVec2(77, 3));


				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();

			}
			else
			{

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 255)));


				ImGui::Button(" ", ImVec2(77, 3));

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}

			// BOTTOM BAR BELOW TAB BUTTONS

			if (tabb == 2)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(111, 0, 255, 255)));

				ImGui::SameLine();

				ImGui::Button(" ", ImVec2(77, 3));


				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();

			}
			else
			{

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 255)));

				ImGui::SameLine();

				ImGui::Button(" ", ImVec2(77, 3));

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}
			// BOTTOM BAR BELOW TAB BUTTONS

			if (tabb == 3)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(111, 0, 255, 255)));

				ImGui::SameLine();

				ImGui::Button(" ", ImVec2(77, 3));


				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();

			}
			else
			{

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 255)));

				ImGui::SameLine();

				ImGui::Button(" ", ImVec2(77, 3));

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}

			// BOTTOM BAR BELOW TAB BUTTONS

			if (tabb == 4)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(111, 0, 255, 255)));

				ImGui::SameLine();

				ImGui::Button(" ", ImVec2(77, 3));


				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();

			}
			else
			{

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 255)));

				ImGui::SameLine();

				ImGui::Button(" ", ImVec2(77, 3));

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}
			// BOTTOM BAR BELOW TAB BUTTONS

			if (tabb == 5)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(111, 0, 255, 255)));

				ImGui::SameLine();

				ImGui::Button(" ", ImVec2(77, 3));


				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();

			}
			else
			{

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 255)));

				ImGui::SameLine();

				ImGui::Button(" ", ImVec2(77, 3));

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}


			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(15, 15, 15, 255)));

			ImGui::BeginChild(("##backro3und"), ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar);
			{
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::SameLine();



				if (tabb == 1) 			// TAB 1 FEATURES
				{
					ImGui::BeginChild(("##tab1left"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{
						ImGui::Checkbox("aimbot", &Settings::aimbot::aimbot);
						if (Settings::aimbot::aimbot) {
							ImGui::SliderFloat("fov", &Settings::aimbot::aim_fov, 1, 360);
							ImGui::Spacing();
							ImGui::Spacing();
							ImGui::SliderFloat("smooth", &Settings::aimbot::smooth, 1, 360);
							ImGui::Spacing();
							ImGui::Text(("key "));
							ImGui::SameLine();
							HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus);
							ImGui::Spacing();
							ImGui::Spacing();
							ImGui::Combo(("hitbox"), &Settings::aimbot::selectedhitbox, Settings::aimbot::hitbox, IM_ARRAYSIZE(Settings::aimbot::hitbox));

						}
						ImGui::Spacing();
						ImGui::Checkbox("fov circle", &Settings::aimbot::fov_circle);
						ImGui::Checkbox("nazi crosshair", &Settings::aimbot::crosshair);
						ImGui::Checkbox("triggerbot", &Settings::aimbot::triggerbot);
						if (Settings::aimbot::triggerbot) {
							ImGui::SliderFloat("delay (ms)", &Settings::aimbot::trigger_delay, 1, 30);
						}

						ImGui::EndChild();
					}

					ImGui::SameLine();

					ImGui::BeginChild(("##tab1right"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{
						ImGui::Text("memory aimbot"); {

						}
						ImGui::EndChild();
					}
				}

				if (tabb == 2)			// TAB 2 FEATURES
				{
					ImGui::BeginChild(("##tab2left"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{

						ImGui::Checkbox("show box", &Settings::Visuals::bBox);
						if (Settings::Visuals::bBox) {
							ImGui::Combo("style", &Settings::Visuals::boxMode, Settings::Visuals::boxStyle, IM_ARRAYSIZE(Settings::Visuals::boxStyle));
						}
						ImGui::Checkbox("show heads", &Settings::Visuals::headcircle);
						ImGui::Checkbox("show bones", &Settings::Visuals::bones);
						ImGui::Checkbox("show armor", &Settings::Visuals::armor);
						ImGui::Checkbox(("show health"), &Settings::Visuals::bHealth);
						if (Settings::Visuals::bHealth == true)
						{
							ImGui::Combo(("health type"), &Settings::Visuals::healthtype, Settings::Visuals::healtht, IM_ARRAYSIZE(Settings::Visuals::healtht));
						}
						ImGui::Checkbox("show snaplines", &Settings::Visuals::bSnaplines);
						ImGui::Checkbox("show distance", &Settings::Visuals::distance);
						ImGui::Checkbox("show names", &Settings::Visuals::names);
						if (ImGui::Checkbox("show glow", &Settings::Visuals::glow)) {

							if (Settings::Visuals::glow) {
								isGlow = true;
								// Turn on the glow by writing the appropriate value
							}
							else {
								isGlow = false;
								// Turn off the glow by writing the appropriate value
							}
						}
						ImGui::EndChild();
					}

					ImGui::SameLine();

					ImGui::BeginChild(("##tab2right"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{

						if (ImGui::Checkbox("no flash", &Settings::Visuals::noflash)) {

							if (Settings::Visuals::noflash) {
								noFlashEnabled = true;
								// Turn on the glow by writing the appropriate value
							}
							else {
								noFlashEnabled = false;
								// Turn off the glow by writing the appropriate value
							}
						}
						if (ImGui::Checkbox("no hands", &Settings::Visuals::nohands)) {

							if (Settings::Visuals::nohands) 
							{
								noHandsEnabled = true;
							}
							else {
								noHandsEnabled = false;
							}
						}

						ImGui::Checkbox("chams", &Settings::Visuals::chams);
						ImGui::Checkbox("no ragdolls", &Settings::Visuals::ragdoll);
						ImGui::Checkbox("night mode", &Settings::Visuals::nightmode);

						ImGui::EndChild();
					}
				}

				if (tabb == 3)			// TAB 3 FEATURES
				{
					ImGui::BeginChild(("##tab3left"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{
						ImGui::Checkbox(("radar"), &Settings::misc::radar);

						ImGui::Checkbox("bunny hop", &Settings::misc::bhop);

						ImGui::Checkbox("fov changer", &Settings::misc::fovChanger);

						if (Settings::misc::fovChanger) {
							ImGui::SliderFloat("fov", &Settings::misc::fov, 1, 360);
							isFOV = true;
						}
						else {
							Settings::misc::fov = originalFOV;
							isFOV = false;

						}
						ImGui::EndChild();
					}

					ImGui::SameLine();

					ImGui::BeginChild(("##tab3right"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{

						ImGui::Checkbox("save fps", &Settings::misc::save_fps);
						ImGui::Checkbox("water mark", &Settings::misc::water);


						ImGui::EndChild();
					}
				}

				if (tabb == 4)			// TAB 4 FEATURES
				{
					ImGui::BeginChild(("##tab4left"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{

						ImGui::Button("save config");
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Spacing();

						ImGui::Button("load config");
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Spacing();

						ImGui::Button("import from clipboard");

						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Spacing();

						ImGui::Button("load legit settings");
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Spacing();

						ImGui::Button("load rage settings");


						ImGui::EndChild();
					}

					ImGui::SameLine();

					ImGui::BeginChild(("##tab4right"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{

						ImGui::Text("under construction");


						ImGui::EndChild();
					}
				}

				if (tabb == 5)			// TAB 5 FEATURES
				{
					ImGui::BeginChild(("##tab5left"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{

						ImGui::Text("under construction");

						ImGui::EndChild();
					}

					ImGui::SameLine();

					ImGui::BeginChild(("##tab5right"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{

						ImGui::Text("under construction");


						ImGui::EndChild();
					}
				}

				ImGui::EndChild();

			}

			ImGui::PopStyleColor();

			ImGui::EndChild();
		}




		ImGui::End();
	}
	
}

