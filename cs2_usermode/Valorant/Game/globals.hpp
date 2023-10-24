#pragma once
#include <Windows.h>

HWND Entryhwnd = NULL;
int processid = 0;
RECT Rect;

ULONG64 client = 0;
uintptr_t global_pawn = 0;

bool isGlow = false;
bool isFOV = 0;
bool noFlashEnabled = false;
bool noSmokeEnabled = false;
bool noHandsEnabled = false;
float originalFOV = 68.0f; 

namespace offsets
{
    std::ptrdiff_t dwEntityList = 0x1798738;
    std::ptrdiff_t dwViewMatrix = 0x1886710;
    std::ptrdiff_t dwLocalPlayerController = 0x17E7158;
    std::ptrdiff_t dwLocalPlayerPawn = 0x1885C28;

    std::ptrdiff_t dwPawnHealth = 0x808;
    std::ptrdiff_t dwPlayerPawn = 0x7BC; //m_hPlayerPawn client.dll.rs
    std::ptrdiff_t dwSanitizedName = 0x720;
    std::ptrdiff_t m_bDormant = 0xE7;
    std::ptrdiff_t m_iTeamNum = 0x3bf;
    std::ptrdiff_t m_vecOrigin = 0x1214; //m_vOldOrigin client.dll.rs
    std::ptrdiff_t m_iHealth = 0x32C; //m_iHealth client.dll.rs
    std::ptrdiff_t forceJump = 0x169E360; //m_iHealth client.dll.rs
    std::ptrdiff_t  m_flDetectedByEnemySensorTime = 0x13C4;
    std::ptrdiff_t   m_ArmorValue = 0x14F0;
    std::ptrdiff_t   m_iCompetitiveWins = 0x744;
}

namespace Settings
{
    bool bMenu = true;
    bool bAimbot = true;
    bool bVisuals = true;
    bool bMisc = true;
    bool bConfig = true;
    namespace aimbot 
    {
        bool aimbot = false;
        inline float aim_fov = 0.0f;
        inline float smooth = 0.0f;
        inline float trigger_delay = 0.0f;
        float rcsX = 0.0f;
        float rcsY = 0.0f;
        int startbullet = 0;
        bool fov_circle = false;
        bool crosshair = false;
        bool triggerbot = false;
        inline  int selectedhitbox = 0;
        inline  const char* hitbox[] = { ("head") ,("neck"), ("cock") };



    };
    namespace rage_aimbot {

    }
    namespace Visuals
    {
        int boxMode = 0;
         bool bSnaplines = false;
         bool bDistance = false;
         bool bBox = true;
         bool bHealth = false;
         bool headcircle = false;
         bool bones = false;
         bool glow = false;
         bool distance = false;
         bool armor = false;
         bool names = false;
         bool noflash = false;
         bool chams = false;
         bool ragdoll = false;
         bool nightmode = false;
         bool nohands = false;
         bool noSmoke = false;
    

         bool box = false;
         inline  int healthtype = 0;
         inline  const char* healtht[] = { ("text") ,("bar"), ("both") };

         static const char* boxStyle[] =
         {
             "off",
             "box",
             "corner",
             "filled",
         };

         float BoxWidth = 1.0f;
    }
    namespace misc {
        bool bhop = false;
        bool radar = false;
        bool save_fps = false;
        bool water = false;
        bool fovChanger = false;
        bool spectators = false;
        bool hitsound = false;
        bool viewmodleChanger = false;

        inline float x = 0.0f;
        inline float y = 0.0f;
        inline float z = 0.0f;


        inline float fov = 0.0f;

    }
}

