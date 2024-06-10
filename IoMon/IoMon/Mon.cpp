#include "Mon.h"

typedef NTSTATUS (NTAPI* t_NtCreateFile) (
	PHANDLE FileHandle,
	ACCESS_MASK DesiredAccess,
	POBJECT_ATTRIBUTES ObjectAttributes,
	PIO_STATUS_BLOCK IoStatusBlock,
	PLARGE_INTEGER AllocationSize,
	ULONG FileAttributes,
	ULONG ShareAccess,
	ULONG CreateDisposition,
	ULONG CreateOptions,
	PVOID EaBuffer,
	ULONG EaLength
);
t_NtCreateFile orgNtCreateFile;

NTSTATUS NtCreateFileDetour(
	PHANDLE FileHandle,
	ACCESS_MASK DesiredAccess,
	POBJECT_ATTRIBUTES ObjectAttributes,
	PIO_STATUS_BLOCK IoStatusBlock,
	PLARGE_INTEGER AllocationSize,
	ULONG FileAttributes,
	ULONG ShareAccess,
	ULONG CreateDisposition,
	ULONG CreateOptions,
	PVOID EaBuffer,
	ULONG EaLength
) {
	PUNICODE_STRING fileName = ObjectAttributes->ObjectName;
	
	std::wstring wFileName = std::wstring(fileName->Buffer);
	std::wstring fileExtension = wFileName.substr(wFileName.length() - 3, wFileName.length() - 1);

	NTSTATUS createFileStatus = orgNtCreateFile(FileHandle, DesiredAccess, ObjectAttributes, IoStatusBlock, AllocationSize, FileAttributes, ShareAccess, CreateDisposition, CreateOptions, EaBuffer, EaLength);

	if (fileExtension.compare(L"dll") == 0) {
		PrintInfoW(L"NtCreateFile Call On Dll [ %ls ] [ 0x%x ]", fileName->Buffer, IoStatusBlock->Information);
	}
	
	return createFileStatus;
}

bool IoMon::InitHook() {

	if (MH_Initialize() != MH_OK) {
		PrintFail("Failed To Initialize MinHook.");
		return false;
	}
	PrintOkay("MinHook Initialized Successfully.");

	if (MH_CreateHookApi(L"NTDLL", "NtCreateFile", NtCreateFileDetour, (PVOID*)&orgNtCreateFile) != MH_OK) {
		PrintFail("Failed To Create NtCreateFile Hook.");
		return false;
	}

	PrintOkay("Created NtCreateFile Hook Successfully.");


	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
		PrintFail("Failed To Enable Hooks.");
		return false;
	}

	PrintOkay("Enabled Hook Successfully.");

	return true;
}