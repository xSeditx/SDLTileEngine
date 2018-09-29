#pragma once
#include "AssetManager.h"
#include "Window.h"
#include "SDL_Image.h"

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
	Image(SDL_Surface *surf, SDL_Rect area);
	
    const char *Name;
    int   ID;
    Vec2  Size;
   
    void Render(Vec2 position);
    void Render(Vec2 position, Vec2 size);


    static AssetManager<Image> Manager;

	Texture *GetTexture() { return ImageTexture; }
	Surface *GetSurface() { return ImageSurface; }

static Image *MakeGreyScale(Image *img);
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

	int  AnimationSpeed;

	bool Collidable;
public:

	inline void SetPosition(Vec2 pos) { Position = pos; }

	void  Update();
	void  Render();
	void  Render(float angle);
	void  Render(Vec2 pos);
	void  Render(Vec2 pos, float angle);

//	AABB* MakeCollisionBox();
	//------------------------------------------------------------------------------------------------------------------
	static AssetManager<Sprite> Manager;
	//------------------------------------------------------------------------------------------------------------------
};


class TileRender
{
public:
	TileRender() {}
	TileRender(Image sheet);

private:
	Image TileSheet;
	std::vector<SDL_Rect> TileList;
};
