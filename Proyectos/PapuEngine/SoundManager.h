#pragma once
#include <SDL\SDL_mixer.h>
#include <string>
using namespace std;

class SoundManager
{
private:
	Mix_Music* bgm;
	Mix_Chunk * soundEffect1;
	Mix_Chunk * soundEffect2;
	Mix_Chunk * soundEffect3;
public:

	SoundManager(/*const char* _backgroundPath*/);
	SoundManager(const char* _backgroundPath);

	SoundManager(const char* _backgroundPath,const char* _sfx);
	SoundManager(const char* _backgroundPath, const char* _sfx1, const char* _sfx2, const char* _sfx3);

	~SoundManager();
	void StopMusic();
	void ResumeMusic();
	void RestartMusic();

	void PlaySFX1();
	void PlaySFX2();
	void PlaySFX3();
	void StopChannel(int sfx);
};

