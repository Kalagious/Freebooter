#include "cheats.h"''

void Cheats::keybinds()
{
	if (GetAsyncKeyState(VK_XBUTTON2))
	{
		zoooom->enable = true;
		zoooomShipEdition->enable = true;
	}
	else
	{
		zoooom->enable = false;
		zoooomShipEdition->enable = false;

	}


	if (GetAsyncKeyState(VK_UP) & 0x01)
		screenManager->bShowGUI = !screenManager->bShowGUI;

	//if (GetAsyncKeyState(VK_NUMPAD5) & 0x01)
	//	turnyBoi->enable = !turnyBoi->enable;
	/*if (GetAsyncKeyState(VK_NEXT) & 0x01)
		minigunGoBurr->enable = !minigunGoBurr->enable;*/
		
}