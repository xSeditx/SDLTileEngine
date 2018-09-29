#pragma once
#include"Window.h"
#include"Sprite.h""

class Viewport
{
public:
	Viewport() {}
	Viewport(Vec2 pos, Vec2 size) 
		: Position(pos), Size(size) {}

	void MoveLeft (float amount);
	void MoveRight(float amount);
	void MoveUp   (float amount);
	void MoveDown (float amount);
	void ZoomIn   (float amount);
	void ZoomOut  (float amount);

private:
	Vec2  Position,
	      Size;
	float Zoom;
};





class World
{
public:
      ~World() {}
	   World() {}
	   World(Vec2 size);
		   
	   int GetXY(int x, int y);
	   int WorldtoGrid(Vec2 pos);

	   void Update();
	   void Render();

private:
	   int SizeX, 
		   SizeY,
		   TileSizeX, 
		   TileSizeY;

	   int *Data;
	   Viewport Camera;
	   TileRender Tiles;
};