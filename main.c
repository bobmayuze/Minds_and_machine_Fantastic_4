#include <stdio.h>
#include <stdlib.h>
#include "ev3_output.h"
#include "ev3_command.h"
#include "ev3_button.h"
#include "ev3_timer.h"
#include "ev3_lcd.h"
#include "serial_read.h"
#include <time.h>


void move()
{
	//We set the "threshold" value for determining what color we're looking at
	//to 100, but this number will almost definitely be different for you.
	int THRESHOLD = 23;

	//"sensor" is where we'll store the value that is returned by the sensor on out bot
	int sensor = 0;
	int sensor2 = 0;
	int whichside = 0;
	//this variable is to help us decide what values to throw away and what to keep
	//because the sensors aren't completely reliable.
	int temp = 0;
	int temp2 = 0; 

	//We set the power level for the motors before moving forward until a line
	SetPower(OUT_AD, -20);

	//Then we turn the motors on
	On(OUT_AD);

	while ((sensor < THRESHOLD) && (sensor2 < THRESHOLD))
	{
		//we will continue to execute the code in this block while the sensor
		//is picking up a value less than the threshold. This will likely mean that, while the robot is
		//over a black (or in general, dark) surface, it will continue to repeat these instructions

		//we read the value from serial port 1 into the temp variable
		temp = ReadSerial(1);
		temp2 = ReadSerial(4);

		//the invalid values that we want to throw away tend to be in the 400-1700 range, we only want
		//to look at values that are less than 100. You should never receive valid values above 100.
		if (temp < 100)
		{
			sensor = temp;//assuming the temporary value we just read is valid, we store it into the sensor variable
		}
		if (temp2 < 100)
		{
			sensor2 = temp2;//assuming the temporary value we just read is valid, we store it into the sensor variable
		}
		//printf("sensor: %d sensor2: %d\n", sensor, sensor2);
	}
	Off(OUT_ALL);
	Wait(100);

	if (sensor > sensor2)
	{
		On(OUT_D);
		while (sensor2 < THRESHOLD)
		{
			temp2 = ReadSerial(4);
			if (temp2 < 100)
			{
				sensor2 = temp2;//assuming the temporary value we just read is valid, we store it into the sensor variable
			}
		}
		Off(OUT_ALL);
	}
	else
	{
		On(OUT_A);
		while (sensor < THRESHOLD)
		{
			temp = ReadSerial(1);
			if (temp < 100)
			{
				sensor = temp;//assuming the temporary value we just read is valid, we store it into the sensor variable
			}
		}
		Off(OUT_ALL);
	}
	
	return;


}

void left()
{

	ResetAllTachoCounts(OUT_AD);
	SetPower(OUT_A, 10);
	SetPower(OUT_D, -10);
	On(OUT_AD);
	while (MotorRotationCount(OUT_D)> -150)
	{

	}
	Off(OUT_ALL);
}

void other_left()
{
	ResetAllTachoCounts(OUT_AD);
	SetPower(OUT_A, -10);
	SetPower(OUT_D, 10);
	//Then we turn the motors on
	On(OUT_AD);
	while (MotorRotationCount(OUT_A)> -150)
	{

	}
	Off(OUT_ALL);
}



int main()
{
	char input = 'p';
	OutputInit();
	while (input != 'q')
	{
		printf("What do you want to do? (l, r, f)\n");
		scanf(" %c", &input);
		switch (input)
		{
		case 'l': left();
			break;
		case 'r': other_left();
			break;
		case 'f': move();
			break;
		default:
			break;
		}
	}
	OutputExit();
	return 0;
}
