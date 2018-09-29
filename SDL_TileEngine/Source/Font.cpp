#include"Fonts.h"
#include"Window.h"

FontRender *FontRender::Fonts;

FontRender::FontRender(const char*file)
{
    if (TTF_Init() < 0) 
    {
        Print("Font Initialization Failed");
        Print("Error: " << TTF_GetError());
    }

    CurrentFont = TTF_OpenFont(file, 30);

    if(!CurrentFont)
    {
        Print(TTF_GetError);
    }
}
FontRender::FontRender(const char*file, int size)
{
    if (TTF_Init() < 0) 
    {
        Print("Font Initialization Failed");
        Print("Error: " << TTF_GetError());
    }

    CurrentFont = TTF_OpenFont(file, size);

    if(!CurrentFont)
    {
        Print(TTF_GetError);
    }
}

void FontRender::FreeFont(TTF_Font *font)
{
    TTF_CloseFont(font);
}
void FontRender::CloseFontRender()
{
    TTF_Quit();
}
void FontRender::SetSize()
{
    
}
void FontRender::Write(float value, Vec2 pos)
{
    std::string Str = std::to_string((int)value);
    const char* S = Str.c_str();

    Write(S, pos);
}
void FontRender::Write(const char *text, Vec2 pos)
{
    float Width  = 0, 
          Height = 0;

    SDL_Surface *surface = TTF_RenderText_Solid(CurrentFont, text, ForgroundColor);

    if( surface == NULL )
     {
         printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
     }
     else
     {
         SDL_Texture *mTexture = SDL_CreateTextureFromSurface( SCREEN->Renderer, surface );
         if( mTexture == NULL )
         {
             printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
             Print("Failed Printing: " << text );
         }
         else
         {
             //Get image dimensions
             Width  = surface->w;
             Height = surface->h;
#ifdef _FONTDEBUG
                 Print("Did it Make it here The Text we are writing is....("<<text<<")");
#endif              
             }
             SDL_FreeSurface( surface );
             //TTF_Set
             //Set rendering space and render to screen
             SDL_Rect renderQuad = { (int)pos.x,  (int)pos.y, 
				                     (int)Width,  (int)Height };
             SDL_RenderCopy( SCREEN->Renderer, mTexture, NULL, &renderQuad );
             
             SDL_DestroyTexture(mTexture); 
         }
    }

void FontRender::WriteShadow(const char *text, Vec2 pos, int depth)
{
    SDL_Color savedcol = ForgroundColor; 

    SetForgroundColor(100,100,100, 255);
    Write(text, Vec2(pos.x + depth, pos.y + depth));

    SetForgroundColor(savedcol.r, savedcol.g, savedcol.b, savedcol.a);
    Write(text, pos);
}
void FontRender::WriteShadow(float value, Vec2 pos, int depth)
{
    SDL_Color savedcol = ForgroundColor; 

    SetForgroundColor(100,100,100, 255);
    std::string Str = std::to_string((int)value);
    const char* S = Str.c_str();
    Write(S, Vec2(pos.x + depth, pos.y + depth));

    SetForgroundColor(savedcol.r, savedcol.g, savedcol.b, savedcol.a);
    Str = std::to_string((int)value);
    S = Str.c_str();
    Write(S, pos);
}

void FontRender::SetForgroundColor(float R, float G, float B, float A)
{
    ForgroundColor.r = R;
    ForgroundColor.g = G;
    ForgroundColor.b = B;
    ForgroundColor.a = A;
}



