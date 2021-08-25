#include <windows.h>
#include <iostream>
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


void screenTest(wchar_t *screen, int const length)
{
    int i = 0;
    for (wchar_t *ss = screen, *se = screen + length; ss != se; ss++)
    {
        if (i > 9){
            i = 0;
        }
        *ss = '0' + i;
        i++;
    }
}

void screenTest1(wchar_t *screen, int const length){
    for (wchar_t *ss = screen, *se = screen + length; ss != se; ss++){
        *ss = '#';
    }
}

int main(int argc, char *argv[]){
    int a,b;
    short ScreenHeight      = 20;
    short ScreenWidth       = 20;
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