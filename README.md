
# IoMon

Monitoring NtCreateFile Calls On DLLs To Find Possible Dll Hijacking Vulnerabilities.


## Technical Explanation

Alot of applications nowadays will check if a specific file in a specific directory exists, Whether that be a configuration file or an executable file or a **DLL** file, These checks are done by using **CreateFileA** / **CreateFileW** which all come down to the NTAPI function of **NtCreateFile**, IoMon will hook NtCreateFile and check for file names ending with **.dll**, Then will show you the file's **IoStatusBlock->Information** which indicates if the file exists or does not exist, Consult the **MSDN** documentation for more information about **NtCreateFile**.


## Resources

- [NtCreateFile - MSDN](https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntcreatefile)

- [MinHook - TsudaKageyu](https://github.com/TsudaKageyu/minhook)
