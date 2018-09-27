#include"Window.h"


void Load();
void Unload();


void main()
{
    Window GameWindow(0,0,640,480, "GameWindow");
    Load();

    while(GameWindow.LOOP_GAME())
    {
    }

    Unload();
}


void Load()
{
}

void Unload()
{
}