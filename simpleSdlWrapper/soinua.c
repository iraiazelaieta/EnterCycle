#define SOINUA_C
#include "soinua.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
// #include <cstring>

void musicUnload(void);
void soundsUnload();

Mix_Chunk *soinuak[MAX_SOUNDS]; // mix_chunk soinu motza da, es un array de punteros que cada uno apunta a un sonido cargado
int soinuKop = 0; // zenbat soinu dauden igota
Mix_Music *musika = NULL; // fondoko musika, BAKARRIK BAT

void audioInit()
{
    // Cambiamos 2048 por 4096
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
}
/* Mix_OpenAudio irekitzen dau el sistema de audio, barrukoak die parametro "estandarrak"
frekuentzia, audio formatua, estero, buffer tamaina
<0 zeba SDL zenbaki negatiboak bueltatzen ditu erroreegaz*/


int loadSound(char *fileName) //.way artxiboa kargatzen du, array-an gorde, ID bat itzuli
{
    if (soinuKop == MAX_SOUNDS) // array-a ez desbordatzeko
    {
        return -1;
    }
    if ((soinuak[soinuKop] = Mix_LoadWAV(fileName)) == NULL) // soinua kargatzen du mix_chunk itzuliz
    {
        printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }
    soinuKop++;
    return soinuKop - 1; // ID bat itzuli soinu bakoitzeko
}

int loadTheMusic(char *fileName) // musika kargatu
{
    int wasPlaying = 0;

    if (musika != NULL)
    {
        wasPlaying = (Mix_PlayingMusic() != 1); // musika aktibatuta dagoen gordetzen du
        Mix_HaltMusic(); // aurreko musika gelditzen ez, ez solapatzeko
        // Mix_FreeMusic(musika);
    }
    if ((musika = Mix_LoadMUS(fileName)) == NULL) // musika berria kargatzen du
    {
        return 0;
    }
    if (wasPlaying) // erreproduzitzen bazegoen berriz erreproduzitu
    {
        Mix_PlayMusic(musika, -1); //-1 loop bat da
    }
    return 1;
}

int playSound(int idSound) // soinua erreproduzitu
{
    if ((idSound <= 0) && (idSound >= soinuKop))
    {
        return -1;
    }
    Mix_PlayChannel(0, soinuak[idSound], 0); // erreproduzitzeko: kanala (-1), soinua, ez errepikatzeko
    return idSound;
}

int playMusic(void) // musika erreproduzitzeko
{
    if (musika != NULL) // musika badau buklean (-1) erreproduzitzen dau
    {
        Mix_PlayMusic(musika, -1);
        return 1;
    }
    return 0;
}

void toggleMusic(void) // musika txandakatu --> gelditu/berrabiarazi
{
    if (musika != NULL) // konprobau musika dauela
    {
        if (Mix_PlayingMusic() != 0) // sonatzen badau
        {
            if (Mix_PausedMusic())
            {
                Mix_ResumeMusic(); // pausatuta badau berriz jarri
            }
            else
            {
                Mix_PauseMusic(); // pausatu musika
            }
        }
        else
        {
            playMusic(); // ez badau musika jarrita, jarri
        }
    }
}

void musicUnload(void) // musika liberatu
{
    if (musika != NULL)
    {
        Mix_HaltMusic(); // musika gelditzen dau
        Mix_FreeMusic(musika); // memoria liberatzen du
    }
}

void soundsUnload() // soinua liberatu
{
    int i;

    for (i = 0; i < soinuKop; i++) // dauden soinu guztietatik pasatzeko
    {
        Mix_FreeChunk(soinuak[i]); // banan banan libertzen dira
        soinuak[i] = NULL; // kontadorea reiniziau, 0 soinu
    }
    soinuKop = 0;
}

void audioTerminate(void) // soinu sistema ixteko
{
    Mix_HaltChannel(-1); // kanal guztiak gelditu
    soundsUnload(); // soinuak liberatu
    musicUnload(); // musika liberatu
    Mix_Quit(); // SDL_Mixer itxi
}
