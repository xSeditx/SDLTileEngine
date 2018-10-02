#pragma once
#include"Window.h"


class Viewport
{
public:
	Viewport() {}
	Viewport(Vec2 pos, Vec2 size);


	void MoveLeft(float amount);
	void MoveRight(float amount);
	void MoveUp(float amount);
	void MoveDown(float amount);
	void ZoomIn(float amount);
	void ZoomOut(float amount);

	void CameraCenter(int x, int y);
	void CameraGoto(int x, int y);
	void Update();
	//private:
	Vec2  Position,
		  Target,
	   	  Size;

	float Zoom,
		  Speed;
};


