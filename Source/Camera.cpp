#include"Camera.h"


Viewport::Viewport(Vec2 pos, Vec2 size)
	: Position(pos), 
	  Size(size), 
	  Speed(.5)
{}

void Viewport::Update()
{
	
	float x, y, Distance;
	float Vx, Vy, V;

	x = (float)(Target.x - Position.x);
	y = (float)(Target.y - Position.y);

	if (Squared(x) + Squared(y) <= 1)
	{
		Position = Target;
	}
	else
	{
		Distance = sqrt(Squared(x) + Squared(y));
		V = (Distance * Speed / 60);
		if (V < 1.0f)
		{
		    V = 1.0f;
	    }
		Vx = x * (V / Distance);
		Vy = y * (V / Distance);

		Position.x += Vx;
		Position.y += Vy;
	}
}
void Viewport::CameraCenter(int x, int y)
{
	x = x - (Size.x / 2);
	y = y - (Size.y / 2);
	Target.x = (float)x;
	Target.y = (float)y;
}
void Viewport::CameraGoto(int x, int y)
{
	Target.x = (float)x;
	Target.y = (float)y;
}

void Viewport::MoveLeft(float amount)
{
	CameraGoto(Position.x - amount, Position.y);
}
void Viewport::MoveRight(float amount)
{
	CameraGoto(Position.x + amount, Position.y);
}
void Viewport::MoveUp(float amount)
{
	CameraGoto(Position.x, Position.y - amount);
}
void Viewport::MoveDown(float amount)
{
	CameraGoto(Position.x, Position.y + amount);
}
void Viewport::ZoomIn(float amount)
{
	Zoom += amount;
}
void Viewport::ZoomOut(float amount)
{
	Zoom -= amount;
}