#include "fmod.hpp"

#pragma comment (lib, "fmodex_vc.lib")
using namespace FMOD;

class pSound {
public:
	pSound();
	void pSound_Pistol();
	void pSound_BGM();
	void pSound_FlameThrower();
	void sSound_FlameThrower();
	void pSound_Grenade();
	void pSound_Item();
	void pSound_Potion();
	void update_Sound();
	void Release();
private:
	enum SOUNDKIND {
		SD_BGM,
		SD_PISTOL,
		SD_FLAMETHROWER,
		SD_GRENADE,
		SD_ITEM,
		SD_POTION,
		SD_END
	};

	System*   g_pSystem;
	Sound*    g_pSound[SD_END];
	Channel* g_pChannel;
};