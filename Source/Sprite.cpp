#include"Sprite.h"
#include "..\Headers\Sprite.h"
AssetManager<Image>  Image::Manager;
AssetManager<Sprite> Sprite::Manager;


State::State(SDL_Rect srcrect, uint numframes)
	:TOTAL_FRAMES(numframes)
{
	CURRENT_FRAME = 0;
	FRAMES.reserve(numframes);
	uint x = srcrect.x;
	for_loop(Count, numframes)
	{
		SDL_Rect frame;
		frame.x = x;
		frame.y = srcrect.y;
		frame.w = srcrect.w;
		frame.h = srcrect.h;
		*this += frame; //FIXED Remember to get back to fixing the Overloaded Operator so that you can += new frames and states into your frame list.
		x += srcrect.w;
	}
}
std::vector<SDL_Rect> &State::ADD_FRAME(SDL_Rect frame)
{
	FRAMES.emplace_back(frame);
	return FRAMES;
} // Adds a frame to the State


const char *Name;
int ID;
Vec2 Size;
Texture *ImageTexture;
Surface *ImageSurface;


Image::~Image()
{
}
Image::Image(char * name, const char * file)
	 :Name(name)
{
        ImageSurface = IMG_Load(file);
		Source = file;

        if (!ImageSurface)
        {
        	Print("ImageClass: Image Can not be loaded"); Print(file);
        	return;
        }
        
        ImageTexture = SDL_CreateTextureFromSurface(SCREEN->Renderer, ImageSurface);
        
        if (!ImageTexture)
        {
        	Print("ImageClass: Texture Can not be made."); Print(file);
        	return;
        }
        Size.x = ImageSurface->w;
        Size.y = ImageSurface->h;
        
		ID = Manager.Add(this);
}
Image::Image(char *name)
	 : Name(name)
{
	Print("Getting into trouble here, fix the default Image Constructor with *name");
	ImageSurface = NULL;
	ImageTexture = NULL;

	Size.x = 0; 
	Size.y = 0; 

	ID = Manager.Add(this);
}
Image::Image(char *name, SDL_Surface * surf, SDL_Rect area)
{ // Use this for making tiles
	Print("Getting into trouble here, Image from surface");

	ImageSurface = SDL_CreateRGBSurface(NULL,
		area.w, area.h,
		surf->format->BitsPerPixel,
		surf->format->Rmask,
		surf->format->Gmask,
		surf->format->Bmask,
		surf->format->Amask);

	SDL_Rect dest = { 0, 0, area.w, area.h };
	SDL_BlitSurface(surf, &area, ImageSurface, &dest);

	ImageTexture = SDL_CreateTextureFromSurface(SCREEN->Renderer, ImageSurface);
	if (!ImageTexture)
	{
		Print("ImageClass: Texture Can not be made from existing Surface.");
		return;
	}
	
	ID = Manager.Add(this);
}

void Image::Render(Vec2 position)
{
	SDL_Rect srcrect = { 0, 0, Size.x, Size.y };
	SDL_Rect dstrect = { position.x, position.y , position.x + Size.x, position.y + Size.y };
	SDL_RenderCopy(SCREEN->Renderer, ImageTexture, &srcrect, &dstrect);
}
void Image::Render(Vec2 position, Vec2 size)
{
	SDL_Rect srcrect = { 0, 0, size.x, size.y };
	SDL_Rect dstrect = { position.x, position.y ,  size.x,size.y };
	SDL_RenderCopy(SCREEN->Renderer, ImageTexture, &srcrect, &dstrect);
}

void Image::MakeGreyScale()
{
	//Image ret;// = new Image();

	SDL_Texture * texture = SDL_CreateTexture(SCREEN->Renderer,
		                                      SDL_PIXELFORMAT_ARGB8888,
		                                      SDL_TEXTUREACCESS_STATIC,
		                                      Size.x, 
		                                      Size.y);

	SDL_Surface *originalImage = ImageSurface;
	ImageSurface = SDL_ConvertSurfaceFormat( ImageSurface, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(originalImage);

	SDL_UpdateTexture(texture, NULL,  ImageSurface->pixels,  Size.x * sizeof(Uint32));
	Uint32 *Pixels = (Uint32 *) ImageSurface->pixels;

	for_loop (y,  Size.y)
	{
		for_loop (x, Size.x)
		{
			Uint32 Pixel = Pixels[x + (int) Size.x * y];

			Uint8 Red   = Pixel >> 16 & 0xFF;
			Uint8 Green = Pixel >> 8 & 0xFF;
			Uint8 Blue  = Pixel & 0xFF;
			Uint8 Grey =  0.212671f * Red + 0.715160f * Green + 0.072169f * Blue; ;// (Red + Green + Blue) / 3;

			Pixel =  (0xFF << 24) | (Grey << 16) | (Grey << 8) | Grey;//Grey;//RGB( Grey, Grey, 255);// (0xFF << 24) | (Grey << 16) | (Grey << 8) | Grey;
			Pixels[y * (int) Size.x + x] = Pixel;

		}
	}

	SDL_UpdateTexture(texture, NULL, Pixels, Size.x * sizeof(Uint32));
	ImageTexture = texture;
}



Sprite::~Sprite()
{
	if (ID > 0)
	{
		Manager.Remove(ID);
	}
}
Sprite::Sprite(char *name, Image *source, int numstates)
	: TotalStates(numstates),
	SpriteSheet(source)
{
	Name = name;
	TotalStates = numstates;
	States.reserve(numstates);

	for_loop(count, TotalStates)
	{
		State temp;
		States.emplace_back(temp);
	}

	Angle = 0;
	AnimationSpeed = 150;
	Animated = true;
	CurrentState = 0;

	ID = Manager.Add(this);
}
void Sprite::Update()
{
	// Update information about this sprite, perhaps the specific frame or anythign of that nature
}
void Sprite::Render()
{
	Uint32 ticks = SDL_GetTicks();

	if (Animated == true)
	{

		States[CurrentState].CURRENT_FRAME = (ticks / AnimationSpeed) % States[CurrentState].TOTAL_FRAMES;
	}

	SDL_Rect srcrect = States[CurrentState].FRAMES[States[CurrentState].CURRENT_FRAME]; //{ frames * SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT };
	SDL_Rect dstrect = { Position.x - (Size.x *.5), Position.y - (Size.y * .5), Size.x, Size.y };
	SDL_RenderCopy(SCREEN->Renderer, SpriteSheet->GetTexture(), &srcrect, &dstrect);
}
void Sprite::Render(float angle)
{
	Uint32 ticks = SDL_GetTicks();
	if (Animated == true)
	{
		States[CurrentState].CURRENT_FRAME = (ticks / AnimationSpeed) % States[CurrentState].TOTAL_FRAMES;
	}

	SDL_Rect srcrect = States[CurrentState].FRAMES[States[CurrentState].CURRENT_FRAME]; //{ frames * SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT };
	SDL_Rect dstrect = { Position.x - (Size.x *.5), Position.y - (Size.y * .5), Size.x, Size.y };
	//    SDL_RenderCopy(SCREEN->Renderer, SpriteSheet->Sheet->ImageTexture, &srcrect, &dstrect);  
	SDL_Point Center = { Size.x / 2,Size.y / 2 };
	SDL_RenderCopyEx(SCREEN->Renderer, SpriteSheet->GetTexture(), &srcrect, &dstrect, Angle, &Center, SDL_RendererFlip(0));
}
void Sprite::Render(Vec2 position)
{
	Uint32 ticks = SDL_GetTicks();

	if (Animated == true)
	{
		States[CurrentState].CURRENT_FRAME = (ticks / AnimationSpeed) % States[CurrentState].TOTAL_FRAMES;
	}

	SDL_Rect srcrect = States[CurrentState].FRAMES[States[CurrentState].CURRENT_FRAME]; //{ frames * SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT };
	SDL_Rect dstrect = { position.x - (Size.x *.5), position.y - (Size.y * .5), Size.x, Size.y };

	SDL_Point Center = { Size.x / 2,Size.y / 2 };
	SDL_RenderCopyEx(SCREEN->Renderer, SpriteSheet->GetTexture(), &srcrect, &dstrect, Angle, &Center, SDL_RendererFlip(0));
}
void Sprite::Render(Vec2 pos, float angle)
{
	Uint32 ticks = SDL_GetTicks();

	if (Animated == true)
	{
		States[CurrentState].CURRENT_FRAME = (ticks / AnimationSpeed) % States[CurrentState].TOTAL_FRAMES;
	}

	SDL_Rect srcrect = States[CurrentState].FRAMES[States[CurrentState].CURRENT_FRAME]; //{ frames * SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT };
	SDL_Rect dstrect = { pos.x - (Size.x *.5), pos.y - (Size.y * .5), Size.x, Size.y };

	SDL_Point Center = { Size.x / 2,Size.y / 2 };
	SDL_RenderCopyEx(SCREEN->Renderer, SpriteSheet->GetTexture(), &srcrect, &dstrect, angle, &Center, SDL_RendererFlip(2));

}


Tile::Tile(int x, int y, int w, int h, bool collidable)
{
	PictureArea = {x, y, w, h};
	Collidable = collidable;
}

TileRender::TileRender(Image sheet, int tx, int ty)
{
	TileSheet = sheet;
	for (int y = 0; y < sheet.Size.y; y += ty)
	{
		for (int x = 0; x < sheet.Size.x; x += tx)
		{
			SDL_Rect src = {};
			Tile *newTile = new Tile(x, y, tx, ty, NULL);
			TileList.push_back(*newTile);
		}
	}
}

void TileRender::RenderTile(int tileID, float x, float y)
{
	Tile T = TileList[tileID];

	SDL_Rect srcrect = { T.PictureArea.x,
		                 T.PictureArea.y,
		                 T.PictureArea.w,
		                 T.PictureArea.h };
		                 
	SDL_Rect dstrect = { x,
		                 y,
		                 T.PictureArea.w / 2,
		                 T.PictureArea.h / 2};

	SDL_RenderCopy(SCREEN->Renderer, TileSheet.GetTexture(), &srcrect, &dstrect);
}



AABB* Sprite::MakeCollisionBox()
{
	//IDK WTF TO DO WITH THIS AT THE MOMENT
	//SDL_Rect dstrect = {Position.x - (Size.x *.5), Position.y - (Size.y * .5), Size.x, Size.y}
	return new AABB(Position, ((Size * .8f) *.5f));
}