#include "CivilWar.h"

#include <iostream>

int main()
{
	Soldier* greenSoldier = new Soldier();
	Soldier* blueSoldier = new Soldier();

	CivilWar* civilWar = new CivilWar();
	try {
		civilWar->start(greenSoldier, blueSoldier);
	}
	catch (BaseCWException e) {
		std::cout << e.getMsg();
	}
	
	delete(greenSoldier);
	delete(blueSoldier);
	delete(civilWar);

	return 0;
}
