#include "Sound.h"
#include <Windows.h>

void Sound::play(std::string path)
{
	std::wstring stemp = std::wstring(path.begin(), path.end());
	LPCWSTR sw = stemp.c_str();
	PlaySound(sw, NULL, SND_FILENAME | SND_ASYNC);
}

void Sound::stop()
{
	PlaySound(NULL, NULL, 0);
}
