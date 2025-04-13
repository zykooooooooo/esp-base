#include <include.h>
#include <src/cache/index.h>
#include <src/rendering/menu/index.h>

#define BLUE    "\033[38;2;0;140;255m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

std::vector<std::string> blacklistedTitles = {
    "x32dbg", "x64dbg", "Cheat Engine", "Process Hacker", "Process Explorer",
    "IDA", "OllyDbg", "Wireshark", "PE-bear", "scylla", "ReClass", "Ghidra",
    "Immunity Debugger", "Sysinternals", "ExtremeDumper", "Fiddler",
    "dnSpy", "Hiew", "Resource Hacker", "API Monitor", "Frida", "TitanHide", "Everything", "memory viewer",
    "dotPeek", "Burp", "fiddler", "Registry Alert", "x96dbg", "file grab", "exeinfope"
};


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char windowTitle[256];
    GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));

    for (const std::string& blacklisted : blacklistedTitles) {
        if (std::string(windowTitle).find(blacklisted) != std::string::npos) {

            exit(0);
            return 0;



        }
    }
    return TRUE;
}

void CheckForBlacklistedWindows() {
    while (true) {
        EnumWindows(EnumWindowsProc, 0);
        Sleep(1);
    }
}

int main()
{
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CheckForBlacklistedWindows, NULL, 0, NULL);
	SetConsoleTitleA( "Fortnite Slotted Cheat [Kernel]" ); 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hConsole, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hConsole, dwMode);

    std::cout << "[+] Product: " << BLUE << "Fortnite Slotted" << RESET << "\n";
    std::cout << "[+] Status: " << GREEN << "Undetected" << RESET << "\n";

	cmd::AutoFind( );
	MessageBoxA( 0 , "open fortnite and movavi then press OK in lobby" , "" , 0 );
	cmd::process_id = cmd::FProcess( L"FortniteClient-Win64-Shipping.exe" );
	cr3 = cmd::cache_cr3( );
	virtualaddy = cmd::SimpleBase( );
	printf( "FortniteClient-Win64-Shipping.exe | 0x%llx\n" , virtualaddy, "\n" );

	std::thread( &updater::run ).detach( );

	if ( !overlay::run( ) )
	{
		std::cin.get( );
		return 0xdead;
	}
}