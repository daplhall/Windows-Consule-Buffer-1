#ifndef H_WINDOWS_CANVAS_H
#define H_WINDOWS_CANVAS_H
#include <windows.h>
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

class wCanva{
      protected:
            HANDLE   m_hConsole, m_hOriginalConsole;
            short    m_ScreenHeight;
            short    m_ScreenWidth;
            int      m_ScreenArrayLength;
            wchar_t *m_Screen = NULL; // NULL = const 0. This is set to NULL (0), such that we can check if the pointer is empty 
      public:
            wCanva();
            wCanva(short width, short height);
            ~wCanva();
            int CreateScreen(short width, short height); // Also need one for font size.
            int TestCanva();
};

#endif