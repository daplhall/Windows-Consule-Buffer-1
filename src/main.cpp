#include <windows.h>
#include <iostream>
#include "Canva.h"



int main(int argc, char *argv[]){
    int a;
    wCanva canva;
    canva.CreateScreen(120,40);
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