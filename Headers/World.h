#pragma once
#include"Window.h"

#include"Sprite.h"

#include"Entity.h"
#include"Camera.h"



class Player
{
public:
        Player() {}
        Player(Vec2 pos, Vec2 size);
        
        void MoveLeft(float amount);
        void MoveRight(float amount);
        void MoveUp(float amount);
        void MoveDown(float amount);
        
        int Health;
        
        void Update();
        void Render();
        
        Sprite *PlayerSprite;
        int PlayerState;
        
        Vec2  WorldPosition,
			  ScreenPosition,
        	  Size;
        bool Grounded;
        bool Jumping;
        bool Forward;

		Viewport Camera;

        AABB *CollisionBox;

		Mass Body;

        enum StateNames
        {
                Running = 0,
                Walking = 4,
                JumpCrouch,
                HighStep,
                LessHighStep,
                Stopped
        };


};


class World
{
public:
       ~World() {}
        World() {}
	    World(Vec2 size);
		   
        int GetXY(int x, int y);
		bool isCollision(int x, int y);
        int WorldtoGrid(Vec2 pos);
        
        void Update();
        void Render();
        
        TileRender Tiles;
        
        Player Player1;
        
        std::vector<Entity *> EntityList;
// Private:
        int SizeX, 
            SizeY,
            TileSizeX, 
            TileSizeY;
        
        int *Data;

};