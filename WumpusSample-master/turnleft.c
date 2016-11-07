#include <stdio.h>
#include <stdlib.h>
#include "ev3_output.h"
#include "ev3_command.h"
#include "ev3_button.h"
#include "ev3_timer.h"
#include "ev3_lcd.h"


void turnleft()
{
	//before doing anything we reset the tachometers, that way
	//we can measure the turn for consistency
	ResetAllTachoCounts(OUT_AD);

	//we synchronize the motors A and D, setting A's speed to 20, and D's speed
	//to 200. I don't remember what the 0 does, but the fourth argument should
	//be 0.
	OnFwdSyncEx(OUT_AD,20,200,0);
	
	//We track the rotation of motor A, and continue to rotate until the
	//tachometer's count is -191.
	while(MotorRotationCount(OUT_A)<187)
	{
		//I had to remove the button check feature, since that was causing
		//segfaults for some reason. Now it just rotates until completion.
	};

	//then we turn all the motors off
	Off(OUT_ALL);

}


int main()
{//we need to initialize main
	//This is necessary at the beginning of main in order to prevent the
	//robot from doing really dumb stuff. It initializes motor values and
	//things like that so you can successfully start them
	OutputInit();

	//call the turn left function
	turnleft();
	
	//This takes care of all the shut down stuff for the motors. It has to be
	//at the end of main. 
	OutputExit();

	//then return from main
	return 0;
}
