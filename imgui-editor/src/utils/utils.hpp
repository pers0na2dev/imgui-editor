#pragma once

#include <windows.h>
#include <filesystem>

#include "../layerSystem/layerSystem.hpp"
#include "../projects/projectSystem.hpp"
#include "../context.hpp"

namespace utils {
    inline LSTATUS result;
    inline BYTE databuffer[256];

    inline void EnumerateValues(HKEY hKey, DWORD numValues)
    {
        DWORD dwIndex = 0;
        LPSTR valueName = new CHAR[256];
        DWORD valNameLen;
        DWORD dataType;
        BYTE* data = databuffer;
        DWORD dataSize = 1024;

        for (int i = 0; i < numValues; i++)
        {
            DWORD valNameLen = 256;
            dataSize = 256;
            dataType = 0;
            result = RegEnumValue(hKey, dwIndex, valueName, &valNameLen, NULL, &dataType, data, &dataSize);

            if (std::filesystem::path((const char*)data).extension() == ".ttf" ||
                std::filesystem::path((const char*)data).extension() == ".otf")
            {
                gLayerSystem->systemFonts.push_back(systemFont{
                    .name = (std::string)valueName,
                    .file = (const char*)data,
                    });
            }
            dwIndex++;
        }
    }

    inline void EnumerateSubKeys(HKEY RootKey, const char* subKey, unsigned int tabs = 0)
    {
        HKEY hKey;
        DWORD cSubKeys;
        DWORD maxSubkeyLen;
        DWORD cValues;
        DWORD maxValueLen;
        DWORD retCode;

        result = RegOpenKeyEx(RootKey, subKey, 0, KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_READ, &hKey);

        if (result != ERROR_SUCCESS) return;

        result = RegQueryInfoKey(hKey, NULL, NULL, NULL, &cSubKeys, &maxSubkeyLen, NULL, &cValues, &maxValueLen, NULL, NULL, NULL);

        if (result != ERROR_SUCCESS) return;

        if (cSubKeys > 0)
        {
            char currentSubkey[MAX_PATH];
            for (int i = 0; i < cSubKeys; i++)
            {
                DWORD currentSubLen = MAX_PATH;

                retCode = RegEnumKeyEx(hKey, i, currentSubkey, &currentSubLen, NULL, NULL, NULL, NULL);

                if (retCode == ERROR_SUCCESS)
                {
                    char* subKeyPath = new char[currentSubLen + strlen(subKey)];
                    sprintf(subKeyPath, "%s\\%s", subKey, currentSubkey);
                    EnumerateSubKeys(RootKey, subKeyPath, (tabs + 1));
                }
            }
        }
        else
            EnumerateValues(hKey, cValues);

        RegCloseKey(hKey);
    }

    inline bool GetImageSizeEx(const char* fn, int* x, int* y)
    {
        FILE* f;
        fopen_s(&f, fn, "rb");

        if (f == 0) return false;

        fseek(f, 0, SEEK_END);
        long len = ftell(f);
        fseek(f, 0, SEEK_SET);

        if (len < 24) {
            fclose(f);
            return false;
        }

        unsigned char buf[24]; fread(buf, 1, 24, f);

        if (buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF && buf[3] == 0xE0 && buf[6] == 'J' && buf[7] == 'F' && buf[8] == 'I' && buf[9] == 'F')
        {
            long pos = 2;
            while (buf[2] == 0xFF)
            {
                if (buf[3] == 0xC0 || buf[3] == 0xC1 || buf[3] == 0xC2 || buf[3] == 0xC3 || buf[3] == 0xC9 || buf[3] == 0xCA || buf[3] == 0xCB)
                    break;

                pos += 2 + (buf[4] << 8) + buf[5];
                if (pos + 12 > len) break;
                fseek(f, pos, SEEK_SET);
                fread(buf + 2, 1, 12, f);
            }
        }

        fclose(f);

        if (buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF)
        {
            *y = (buf[7] << 8) + buf[8];
            *x = (buf[9] << 8) + buf[10];

            return true;
        }


        if (buf[0] == 'G' && buf[1] == 'I' && buf[2] == 'F')
        {
            *x = buf[6] + (buf[7] << 8);
            *y = buf[8] + (buf[9] << 8);
            return true;
        }

        if (buf[0] == 0x89 && buf[1] == 'P' && buf[2] == 'N' && buf[3] == 'G' && buf[4] == 0x0D && buf[5] == 0x0A && buf[6] == 0x1A && buf[7] == 0x0A && buf[12] == 'I' && buf[13] == 'H' && buf[14] == 'D' && buf[15] == 'R')
        {
            *x = (buf[16] << 24) + (buf[17] << 16) + (buf[18] << 8) + (buf[19] << 0);
            *y = (buf[20] << 24) + (buf[21] << 16) + (buf[22] << 8) + (buf[23] << 0);

            return true;
        }

        return false;
    }

    inline std::string genName(const int len) {
        srand((unsigned)time(NULL) * _getpid());
        Sleep(1);

        static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        std::string tmp_s;
        tmp_s.reserve(len);

        for (int i = 0; i < len; ++i) {
            tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
        }

        return tmp_s;
    }

    inline void RenderMiniRect(ImVec2 pos) {
        ImGui::GetForegroundDrawList()->AddRectFilled(
            gContext.RenderPos + gContext.ScaleM(pos) - ImVec2(5, 5),
            gContext.RenderPos + gContext.ScaleM(pos) + ImVec2(5, 5),
            ImColor(255, 255, 255)
        );
        ImGui::GetForegroundDrawList()->AddRect(
            gContext.RenderPos + gContext.ScaleM(pos) - ImVec2(5, 5),
            gContext.RenderPos + gContext.ScaleM(pos) + ImVec2(5, 5),
            ImColor(0, 166, 255)
        );
    }

    inline bool HandleMiniRect(ImVec2 pos) {
        if (ImGui::IsMouseHoveringRect(
            gContext.RenderPos + gContext.ScaleM(pos) - ImVec2(5, 5) + ImGui::GetIO().MouseDelta,
            gContext.RenderPos + gContext.ScaleM(pos) + ImVec2(5, 5) + ImGui::GetIO().MouseDelta, false)
            )
        {
            gContext.InResize = true;
            return true;
        }
        else {
            gContext.InResize = false;
        }

        return false;
    }

    inline void PushSettings()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, gProjectSystem->data.window.Alpha);
        ImGui::PushStyleVar(ImGuiStyleVar_DisabledAlpha, gProjectSystem->data.window.DisabledAlpha);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, gProjectSystem->data.window.WindowRounding);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, gProjectSystem->data.window.WindowBorderSize);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, gProjectSystem->data.window.WindowMinSize);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, gProjectSystem->data.window.WindowPadding);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, gProjectSystem->data.window.WindowTitleAlign);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, gProjectSystem->data.window.ChildRounding);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, gProjectSystem->data.window.ChildBorderSize);
        ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, gProjectSystem->data.window.PopupRounding);
        ImGui::PushStyleVar(ImGuiStyleVar_PopupBorderSize, gProjectSystem->data.window.PopupBorderSize);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, gProjectSystem->data.window.FrameRounding);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, gProjectSystem->data.window.FrameBorderSize);
        ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, gProjectSystem->data.window.IndentSpacing);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, gProjectSystem->data.window.ItemSpacing);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, gProjectSystem->data.window.ItemInnerSpacing);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, gProjectSystem->data.window.FramePadding);
    }

    inline void PushWidgetSettings()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.f);
        ImGui::PushStyleVar(ImGuiStyleVar_DisabledAlpha, 1.f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, {10, 10});
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
        ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, gProjectSystem->data.window.WindowTitleAlign);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, gProjectSystem->data.window.ChildRounding);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, gProjectSystem->data.window.ChildBorderSize);
        ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, gProjectSystem->data.window.PopupRounding);
        ImGui::PushStyleVar(ImGuiStyleVar_PopupBorderSize, gProjectSystem->data.window.PopupBorderSize);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, gProjectSystem->data.window.FrameRounding);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, gProjectSystem->data.window.FrameBorderSize);
        ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, gProjectSystem->data.window.IndentSpacing);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, gProjectSystem->data.window.ItemSpacing);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, gProjectSystem->data.window.ItemInnerSpacing);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, gProjectSystem->data.window.FramePadding);
    }
}