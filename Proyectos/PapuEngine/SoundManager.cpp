#include "SoundManager.h"

SoundManager::SoundManager(/*const char* _backgroundPath*/)
{
	bgm = Mix_LoadMUS("Sounds/Purple Planet Music - Atmospheric - Eventide.mp3");
	if (!Mix_PlayingMusic())
	{
		Mix_PlayMusic(bgm, -1);
	}
}

SoundManager::SoundManager(const char* _backgroundPath)
{
	bgm = Mix_LoadMUS(_backgroundPath);
	if (!Mix_PlayingMusic())
	{
		Mix_PlayMusic(bgm, -1);
	}
}

SoundManager::SoundManager(const char* _backgroundPath, const char* _sfx)
{
	bgm = Mix_LoadMUS(_backgroundPath);
	if (!Mix_PlayingMusic())
	{
		Mix_PlayMusic(bgm, -1);
	}
	soundEffect1 = Mix_LoadWAV(_sfx);
}

SoundManager::SoundManager(const char* _backgroundPath,
	const char* _sfx1, const char* _sfx2, const char* _sfx3,
	const char* _sfx4, const char* _sfx5)
{
	bgm = Mix_LoadMUS(_backgroundPath);
	if (!Mix_PlayingMusic())
	{
		Mix_PlayMusic(bgm, -1);
	}
	soundEffect1 = Mix_LoadWAV(_sfx1);
	soundEffect2 = Mix_LoadWAV(_sfx2);
	soundEffect3 = Mix_LoadWAV(_sfx3);
	soundEffect4 = Mix_LoadWAV(_sfx4);
	soundEffect5 = Mix_LoadWAV(_sfx5);
}
SoundManager::~SoundManager()
{
	bgm = nullptr;
}

void SoundManager::StopMusic() {
	if(Mix_PlayingMusic)
		Mix_PauseMusic();
	//delete bgm;
}

void SoundManager::ResumeMusic() {
	if (Mix_PausedMusic)
		Mix_ResumeMusic();
}

void SoundManager::RestartMusic() {
	Mix_HaltMusic();
}

void SoundManager::PlaySFX1() {
	if (Mix_ChannelFinished)
		Mix_PlayChannel(-1, soundEffect1, 0);
	else
		StopChannel(-1);
	//if(Mix_ExpireChannel(-1,soundEffect1->))
}

void SoundManager::PlaySFX2() {
	Mix_PlayChannel(-1, soundEffect2, 0);
}

void SoundManager::PlaySFX3() {
	Mix_PlayChannel(-1, soundEffect3, 0);
}

void SoundManager::PlaySFX4() {
	Mix_PlayChannel(-1, soundEffect4, 0);
}

void SoundManager::PlaySFX5() {
	Mix_PlayChannel(-1, soundEffect5, 0);
}

void SoundManager::StopChannel(int sfx) {

	Mix_HaltChannel(sfx);
	/*switch (sfx)
	{
		default:
		case 0:
			break;
		case 1:
			break;	
		case 2:
			break;
	}*/
}
