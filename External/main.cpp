#include <Windows.h>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <winbase.h>
#include <tchar.h>
#include <WinInet.h>
#include "Main.h"
#include "includes.h" // Assuming includes.h contains necessary function declarations
#include "proc.h"
#include <chrono>
#include <thread>

#pragma comment(lib,"Wininet.lib")
#pragma comment(lib, "winmm.lib")

namespace Variables {
    int ActiveTab = 1;
}

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    DWORD pID, baseModule, localPlayerPtr;
    int health = 6969;
    int highscore = 9999999999;
    int rifleammo = 123;
    int riflemag = 69;
    int pistolammo = 9;
    int pistolmag = 69;
    int grenade = 10;
    int armour = 69;
    int sniperammo = 21;
    int rapidknife = 1;
    int rapidf = 1;
    int fullbright = 1;
    int nojump = 5;
    float fov = 90.0f;
    int name = 2234;
    float fly_height = 10.0f;    
    float max_fly_height = 100.0f;
    float defaultSpeed = 100.0f; // Example default player speed
    float speedMultiplier = 2.0f; // Example speed multiplier


    pID = GetProcessID("ac_client.exe");
    baseModule = GetModuleBaseAddress(pID, "ac_client.exe");
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, pID);
    ReadProcessMemory(handle, (LPCVOID)(baseModule + 0x17E0A8), &localPlayerPtr, sizeof(localPlayerPtr), nullptr);

    // Set up ImGui and DirectX environment as per the first snippet
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, LOADER_BRAND, NULL };
    RegisterClassEx(&wc);
    HWND main_hwnd = CreateWindow(wc.lpszClassName, LOADER_BRAND, WS_POPUP, 0, 0, 5, 5, NULL, NULL, wc.hInstance, NULL);

    if (!CreateDeviceD3D(main_hwnd)) {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(main_hwnd, SW_HIDE);
    UpdateWindow(main_hwnd);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    // Apply your ImGui style settings here

    ImGui_ImplWin32_Init(main_hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    DWORD window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

    RECT screen_rect;
    GetWindowRect(GetDesktopWindow(), &screen_rect);
    auto screenwidth = float(screen_rect.right - WINDOW_WIDTH) / 2.f;
    auto screenheight = float(screen_rect.bottom - WINDOW_HEIGHT) / 2.f;

    bool toggle_inf_ammo = false;
    bool toggle_inf_ammo2 = false;
    bool toggle_pistol_mag = false;
    bool toggle_rifle_mag = false;
    bool toggle_inf_health = false;
    bool toggle_inf_armor = false;
    bool toggle_rapid_fire = false;
    bool toggle_inst_knife = false;
    bool toggle_inf_grenade = false;
    bool toggle_high_score = false;
    bool toggle_full_bright = false;
    bool toggle_nojump = false;
    bool toggle_fov = false;
    bool toggle_flyhack = false;
    bool toggle_speedHack = false;


    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        // Update memory values based on ImGui toggles
        if (toggle_inf_ammo)
        {
            int inf_ammo_value = 1; // Example value for infinite ammo
            WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x140), &inf_ammo_value, sizeof(inf_ammo_value), nullptr);
            WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x12C), &pistolammo, sizeof(pistolammo), nullptr);
            WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x13C), &sniperammo, sizeof(sniperammo), nullptr);
        }
        else
        {
            int normal_ammo_value = 0;
        }
        if (toggle_rifle_mag)
        {
            int inf_rifle_mag = 1;
            WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x11C), &riflemag, sizeof(riflemag), nullptr);
        }
        else
        {
            int normal_rifle_mag_value = 0;
        }
        if (toggle_pistol_mag)
        {
            int inf_pistol_mag_value = 1; // Example value for infinite pistol mag
            WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x108), &inf_pistol_mag_value, sizeof(inf_pistol_mag_value), nullptr);
        }
        else
        {
            int normal_pistol_mag_value = 0;
        }

        if (toggle_inf_health)
        {
            int inf_health_value = 999; // Example value for infinite pistol mag
            WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0xEC), &inf_health_value, sizeof(inf_health_value), nullptr);
        }
        else
        {
            int normal_health_value = 100;
        }

        if (toggle_inf_armor)
        {
            WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0xF0), &armour, sizeof(armour), nullptr);
        }

        if (toggle_rapid_fire)
        {
            WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x1EC), &rapidf, sizeof(rapidf), nullptr);
        }
        if (toggle_inst_knife)
        {
            WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x14C), &rapidknife, sizeof(rapidknife), nullptr);
        }

        if (toggle_inf_grenade)
        {
            WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x144), &grenade, sizeof(grenade), nullptr);
        }

        if (toggle_high_score)
        {
            WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x1DC), &highscore, sizeof(highscore), nullptr);
        }
        
        if (toggle_nojump)
        {
            WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x1B), &nojump, sizeof(nojump), nullptr);
        }

        if (toggle_fov)
        {
            float fov_value = fov;
            SIZE_T bytesWritten;
            BOOL result = WriteProcessMemory(handle, (LPVOID)(baseModule + 0x18A7CC), &fov_value, sizeof(fov_value), &bytesWritten);
            if (!result || bytesWritten != sizeof(fov_value))
            {
                // Handle error: failed to write memory
                // Example: Output an error message or log the failure
                std::cout << "Failed to write FOV value." << std::endl;
            }
        }

        //flyhack
        if (toggle_flyhack)
        {
            float currentZ;
            ReadProcessMemory(handle, (LPCVOID)(localPlayerPtr + 0x30), &currentZ, sizeof(currentZ), nullptr); // Assuming 0x30 is the correct offset for Z-coordinate

            // Adjust height based on controls
            currentZ += fly_height;

            // No-clip logic: Prevent dropping to the ground inside objects
            float groundCheckZ;
            ReadProcessMemory(handle, (LPCVOID)(localPlayerPtr + 0x34), &groundCheckZ, sizeof(groundCheckZ), nullptr); // Adjust this offset as needed
            if (currentZ < groundCheckZ) // If currentZ goes below groundCheckZ, adjust it to groundCheckZ
            {
                currentZ = groundCheckZ;
            }

            // Cap maximum height
            if (currentZ > max_fly_height)
                currentZ = max_fly_height;

            WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x30), &currentZ, sizeof(currentZ), nullptr); // Write the modified Z-coordinate
        }

        if (toggle_speedHack)
        {
            // Read current player speed from memory
            float currentSpeed;
            ReadProcessMemory(handle, (LPCVOID)(localPlayerPtr + 0x81), &currentSpeed, sizeof(currentSpeed), nullptr);

            // Modify the speed value (increase by multiplier)
            float newSpeed = currentSpeed * speedMultiplier;

            // Write the modified speed value back to memory
            WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x81), &newSpeed, sizeof(newSpeed), nullptr);
        }


        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // ImGui GUI setup as per the first snippet
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 5.0f;
        style.FrameRounding = 4.0f;
        style.WindowPadding = ImVec2(8, 8);
        style.FramePadding = ImVec2(4, 4);
        ImGui::StyleColorsDark();
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(600, 450));
        ImGui::SetNextWindowBgAlpha(1.0f);
        ImGui::Begin("External", &loader_active, window_flags);
        {
            if (ImGui::Checkbox("##InfiniteAmmo", &toggle_inf_ammo))
            {
                // Toggle or set state for infinite ammo
            }
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.678f, 0.847f, 0.902f, 1.0f), "Infinite ammo");

            // Add similar ImGui elements for other options
            if (ImGui::Checkbox("##Rifle Mag", &toggle_rifle_mag))
            {
                // Toggle or set state for pistol mag
            }
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.678f, 0.847f, 0.902f, 1.0f), "Rifle Mag");

            if (ImGui::Checkbox("##Pistol Mag", &toggle_pistol_mag))
            {
                // Toggle or set state for pistol mag
            }
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.678f, 0.847f, 0.902f, 1.0f), "Pistol Mag");

            if (ImGui::Checkbox("##Godmode", &toggle_inf_health))
            {
                // Toggle or set state for pistol mag
            }
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.678f, 0.847f, 0.902f, 1.0f), "Godmode");

            if (ImGui::Checkbox("##Armor", &toggle_inf_armor))
            {
                // Toggle or set state for pistol mag
            }
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.678f, 0.847f, 0.902f, 1.0f), "Armor");

            if (ImGui::Checkbox("##Rapid Fire", &toggle_rapid_fire))
            {
                // Toggle or set state for pistol mag
            }
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.678f, 0.847f, 0.902f, 1.0f), "Rapid Fire");

            if (ImGui::Checkbox("##Instant Knife", &toggle_inst_knife))
            {
                // Toggle or set state for pistol mag
            }
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.678f, 0.847f, 0.902f, 1.0f), "Instant Knife");

            if (ImGui::Checkbox("##Infinite Grenade", &toggle_inf_grenade))
            {
                // Toggle or set state for pistol mag
            }
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.678f, 0.847f, 0.902f, 1.0f), "Infinite Grenade");

            if (ImGui::Checkbox("##High Score", &toggle_high_score))
            {
                // Toggle or set state for pistol mag
            }
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.678f, 0.847f, 0.902f, 1.0f), "High Score");

            if (ImGui::Checkbox("##No Jump", &toggle_nojump))
            {
                // Toggle or set state for pistol mag
            }
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.678f, 0.847f, 0.902f, 1.0f), "No Jump");
            
            ImGui::Checkbox("##FOV", &toggle_fov);
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.678f, 0.847f, 0.902f, 1.0f), "FOV");

            if (toggle_fov)
            {
                ImGui::SliderFloat("##FOVSlide", &fov, 75.0f, 175.0f);
                ImGui::SameLine();
                if (ImGui::Button("Default"))
                {
                    fov = 90.0f; // Set FOV to default value (90.0)
                }
            }

            if (ImGui::Checkbox("##FlyHack", &toggle_flyhack));
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.678f, 0.847f, 0.902f, 1.0f), "Fly Hack");

            ImGui::SliderFloat("Max Flying Height", &max_fly_height, 1.0f, 500.0f);

            if (ImGui::Checkbox("##Speed", &toggle_speedHack))
            {
                // Toggle or set state for pistol mag
            }
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.678f, 0.847f, 0.902f, 1.0f), "Speed");

        }
        ImGui::End();

        ImGui::EndFrame();

        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            ResetDevice();
        }
        if (!loader_active) {
            msg.message = WM_QUIT;
        }
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    DestroyWindow(main_hwnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}