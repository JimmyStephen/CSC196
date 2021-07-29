#include <iostream>
#include <Windows.h>

void FireworkSound() {
	bool soundPlayed = PlaySound(TEXT("Firework_Sound.wav"), NULL, SND_SYNC);
}