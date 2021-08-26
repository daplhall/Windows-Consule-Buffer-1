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
#include <random>

class canvas : public wCanva
{
    bool UserInit() override{   
        return true;
    }
    bool UserClean() override{
        return true;
    }

    bool UserTick(float dt) override{
        return true;
    }
};


int main(int argc, char *argv[]){
    int a;
    canvas canva;
    if (canva.CreateScreen(120,40)){ return 1; }
    //canva.TestCanva();
    canva.Fill(0xDB, rand()%256);
    canva.RunThread();
    std::cin >> a;
    return 0;
}