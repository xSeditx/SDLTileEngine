#include"Window.h"
#include"World.h"
#include"Sprite.h"




void Load();
void Unload();

World *GW;

bool KD = false;

void KeyDown(Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier, Uint8 rep)                                                    //(SDL_Keysym sym, int mod, Uint16 unicode);
{
	KD = true;
}
void KeyUp(Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier)
{
	if(ScanCode != SDL_SCANCODE_SPACE)KD = false;
}

void main()
{
    Window GameWindow(0, 0, SCREENWIDTH, SCREENHEIGHT, "GameWindow");
	GameWindow.Set_Sync_rate(60);
	GameWindow.CallBacks.SetOnKeyDown(KeyDown);
	GameWindow.CallBacks.SetOnKeyUp(KeyUp);
	Load();

	World  GameWorld(Vec2(100, 50));
	GW = &GameWorld;

    while(GameWindow.LOOP_GAME())
    {
		GameWindow.CLS(0);
		    GameWorld.Update();

			if (KD == true)
			{
//			if (SCREEN->Keyboard.KeyState[SDL_SCANCODE_RIGHT] == true)
//			{
//				GW->Player1.Forward = true;
//				GW->Player1.CollisionBox->Body.Force = Vec2(1, 0);
//				GW->Player1.PlayerState = Player::Running;
//				GW->Camera.MoveRight(7);
//			}
//			if (SCREEN->Keyboard.KeyState[SDL_SCANCODE_LEFT] == true)
//			{
//				GW->Player1.Forward = false;
//				GW->Player1.CollisionBox->Body.Force = Vec2(-1, 0);
//				GW->Player1.PlayerState = Player::Running;
//				GW->Camera.MoveLeft(7);
//			}
//			if (SCREEN->Keyboard.KeyState[SDL_SCANCODE_SPACE] == true)
//			{
//				GW->Player1.PlayerState = Player::JumpCrouch;
//				GW->Player1.CollisionBox->Body.Force = Vec2(0, -20);
//			}
			}
			else
			{
				GW->Player1.PlayerState = Player::Stopped;
			}


		    GameWorld.Render();
		GameWindow.SYNC();
	//Print(SCREEN->FPS);
    }

    Unload();
}

// https://opengameart.org/content/platformer-animations

void Load()
{
	Image *TestImage = new Image("TestI", "C:\\Users\\Sedit\\Documents\\Visual Studio 2015\\Projects\\SDLTileEngine\\Assets\\TileTest.bmp");
	Image *GreyTest  = new Image("Grey", "C:\\Users\\Sedit\\Documents\\Visual Studio 2015\\Projects\\SDLTileEngine\\Assets\\TileTest.bmp");
	       GreyTest->MakeGreyScale();

    Image *Runner = new Image("Runner", "C:\\Users\\Sedit\\Documents\\Visual Studio 2015\\Projects\\SDLTileEngine\\Assets\\Platformer.bmp");

    Sprite   *TestSprite = new Sprite("TestSprite",   Image::Manager.GetAsset(0), 1);
	Sprite *PlayerSprite = new Sprite("PlayerSprite", Image::Manager.GetAsset("Runner"), 9);
	PlayerSprite->Size = Vec2(64);
	PlayerSprite->CurrentState = 0;
	PlayerSprite->AnimationSpeed = 50;

	PlayerSprite->States[0] = State(64 * 4, 0, 64, 64, 4);
	PlayerSprite->States[0] += State(0, 64, 64, 64, 4);


	PlayerSprite->States[1] = State(0, 64, 64, 64, 8);
	PlayerSprite->States[2] = State(0, 64 * 2, 64, 64, 8);
	PlayerSprite->States[3] = State(0, 64 * 3, 64, 64, 8);
	PlayerSprite->States[4] = State(0, 64 * 4, 64, 64, 8);
	PlayerSprite->States[5] = State(0, 64 * 5, 64, 64, 8);
	PlayerSprite->States[6] = State(0, 64 * 6, 64, 64, 8);
	PlayerSprite->States[7] = State(0, 64 * 7, 64, 64, 8);
	PlayerSprite->States[8] = State(0, 64 * 8, 64, 64, 1);


return;

}

void Unload()
{
}