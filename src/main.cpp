#include <windows.h>
#include <iostream>
#include "Canva.h"


// https://gamedev.stackexchange.com/questions/162455/native-c-console-screen-buffer
/*

    You can set buffer size before setting screen size
    Notes:
    This creates a new console scrren buffer and returns it,  here we can specifiy options
        CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0 , NULL, CONSOLE_TEXTMODE_BUFFER, NULL); 
    This seems to get a handle, for standard useage, likely just a default config.
        GetStdHandle(STD_OUTPUT_HANDLE) 
    This sets the active screen buffer to a wchar sequence. 
        SetConsoleActiveScreenBuffer
*/

int main(int argc, char *argv[]){
    int a;
    wCanva canva;
    if (!canva.CreateScreen(120,40)){ return 1; }
    canva.TestCanva();
    std::cin>>a;
    return 0;
}


/*
int main(int argc, char *argv[]){
    int a;
    short ScreenWidth       = 120;
    short ScreenHeight      = 40;
    int   ScreenArrayLength =  ScreenWidth*ScreenHeight;
    COORD coord             = {ScreenWidth, ScreenHeight};
    SMALL_RECT m_rectWindow = { 0, 0, 1, 1};
    DWORD dwByteWritten     = 0;
    wchar_t *screen = new wchar_t[ScreenArrayLength]; // 80*30 must be width and hight?

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(hConsole, true, &m_rectWindow); // This gives a buffer size error, but that deosn't stop the program!
    if (!SetConsoleScreenBufferSize(hConsole, coord)){
        std::cout << "Buffer size Error" << std::endl;
    }
    if (!SetConsoleActiveScreenBuffer(hConsole)){
        std::cout << "Active Buffer Error" << std::endl;    
    } // sets the active console to hConsole
    m_rectWindow = {0, 0, ScreenWidth - 1, ScreenHeight - 1};
    SetConsoleWindowInfo(hConsole, true, &m_rectWindow);
    screenTest(screen, ScreenArrayLength);
    WriteConsoleOutputCharacterW(hConsole, screen, ScreenArrayLength, {0,0}, &dwByteWritten);
    std::cin>>a;
    return 0;
}
*/