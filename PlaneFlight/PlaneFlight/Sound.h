#pragma once
#include <string>
#pragma comment(lib, "winmm.lib")
class Sound
{
public:
	void play(std::string);
	void stop();
};

