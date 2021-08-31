#include "Sound.h"
#include "default_value.h"

pSound::pSound()
{
	System_Create(&g_pSystem);
	g_pSystem->init(6, FMOD_INIT_NORMAL, 0);

	g_pSystem->createSound(".\\Resource\\Boss_BGM.mp3", FMOD_LOOP_NORMAL, 0, &g_pSound[SD_BGM]);
	g_pSystem->createSound(".\\Resource\\Pistol.wav", FMOD_DEFAULT, 0, &g_pSound[SD_PISTOL]);
	g_pSystem->createSound(".\\Resource\\FlameThrower.mp3",FMOD_LOOP_NORMAL, 0, &g_pSound[SD_FLAMETHROWER]);
	g_pSystem->createSound(".\\Resource\\Grenade.wav", FMOD_DEFAULT, 0, &g_pSound[SD_GRENADE]);
	g_pSystem->createSound(".\\Resource\\Item.wav", FMOD_DEFAULT, 0, &g_pSound[SD_ITEM]);
	g_pSystem->createSound(".\\Resource\\Potion.wav", FMOD_DEFAULT, 0, &g_pSound[SD_POTION]);
}

void pSound::pSound_Pistol()
{
	g_pSystem->playSound(FMOD_CHANNEL_FREE, g_pSound[SD_PISTOL], false, &g_pChannel);
}

void pSound::pSound_BGM()
{
	g_pSystem->playSound(FMOD_CHANNEL_FREE, g_pSound[SD_BGM], false, &g_pChannel);
}

void pSound::pSound_FlameThrower()
{
	g_pSystem->playSound(FMOD_CHANNEL_FREE, g_pSound[SD_FLAMETHROWER], false, &g_pChannel);
}

void pSound::sSound_FlameThrower()
{
	g_pChannel->stop();
}

void pSound::pSound_Grenade()
{
	g_pSystem->playSound(FMOD_CHANNEL_FREE, g_pSound[SD_GRENADE], false, &g_pChannel);
}

void pSound::pSound_Item()
{
	g_pSystem->playSound(FMOD_CHANNEL_FREE, g_pSound[SD_ITEM], false, &g_pChannel);
}

void pSound::pSound_Potion()
{
	g_pSystem->playSound(FMOD_CHANNEL_FREE, g_pSound[SD_POTION], false, &g_pChannel);
}

void pSound::update_Sound()
{
	g_pSystem->update();
}

void pSound::Release()
{
	g_pSystem->release();
	g_pSystem->close();
}