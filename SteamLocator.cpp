#include <iostream>
#include <windows.h>
#include <string>

// Function to automatically locate the Steam installation path via Windows Registry
std::wstring GetSteamInstallPath() {
    HKEY hKey;
    LONG lRes = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Valve\\Steam", 0, KEY_READ, &hKey);
    
    if (lRes != ERROR_SUCCESS) {
        return L"";
    }

    wchar_t szBuffer[512];
    DWORD dwBufferSize = sizeof(szBuffer);
    ULONG nError = RegQueryValueExW(hKey, L"SteamPath", 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
    
    RegCloseKey(hKey);

    if (nError == ERROR_SUCCESS) {
        return std::wstring(szBuffer);
    }

    return L"";
}

int main() {
    std::wcout << L"=== Fatekeeper Reborn Core Utilities ===" << std::endl;
    std::wcout << L"Scanning system configuration..." << std::endl;

    std::wstring steamPath = GetSteamInstallPath();

    if (!steamPath.empty()) {
        std::wcout << L"[SUCCESS] Steam directory located at: " << steamPath << std::endl;
        std::wcout << L"[INFO] Common apps directory: " << steamPath << L"/steamapps/common/" << std::endl;
    } else {
        std::wcout << L"[ERROR] Steam installation not found in registry." << std::endl;
    }

    return 0;
}
