#pragma once
#include"window.h"
#include"SDL_Mixer.h"
#include"Assets.h"

#if !USING_ASSETS



// Good Sound Effect Site:  https://opengameart.org/content/rpg-sound-archive-attack-movement-hits

#define SFX_LASER       0
#define SFX_PLAYERHIT   1
#define SFX_BOOM1       2          
#define SFX_BOOM2       3         
#define SFX_BOOM3       4
#define SFX_BOOM5       5
#define SFX_BOOM8       6
#define SFX_HEAD006     7  
#define SFX_TAIL004     8  
#define SFX_TAIL005     9  
#define SFX_BEEP       10
#define SFX_GUNFIRE    11   
#define SFX_EXTRALIFE  12    

#define MUSIC_BACKGROUND1   0
#define MUSIC_BACKGROUND2   1



class SoundEffect
{
public:
    SoundEffect(){}
    
    ~SoundEffect()
    {
        Mix_FreeChunk(Object);
    }
    SoundEffect(const char *file, int volume):ID(NumberOfSoundEffects++)
    {
        Volume = volume;

        if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT,2, 4096 ) == -1 )
        {
            Print("Failed to initialize Sound Effect" << Mix_GetError() );  
          return;
        }
        else
        {
            Object = Mix_LoadWAV(file);
        }
        SoundEffects.push_back(this);
    }


    void Play()
    {
        Mix_PlayChannel(-1, Object, 0);
    }

    void SetVolume(int vol)
    {
        Volume = vol;
    }

    Mix_Chunk *Object;
    int Volume;

    int ID;

/*___________________________________________________________________________________________________________________________________________
 =====================================================          SOUND  ASSETS             ===========================================================
 ============================================================================================================================================*/

static void InitializeSound()
{
    SoundEffect *LaserSound = new SoundEffect("Assets\\Laser.wav", 100);
    SoundEffect *PlayerHit  = new SoundEffect("assets\\PlayerHit.wav", 100);
    SoundEffect *Boom1 = new SoundEffect("assets\\Boom1.wav", 100);
    SoundEffect *Boom2 = new SoundEffect("assets\\Boom2.wav", 100);
    SoundEffect *Boom3 = new SoundEffect("assets\\Boom3.wav", 100);
    SoundEffect *Boom5 = new SoundEffect("assets\\Boom5.wav", 100);
    SoundEffect *Boom8 = new SoundEffect("assets\\Boom8.wav", 100);
    SoundEffect *LaserHead0006 = new SoundEffect("Assets\\Head0006.wav", 100);
    SoundEffect *LaserTail0004 = new SoundEffect("Assets\\Tail0004.wav", 100);
    SoundEffect *LaserTail0005 = new SoundEffect("Assets\\Tail0005.wav", 100);
    SoundEffect *Beep01 = new SoundEffect("Assets\\Click.wav", 100);
    SoundEffect *GunFire = new SoundEffect("Assets\\antimatterhit.wav",100);
    SoundEffect *Extralife = new SoundEffect("assets\\ExtraLife.wav",100);
}


  static std::vector<SoundEffect *> SoundEffects;
  int NumberOfSoundEffects;


};



class Music
{
public:
        Music(){}
        
        ~Music()
        {
                Mix_FreeMusic(Object);
        }
        Music(const char *file, int volume) : ID(NumberOfMusicFiles++)
        {
                Volume = volume;
                
                if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT,2, 4096 ) == -1 )
                {
                    Print("Failed to initialize Music" << Mix_GetError() );  
                  return;
                }
                else
                {
                    Object = Mix_LoadMUS(file);
                    Mix_VolumeMusic(2000);
                }


                Stereo = true;
        }
        
        void Play()
        {
                Mix_PlayMusic(Object, -1 );
        }
        
        void SetVolume(int vol)
        {
                Volume = vol;
                Mix_VolumeMusic(Volume);
        }


        Mix_Music *Object;
        bool Stereo;
        int Volume;
        int ID;
/*___________________________________________________________________________________________________________________________________________
 =====================================================           MUSIC  ASSETS             ==================================================
 ============================================================================================================================================*/
    static void InitializeMusic()
    {
       Music *BackgroundMusic  = new Music("Assets\\Music.wav", 1000);
       Music *BackgroundMusic2 = new Music("Assets\\Mayhem.mp3", 1000);
    }
    
   // static  Music *BackgroundMusic, *BackgroundMusic2;

    static std::vector<Music *> MusicFiles;
    int  NumberOfMusicFiles;
};
 
#endif


// MUST BE DECLARED IN ANY PROGRAM THAT WISHES TO USE THIS HEADER
//
// static std::vector<SoundEffect *> SoundEffect::SoundEffects;
// int NumberOfSoundEffects;

// static std::vector<Music *> Music::MusicFiles;
// int  NumberOfMusicFiles;
//


