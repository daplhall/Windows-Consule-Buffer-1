#include "Canva.h"
#include <iostream>

// CLASS
wCanva::wCanva(){}
wCanva::wCanva(short width, short height){
    CreateScreen(width, height);
}
wCanva::~wCanva(){
    SetConsoleActiveScreenBuffer(m_hOriginalConsole);
    delete[] m_Screen;
}

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
    m_ScreenWidth  = width;
    m_ScreenHeight = height;
    m_ScreenArrayLength = width*height;

    COORD coord           = {m_ScreenWidth, m_ScreenHeight};
    SMALL_RECT rectWindow = { 0, 0, 1, 1};
    // Neeed to check if mScreen exist.
    if (m_Screen){ delete[] m_Screen; } // If not NULL/0 then delete m_Screen, Saftey net for call create mutliple times
    m_Screen              = new wchar_t[m_ScreenArrayLength];
    m_hConsole            = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(m_hConsole, true, &rectWindow);
    if (!SetConsoleScreenBufferSize(m_hConsole, coord)){
        std::cout << "create screen : Buffer Size Error" << std::endl;
        return 1;
    }
    if (!SetConsoleActiveScreenBuffer(m_hConsole)){
        std::cout << "create screen : Active Buffer Error" << std::endl;
        return 1;
    }
    rectWindow = {0 ,0, m_ScreenWidth - 1, m_ScreenHeight - 1};
    SetConsoleWindowInfo(m_hConsole, true, &rectWindow);
    return 0;
}
int wCanva::TestCanva(){
    DWORD dwByteWritten     = 0;
    int i = 0;
    for (wchar_t *ss = m_Screen, *se = m_Screen + m_ScreenArrayLength; ss != se; ss++){
        if (i > 9){
            i = 0;
        }
        *ss = '0' + i;
        i++;
    }
    WriteConsoleOutputCharacterW(m_hConsole, m_Screen, m_ScreenArrayLength, {0,0}, &dwByteWritten);
    return 0;
}