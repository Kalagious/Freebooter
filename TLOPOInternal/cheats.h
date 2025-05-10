#pragma once
#include "screenmanager.h"
#include "allmodules.h"
#include "module.h"
#include "allclasses.h"
#include "roguepython.h"
#include "hookmanager.h"
#include <iostream>
#include <fstream>


class Cheats {
public:
	Cheats();
	void tick();
	void keybinds();
	void recalculateAddresses();
	void cleanup();

	bool uninject;
	bool addressesAreValid;

	Player* localPlayer;

	void* tlopoExe;
	void* openGl32;

	std::vector<Module*> modules;

	HookManager* hookManager;
	ScreenManager* screenManager;
	RoguePython* roguePython;

	Fly* fly;
	Zoooom* zoooom;
	ZoooomShipEdition* zoooomShipEdition;
	MinigunGoBurr* minigunGoBurr;
	TurnyBoi* turnyBoi;
	CoolDownsAreCringe* cooldownsAreCringe;
	InfiniteCannons* infiniteCannons;
	SniperElite* sniperElite;
	MoreLikeGuidelines* moreLikeGuidelines;
	CannonFlashSuppressor* cannonFlashSuppressor;
	
	NoAttackCooldown* noAttackCooldown;
	bool bMouseDown;
	HWND hWnd;

	uint64_t iTicks;

	std::ofstream myfile;
	uint64_t shipTmp;

};