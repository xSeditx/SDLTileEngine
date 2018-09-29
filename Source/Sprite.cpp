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
	 : Name(name)
{
        ImageSurface = IMG_Load(file);
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
        
       // SDL_FreeSurface(ImageSurface);

		ID = Manager.Add(this);
}

Image::Image(char *name)
	 : Name(name)
{

	ImageSurface = NULL;

	ImageTexture = NULL;

	Size.x = 0; 
	Size.y = 0; 

	ID = Manager.Add(this);
}

Image::Image(SDL_Surface * surf, SDL_Rect area)
{ // Use this for making tiles
	Print("Creating an Image from other images not completed");
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

Image *Image::MakeGreyScale(Image *img)
{
	Image *ret = new Image();

	SDL_Texture * texture = SDL_CreateTexture(SCREEN->Renderer,
		                                      SDL_PIXELFORMAT_ARGB8888,
		                                      SDL_TEXTUREACCESS_STATIC,
		                                      img->Size.x, 
		                                      img->Size.y);


	SDL_Surface *originalImage = img->ImageSurface;
	img->ImageSurface = SDL_ConvertSurfaceFormat(img->ImageSurface, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(originalImage);

	SDL_UpdateTexture(texture, NULL, img->ImageSurface->pixels, img->Size.x * sizeof(Uint32));
	Uint32 *Pixels = (Uint32 *)img->ImageSurface->pixels;

		                                      
	for_loop (y, img->Size.y)
	{
		for_loop (x, img->Size.x)
		{
			Uint32 Pixel = Pixels[x + (int)img->Size.x * y];

			Uint8 Red   = Pixel >> 16 & 0xFF;
			Uint8 Green = Pixel >> 8 & 0xFF;
			Uint8 Blue  = Pixel & 0xFF;
			Uint8 Grey = (Red + Green + Blue) / 3;

			Pixel = (0xFF << 24) | (Grey << 16) | (Grey << 8) | Grey;
			Pixels[y * (int)img->Size.x + x] = Pixel;

		}
	}
	SDL_UpdateTexture(texture, NULL, Pixels, img->Size.x * sizeof(Uint32));

	*ret = *img;
	ret->Size.x = img->Size.x;
	ret->Size.y = img->Size.y;
	 ret->ImageTexture = texture;
	*ret->ImageSurface = *img->ImageSurface;

	ret->Render(Vec2(10,10));
//	Print("Done making image");
	return ret;
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
	SDL_RenderCopyEx(SCREEN->Renderer, SpriteSheet->GetTexture(), &srcrect, &dstrect, Angle, &Center, SDL_RendererFlip(0));

}