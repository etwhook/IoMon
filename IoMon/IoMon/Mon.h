#pragma once

#include<windows.h>
#include<iostream>
#include<winternl.h>
#include "../MinHook/MinHook.h"


#define PrintOkay(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__);
#define PrintFail(msg, ...) printf("[-] " msg "\n", ##__VA_ARGS__);
#define PrintInfo(msg, ...) printf("[*] " msg "\n", ##__VA_ARGS__);
#define PrintWarn(msg, ...) printf("[!] " msg "\n", ##__VA_ARGS__);

#define PrintInfoW(msg, ...) wprintf(L"[*] " msg "\n", ##__VA_ARGS__);

namespace IoMon {

	bool InitHook();
}