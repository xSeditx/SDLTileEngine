#pragma once
#include "AssetManager.h"
#include "Window.h"
#include "SDL_Image.h"
#include "Collision.h"

class Image
{
public:
   ~Image();
    Image(){}
    Image(const Image& other)
    {
       *this = other;
    	this->ID = 0;
    }

	Image(char *name, const char *file);
	Image(char *name);
	Image(char *name, SDL_Surface *surf, SDL_Rect area);
	
    const char *Name;
    int   ID;
    Vec2  Size;
	const char *Source;
    void Render(Vec2 position);
    void Render(Vec2 position, Vec2 size);


    static AssetManager<Image> Manager;

	Texture *GetTexture() { return ImageTexture; }
	Surface *GetSurface() { return ImageSurface; }

	void MakeGreyScale();
private:
	Texture *ImageTexture;
	Surface *ImageSurface;
};



class State
{
public:
	State() {}
	~State() {}

	State(SDL_Rect sourcerect, uint numframes);
	State(SDL_Rect sourcerect, Vec2 size, uint numframes);
	State(uint x, uint y, uint w, uint h, uint numframes)
	{
		SDL_Rect src = { x,y,w,h };
		*this = State(src, numframes);
	}

	std::vector<SDL_Rect>FRAMES;
	uint TOTAL_FRAMES;
	uint CURRENT_FRAME;

	static State* MakeStates(SDL_Rect sourcerect, uint numframes, uint numstates)
	{
		State *ret = new State[numstates];

		uint Ypos  = sourcerect.y;
		uint Ystep = sourcerect.h;

		for_loop(Index, numstates)
		{
			ret[Index] = State(sourcerect.x, Ypos, sourcerect.w, sourcerect.h, numframes);
			Ypos += Ystep;
		}
		return ret;
	}


	State operator +=(SDL_Rect newframe)
	{
		this->ADD_FRAME(newframe);
		return *this;
	}
	State operator +=(State newstate)
	{
		for_loop(count, newstate.TOTAL_FRAMES)
		{
			this->ADD_FRAME(newstate.FRAMES[count]);
			this->TOTAL_FRAMES++;
		}
		return *this;
	}

private:
	std::vector<SDL_Rect>& ADD_FRAME(SDL_Rect frame);
};


class Sprite
{
public:
	Sprite() {}
	~Sprite();

	Sprite(char *name, Image *source, int numstates);
	Sprite(const Sprite& other)
	{
		*this = other;
		this->ID = 0;
	}
	
	Sprite(char *name, Image *source)
	{//	 std::Bind would be useful here
		*this = Sprite(name, source, 1);
	}

	char *Name;
	int ID;

	Vec2 Position;
	Vec2 Size;

	bool Animated;

	float Angle;

	Image *SpriteSheet;

	uint TotalStates;
	std::vector<State> States;

	uint CurrentState;

	uint Timer;

	int  AnimationSpeed;

	bool Collidable;
public:

	inline void SetPosition(Vec2 pos) { Position = pos; }

	void  Update();
	void  Render();
	void  Render(float angle);
	void  Render(Vec2 pos);
	void  Render(Vec2 pos, float angle);

 	AABB* MakeCollisionBox();
	//------------------------------------------------------------------------------------------------------------------
	static AssetManager<Sprite> Manager;
	//------------------------------------------------------------------------------------------------------------------
};

struct Tile
{
public:
	Tile(int x, int y, int w, int h, bool collidable);
	class SDL_Rect PictureArea;
	bool Collidable;
};



class TileRender
{
public:
	TileRender() {}
	TileRender(Image sheet, int tx, int ty);


	void RenderTile(int TileID, float x, float y);
	void Spawn(int index, int x, int y);

	Image TileSheet;


	std::vector<Tile> TileList;
};
