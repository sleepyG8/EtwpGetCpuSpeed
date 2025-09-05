#include <Windows.h>
#include <stdio.h>

int main() {

    HANDLE hNtdll = GetModuleHandle("ntdll.dll");

    typedef ULONG (NTAPI *EtwpGetCpuSpeed_t)(PULONG, PULONG);

    EtwpGetCpuSpeed_t speed = (EtwpGetCpuSpeed_t)GetProcAddress(hNtdll, "EtwpGetCpuSpeed");

    if (!speed) {
        perror("error\n");
        return 0;
    }


    // After dumping the raw data at the function address I discovered that this triggeres a TEB walk internally
    
    ULONG num;
    DWORD check;
    
    speed(&num, &check);

    printf("CPU Speed: %.3f GHz\n", num / 1000.0);

    if (check == 231) {
    printf("check: %lu - Running\n", check);
    } else if (check == 0) {
    printf("check: %lu\n - OK", check);
    } else {
    printf("check: %lu\n - STATUS", check);
    }
    

    return 0;

}
