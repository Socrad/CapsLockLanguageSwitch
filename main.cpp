#include <windows.h>
#include <shellapi.h>
#include <winreg.h>
#include "resource.h"

HHOOK g_keyboardHook = NULL;
HWND g_hMainWnd = NULL;
bool g_isHookActive = true;
bool g_isRunOnStartup = false;

const WCHAR* REG_RUN_KEY = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
const WCHAR* APP_NAME = L"CapsLockLanguageSwitcher";

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CreateTrayIcon(HWND hWnd);
void RemoveTrayIcon(HWND hWnd);
void ShowContextMenu(HWND hWnd);
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

void ToggleStartupRegistration();
bool IsAppInStartup();

void CreateTrayIcon(HWND hWnd) {
    NOTIFYICONDATA nid = {};
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hWnd;
    nid.uID = ID_TRAY_ICON;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAY_ICON_MSG; // 이 메시지를 통해 아이콘 이벤트를 받음

    nid.hIcon = (HICON)LoadImage(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(IDI_APPICON),
        IMAGE_ICON,
        GetSystemMetrics(SM_CXSMICON),
        GetSystemMetrics(SM_CYSMICON),
        LR_DEFAULTCOLOR
    );

    wcscpy_s(nid.szTip, L"CapsLock 한/영 전환");

    Shell_NotifyIcon(NIM_ADD, &nid);
}

void RemoveTrayIcon(HWND hWnd) {
    NOTIFYICONDATA nid = {};
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hWnd;
    nid.uID = ID_TRAY_ICON;
    Shell_NotifyIcon(NIM_DELETE, &nid);
}

void ShowContextMenu(HWND hWnd) {
    POINT pt;
    GetCursorPos(&pt); // 현재 마우스 커서 위치를 가져옴

    HMENU hMenu = CreatePopupMenu();
    if (hMenu) {
        UINT toggle_flags = MF_BYPOSITION | MF_STRING;
        if (g_isHookActive) {
            toggle_flags |= MF_CHECKED;
        } 
        InsertMenu(hMenu, -1, toggle_flags, ID_MENU_TOGGLE, L"작동");

        UINT startup_flags = MF_BYPOSITION | MF_STRING;
        if (g_isRunOnStartup) {
            startup_flags |=MF_CHECKED;
        }
        InsertMenu(hMenu, -1, startup_flags, ID_MENU_STARTUP, L"시작 시 실행");
        InsertMenu(hMenu, -1, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);
        InsertMenu(hMenu, -1, MF_BYPOSITION | MF_STRING, ID_MENU_EXIT, L"종료");

        SetForegroundWindow(hWnd);

        TrackPopupMenu(hMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, hWnd, NULL);
        PostMessage(hWnd, WM_NULL, 0, 0);
        DestroyMenu(hMenu);
    }
    
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (g_isHookActive && nCode == HC_ACTION) {
        if (wParam == WM_KEYUP) {
            KBDLLHOOKSTRUCT* pkbhs = (KBDLLHOOKSTRUCT*)lParam;
            if(pkbhs->vkCode == VK_CAPITAL) {
                INPUT inputs[2] = {};
                inputs[0].type = INPUT_KEYBOARD;
                inputs[0].ki.wVk = VK_HANGUL;
                inputs[0].ki.dwFlags = 0;

                inputs[1].type = INPUT_KEYBOARD;
                inputs[1].ki.wVk = VK_HANGUL;
                inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
                
                SendInput(2, inputs, sizeof(INPUT));

                return 1;
            } 
        }
    }

    if (g_isHookActive && nCode == HC_ACTION && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* pkbhs = (KBDLLHOOKSTRUCT*)lParam;
        if (pkbhs->vkCode == VK_CAPITAL) {
            return 1;
        }
    }
    return CallNextHookEx(g_keyboardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_TRAY_ICON_MSG:
            switch(lParam) {
                case WM_RBUTTONUP:
                    ShowContextMenu(hWnd);
                    break;
            }
            return 0;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_MENU_TOGGLE:
                    g_isHookActive = !g_isHookActive;
                    break;
                case ID_MENU_STARTUP:
                    ToggleStartupRegistration();
                    break;
                case ID_MENU_EXIT:
                    DestroyWindow(hWnd);
                    break;
            }
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool IsAppInStartup() {
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_CURRENT_USER, REG_RUN_KEY, 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        return false;
    }

    WCHAR szPath[MAX_PATH];
    DWORD dwSize = sizeof(szPath);
    bool bResult = (RegQueryValueEx(hKey, APP_NAME, NULL, NULL, (LPBYTE)szPath, &dwSize) == ERROR_SUCCESS);

    RegCloseKey(hKey);
    return bResult;
}

void ToggleStartupRegistration() {
    g_isRunOnStartup = !g_isRunOnStartup;

    HKEY hKey;
    if (RegOpenKeyEx(HKEY_CURRENT_USER, REG_RUN_KEY, 0, KEY_WRITE, &hKey) != ERROR_SUCCESS) {
        return;
    }

    if (g_isRunOnStartup) {
        WCHAR szPath[MAX_PATH];
        GetModuleFileName(NULL, szPath, MAX_PATH);
        RegSetValueEx(hKey, APP_NAME, 0, REG_SZ, (LPBYTE)szPath, (wcslen(szPath) + 1) * sizeof(WCHAR));
    } else {
        RegDeleteValue(hKey, APP_NAME);
    }

    RegCloseKey(hKey);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const WCHAR CLASS_NAME[] = L"CapsLock Language Switcher Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    g_hMainWnd = CreateWindowEx(
        0, 
        CLASS_NAME, 
        L"CapsLock Language Switcher", 
        WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
        NULL, 
        NULL, 
        hInstance, 
        NULL);

    if (g_hMainWnd == NULL) {
        return 0;
    }

    g_isRunOnStartup = IsAppInStartup();

    g_keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInstance, 0); // 0: 전역 훅(모든 스레드에 적용)을 의미.

    CreateTrayIcon(g_hMainWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(g_keyboardHook);
    RemoveTrayIcon(g_hMainWnd);
    
    return (int)msg.wParam;
}