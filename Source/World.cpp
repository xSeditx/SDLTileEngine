#include "..\Headers\World.h"

#include"Fonts.h"


const int WorldWidth = 100;
const int WorldHeight = 20;

int WorldData[] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,6,5,5,5,4,4,4,4,4,3,3,3,3,3,3,3,3,3,2,2,2,2,2,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,4,0,4,4,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,0,0,0,0,0,2,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5,5,7,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,0,0,0,0,0,2,0,0,2,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,0,0,0,0,0,2,0,0,2,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};


World::World(Vec2 size)
	: SizeX(size.x),
   	  SizeY(size.y)
{
	SizeX = WorldWidth;
	SizeY = WorldHeight;

	Data = new int[SizeX * SizeY];

	Player1.WorldPosition = Vec2(200, 200);
	Player1.PlayerState = 0;
	Player1.Forward = true;
	Player1.Grounded = true;
	Player1.Size = Vec2(64);
	Player1.PlayerSprite = Sprite::Manager.GetAsset("PlayerSprite");
	Player1.CollisionBox = Player1.PlayerSprite->MakeCollisionBox();

	Player1.Camera = Viewport(Player1.WorldPosition, Vec2(SCREENWIDTH, SCREENHEIGHT));

	TileSizeY = 32;
	TileSizeX = 32;

	for_loop(Index, (SizeX * SizeY))
	{
		Data[Index] =  WorldData[Index];// Data[Index] = rand() % 15; //
	}

	Tiles = TileRender(*Image::Manager.GetAsset("TestI"), 64, 64);
}

int  World::GetXY(int x, int y)
{
	return Data[x + SizeX * y];
}
int  World::WorldtoGrid(Vec2 pos)
{
	Vec2 Test(0);

	Test.x = (pos.x / (float)TileSizeX);
	Test.y = (pos.y / (float)TileSizeY);

	if (Test.x < 0) Test.x = 0;
	if (Test.x >= WorldWidth) Test.x = WorldWidth - 1;

	if (Test.y < 0) Test.y = 0;
	if (Test.y >= WorldHeight) Test.y = WorldHeight - 1;

	return GetXY((int)Test.x,
		         (int)Test.y );
}
void World::Update()
{
	Vec2 Old = Player1.WorldPosition;
	Player1.Update();
	if (isCollision(Player1.WorldPosition.x + Player1.Size.x / 2, Player1.WorldPosition.y) ||
		isCollision(Player1.WorldPosition.x - Player1.Size.x / 2, Player1.WorldPosition.y))
	{
		Player1.WorldPosition.x = Old.x;
	}

	if (isCollision(Player1.WorldPosition.x, Player1.WorldPosition.y + Player1.Size.y / 2) ||
		isCollision(Player1.WorldPosition.x, Player1.WorldPosition.y - Player1.Size.y / 2))
	{
		Player1.WorldPosition.y = Old.y;
	}
	SDL_Rect rect = { Player1.ScreenPosition.x-2, Player1.ScreenPosition.y-2, Player1.Size.x+4, Player1.Size.y +4};
	SDL_SetRenderDrawColor(SCREEN->Renderer, 255, 0, 0, 255);
	//SDL_Rect rect = { 100,100,64,64 };
	SDL_RenderDrawRect(SCREEN->Renderer, &rect);
	SDL_SetRenderDrawColor(SCREEN->Renderer, 0, 0, 0, 255);
}
void World::Render()
{
	float OffsetX = ((int)Player1.Camera.Position.x % TileSizeX);
	float OffsetY = ((int)Player1.Camera.Position.y % TileSizeY);

	float DrawX = 0 - OffsetX,
		  DrawY = 0 - OffsetY;

	for (float y = 0; y <= SCREENHEIGHT; y += TileSizeY)
	{
		for (float x = 0; x <= SCREENWIDTH; x += TileSizeX)
		{
			float positionx = ((x - OffsetX) + (Player1.Camera.Position.x));
			float positiony = ((y - OffsetY) + (Player1.Camera.Position.y));

			int TileIndex = WorldtoGrid(Vec2(positionx, positiony));

			if (TileIndex > 0)
			{
				Tiles.RenderTile(TileIndex, DrawX, DrawY);
			}
			DrawX += TileSizeX;
		}
		DrawY += TileSizeY;
		DrawX = -OffsetX;
	}
	Player1.PlayerSprite->CurrentState = Player1.PlayerState;
	Player1.Render();
}
bool World::isCollision(int x, int y)
{
	return WorldtoGrid(Vec2(x, y)) > 0;
}

Player::Player(Vec2 pos, Vec2 size)
	  : WorldPosition(pos),
	    Size(size),
	    Health(1000)
{
    PlayerState = 0;
    Forward = true;
	//Size = Vec2(64);
    Grounded = true;
    PlayerSprite = Sprite::Manager.GetAsset("PlayerSprite");
    CollisionBox = PlayerSprite->MakeCollisionBox();
}

void Player::MoveLeft(float amount)
{
	WorldPosition.x -= amount;
}
void Player::MoveRight(float amount)
{
	WorldPosition.x += amount;
}
void Player::MoveUp(float amount)
{
	WorldPosition.y -= amount;
}
void Player::MoveDown(float amount)
{
	WorldPosition.y += amount;
}
void Player::Update()
{
	if (SCREEN->Keyboard.Key.ScanCode == SDL_SCANCODE_RIGHT)
	{
		  Forward = true;
		  MoveRight(2);
		  PlayerState = Player::Running;
	}
	if (SCREEN->Keyboard.Key.ScanCode == SDL_SCANCODE_LEFT)
	{
		  Forward = false;
		  MoveLeft(2);
		  PlayerState = Player::Running;
	}
	if (SCREEN->Keyboard.Key.ScanCode == SDL_SCANCODE_DOWN)
	{
	      MoveDown(2);
		  PlayerState = Player::Running;
	}
	if (SCREEN->Keyboard.Key.ScanCode == SDL_SCANCODE_UP)
	{
		  MoveUp(2);
	  	  PlayerState = Player::Running;
	}

	if (SCREEN->Keyboard.Key.ScanCode == SDL_SCANCODE_SPACE)
    {
    	 PlayerState = Player::JumpCrouch;
    }

	Camera.CameraCenter(WorldPosition.x, WorldPosition.y);
	Camera.Update();

	Print("Player" << WorldPosition.x << " : " << WorldPosition.y);
	Print("Camera" << Camera.Position.x << " : " << Camera.Position.y);

	ScreenPosition = WorldPosition - Camera.Position;
	Body.Update();
}
void Player::Render()
{
	if (Forward == true)
	{
		PlayerSprite->Render(ScreenPosition + (Size / 2.0f));
	}
	else
	{
		PlayerSprite->Render(ScreenPosition + (Size / 2.0f), 180);
	}
}
