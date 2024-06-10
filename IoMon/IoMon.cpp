#include<windows.h>
#include<iostream>
#include "./IoMon/Mon.h"

VOID InitConsole() {
    FILE* conOut;
    AllocConsole();
    SetConsoleTitleA("IoMon");
    freopen_s(&conOut, "CONOUT$", "w", stdout);
    
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  
    DWORD fdwReason,     
    LPVOID lpvReserved)
{

    if (fdwReason == DLL_PROCESS_ATTACH) {
        
        InitConsole();
        PrintInfo("IoMon Initializing...");
        IoMon::InitHook();
    }
    else if (fdwReason == DLL_PROCESS_DETACH) {
        FreeConsole();
    }
   
    return TRUE;
}