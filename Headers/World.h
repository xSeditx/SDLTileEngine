#pragma once
#include"Window.h"
#include"Sprite.h""
#include"Entity.h"

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

//private:
	Vec2  Position,
	      Size;
	float Zoom;
};


class Player
{
public:
	Player() {}
	Player(Vec2 pos, Vec2 size)
		: Position(pos), Size(size), Health(1000) {}

	void MoveLeft(float amount);
	void MoveRight(float amount);
	void MoveUp(float amount);
	void MoveDown(float amount);

	int Health;

	void Update();
	void Render();

	Vec2  Position,
		Size;

	AABB *CollisionBox;
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

	   TileRender Tiles;

	   Player   Player1;


	   std::vector<Entity *> EntityList;
//private:
	   int SizeX, 
		   SizeY,
		   TileSizeX, 
		   TileSizeY;

	   int *Data;
	   Viewport Camera;
};