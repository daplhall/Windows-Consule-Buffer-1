#include <windows.h>
#include <iostream>
// https://gamedev.stackexchange.com/questions/162455/native-c-console-screen-buffer

void screenTest(wchar_t *screen, int const length)
{
    for (wchar_t *ss = screen, *se = screen + length; ss != se; ss++)
    {
        *ss = '#';
    }
}

int main(int argc, char *argv[]){
    int ScreenWidth  = 120;
    int ScreenHeight = 30;
    int ScreenArrayLength = ScreenHeight*ScreenWidth;
    int a;
    wchar_t *screen = new wchar_t[ScreenArrayLength]; // 80*30 must be width and hight?
    HANDLE hconsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0 ,
                                    NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hconsole); // sets the active console to hconsole
    DWORD dwByteWritten = 0;
    //screen[0] = '+';
    //screen[ScreenArrayLength - 1] = '-'; // "" creates a constant char*  '' doesn't \0 is an empty space
    screenTest(screen, ScreenArrayLength);
    WriteConsoleOutputCharacterW(hconsole, screen, ScreenArrayLength, {0,0}, &dwByteWritten);
    std::cin>>a;
    return 0;
}