#include"Window.h"
#include"World.h"
#include"Sprite.h"


void Load();
void Unload();


void main()
{
    Window GameWindow(0,0,1000,800, "GameWindow");



	//World  GameWorld(Vec2(100, 50));

	Load();



    while(GameWindow.LOOP_GAME())
    {
		GameWindow.CLS(0);
		  //  GameWorld.Update();
			Image::Manager.GetAsset("TestImage")->Render(Vec2(10, 10));
		    Image::Manager.GetAsset("Grey")->Render(Vec2(10, 10));
			//GameWorld.Render();
		GameWindow.SYNC();
	Print(SCREEN->FPS);
    }

    Unload();
}


void Load()
{
	Image *TestImage = new Image("TestI", "C:\\Users\\Sedit\\Documents\\Visual Studio 2015\\Projects\\SDLTileEngine\\Assets\\TileTest.bmp");
	Image *GreyTest = new Image("Grey", "C:\\Users\\Sedit\\Documents\\Visual Studio 2015\\Projects\\SDLTileEngine\\Assets\\TileTest.bmp");
	       GreyTest->MakeGreyScale();


	Sprite *TestSprite = new Sprite("TestSprite", &*Image::Manager.GetAsset(0), 1);
return;

}

void Unload()
{
}