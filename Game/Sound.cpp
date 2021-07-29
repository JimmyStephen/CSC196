#include "Sound.h"
#include <Windows.h>

namespace nc {
	void FireworkSound()
	{
		PlaySound(TEXT("Firework_Sound.wav"), NULL, SND_SYNC);
	}
}