#include "..\Headers\World.h"

World::World(Vec2 size)
	: SizeX(size.x),
   	  SizeY(size.y)
{
	Data = new int[SizeX * SizeY];

	for_loop(Index, (SizeX * SizeY))
	{
		Data[Index] = rand() % 15;
	}

}

int World::GetXY(int x, int y)
{
	return Data[x + SizeX * y];
}
int World::WorldtoGrid(Vec2 pos)
{
	Vec2 Test(0);

	Test.x = (pos.x / TileSizeX);
	Test.y = (pos.y / TileSizeY);

	return GetXY((int)Test.x,
		         (int)Test.y );
}

void World::Update()
{
}

void World::Render()
{
	float StartX = 0,
          StartY = 0;

}

void Viewport::MoveLeft(float amount)
{
	Position.x -= amount;
}
void Viewport::MoveRight(float amount)
{
	Position.x += amount;
}
void Viewport::MoveUp(float amount)
{
	Position.y -= amount;
}
void Viewport::MoveDown(float amount)
{
	Position.y += amount;
}

void Viewport::ZoomIn(float amount)
{
	Zoom += amount;
}
void Viewport::ZoomOut(float amount)
{
	Zoom -= amount;
}
