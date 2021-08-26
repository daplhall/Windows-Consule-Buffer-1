#include "Canva.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
// CLASS
wCanva::wCanva(){}
wCanva::wCanva(short width, short height){
    CreateScreen(width, height);
}
wCanva::~wCanva(){
    SetConsoleActiveScreenBuffer(m_hOriginalConsole);
    delete[] m_Screen;
}
/* Reference
    http://cecilsunkure.blogspot.com/2011/11/windows-console-game-writing-to-console.html
    https://stackoverflow.com/questions/38343232/outputs-in-console-with-writeconsoleoutputa
*/
/*
@param : width : short
    - Width of the console window
@param : height : short
    - Height of the console window -- if too high window becomes small/inverted

This function creates a new windows console with a buffer size equal to the 
screen size. This means that you cant write outside the console

For furthere reference--
To set the screen buffer size we need to first have an existing screen size
hence why we set the window to {0,0,1,1}, then set the screen buffer size
, then again set the console size, but this time at the correct values.

If this doensøt happen then the buffer will have its length but will not 
form fit into the consle, eg like resizing it when it is already open.
*/
int wCanva::CreateScreen(short width, short height){    
    m_EngineActive        = true;
    m_ScreenWidth         = width;
    m_ScreenHeight        = height;
    m_ScreenArrayLength   = width*height;
    COORD coord           = {m_ScreenWidth, m_ScreenHeight};
    m_rectWindow = { 0, 0, 1, 1};
    // Neeed to check if mScreen exist.
    if (m_Screen){ delete[] m_Screen; } // If not NULL/0 then delete m_Screen, Saftey net for call create mutliple times
    m_Screen              = new CHAR_INFO[m_ScreenArrayLength];
    m_hConsole            = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(m_hConsole, true, &m_rectWindow);
    if (!SetConsoleScreenBufferSize(m_hConsole, coord)){
        std::cout << "create screen : Buffer Size Error" << std::endl;
        return 1;
    }
    if (!SetConsoleActiveScreenBuffer(m_hConsole)){
        std::cout << "create screen : Active Buffer Error" << std::endl;
        return 1;
    }
    m_rectWindow = {0 ,0, m_ScreenWidth - 1, m_ScreenHeight - 1};
    SetConsoleWindowInfo(m_hConsole, true, &m_rectWindow);
    return 0;
}
int wCanva::TestCanva(){
    for (int i = 0; i < m_ScreenArrayLength; i++){
        m_Screen[i].Char.UnicodeChar = 0xDB; //'0' + i%10;
        m_Screen[i].Attributes       = rand()%256;// this is the color
    }
    return 0;
}
int wCanva::Fill(int const xstart, int const ystart,short const chr = 0x2588, short const color  = 0x000F){
    
    for (int pixel = 0; pixel < m_ScreenArrayLength; pixel++){
        m_Screen[pixel].Char.UnicodeChar = chr;
        m_Screen[pixel].Attributes       = color;
    }
    return 0;
}
void wCanva::Start(){
    m_EngineActive = true;
    std::thread t  = std::thread(&wCanva::RunThread, this);
    // Why actually have a thread of execution here?
    t.join();
}
void wCanva::RunThread(){
    //User Initilize
    if (!UserInit()) {m_EngineActive = false;}

    auto timestamp_prev = std::chrono::system_clock::now();
    auto timestamp_curr = std::chrono::system_clock::now();
    wchar_t title[256];
    // add keys later.
    while(m_EngineActive){
        timestamp_curr = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedtime = timestamp_curr - timestamp_prev;
        timestamp_prev = timestamp_curr;
        float dt = elapsedtime.count();
        if (!UserTick(dt))
        {
            m_EngineActive = false;
            break;
        }
        swprintf(title, 256, L"wCanva Graphics - FPS: %3.2f -- dt: %.3f s", 1.0f/dt, dt ); // Frame over second
        SetConsoleTitleW(title);
        WriteConsoleOutput(m_hConsole, m_Screen, { m_ScreenWidth, m_ScreenHeight }, { 0,0 }, &m_rectWindow);
        /*
        WriteConsoleOutput is the limit on fps it seems, with out it we reach  ~20K frames
        Else we hower around 160 ish frames. This is then the benchmark.
        It seems that the more colors and such there is the less frames.
        Fill with all white boxes are 1000 frames
        */
    }

    if (!UserClean()) {}

}