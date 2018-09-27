#pragma once

#include"C:\Users\Curt\Documents\Visual Studio 2012\Libraries\SDL_TTF\include\SDL_ttf.h"
#pragma comment(lib, "C:\\Users\\Curt\\Documents\\Visual Studio 2012\\Libraries\\SDL_TTF\\lib\\x86\\SDL2_ttf.lib")

#include"window.h"
#include<string>




/*

FONT RENDERER STARTED. NEED TO PLACE ALL THE GIVEN TEXT INTO A STD::VECTOR SO THAT i CAN ASSIGN IT ONCE 
AND SPEED UP THE FONT RENDERING PROCESS. 
CREATE STRING, 
RENDER STRING AND 
DESTROY STRING FUNCTIONS ARE NEEDED
ALSO SOME STYLE AND COLOR FUNCTIONALITY

*/


//TODO: So much shit to do here. Perhaps make a loader like I did everything else but even that has become a pain in the ass to manage 
//     even though its extremely easy.




#define OPENING_FONT 0 

class FontRender
{
public:

    FontRender(const char*file);
    FontRender(const char*file, int size);

    TTF_Font *CurrentFont;

    void FreeFont(TTF_Font *font);
    void CloseFontRender();
    void SetSize();
    void Write(float value, Vec2 pos);
    void Write(const char *text, Vec2 pos);


    void WriteShadow(const char *text, Vec2 pos, int depth);
    void WriteShadow(float value, Vec2 pos, int depth);
    void SetForgroundColor(float R, float G, float B, float A);

    int CurrentFontID;

    SDL_Color ForgroundColor, 
              BackgroundColor;
    static FontRender *Fonts;

    void   SetBackGroundColor(SDL_Color col) {BackgroundColor = col;}
    void   SetForgroundColor(SDL_Color col)  {ForgroundColor  = col;}

    float Size;
};

