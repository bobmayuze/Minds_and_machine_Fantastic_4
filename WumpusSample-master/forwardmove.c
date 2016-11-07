#include <stdio.h>
#include <stdlib.h>
#include "ev3_output.h"
#include "ev3_command.h"
#include "ev3_button.h"
#include "ev3_timer.h"
#include "ev3_lcd.h"
#include "serial_read.h"


void forward_serial_read()
{
	//We set the "threshold" value for determining what color we're looking at
	//to 100, but this number will almost definitely be different for you.
	int THRESHOLD = 20;
	
	//"sensor" is where we'll store the value that is returned by the sensor on out bot
	int sensor = 0;
	
	//this variable is to help us decide what values to throw away and what to keep
	//because the sensors aren't completely reliable.
	int temp = 0;
	
	//We set the power level for the motors before moving forward until a line
	SetPower(OUT_A, 40);
	SetPower(OUT_D, 40);

	//Then we turn the motors on
	On(OUT_ALL);
	
	while(sensor < THRESHOLD)
	{
		//we will continue to execute the code in this block while the sensor
		//is picking up a value less than the threshold. This will likely mean that, while the robot is
		//over a black (or in general, dark) surface, it will continue to repeat these instructions
	
		//we read the value from serial port 1 into the temp variable
		temp = ReadSerial(1);
	
		//the invalid values that we want to throw away tend to be in the 400-1700 range, we only want
		//to look at values that are less than 100. You should never receive valid values above 100.
		if(temp < 100)
		{
			sensor = temp;//assuming the temporary value we just read is valid, we store it into the sensor variable
		}
	}
	
	//Once we've finished moving, we turn the motors off and return
	Off(OUT_ALL);
	return;
	
	
}


void forward()
{
	//we set the power of motor A to 40
  SetPower(OUT_A, 40);
	//then we set the power of motor D to 40
  SetPower(OUT_D, 40);
	//then we turn all the motors on
  On(OUT_ALL);
	//we let it run for 2.750 seconds
	//since the Wait function takes its argument in milliseconds
  Wait(2750);
	//then we turn all the motors off (so the bot will stop moving
  Off(OUT_ALL);
}

int main()
{//set up the main function
	//This is necessary at the beginning of main in order to prevent the
	//robot from doing really dumb stuff. It initializes motor values and
	//things like that so you can successfully start them
	OutputInit();
	
	int instruction = 0;
	while(instruction == 0)
	{
		//the function printf prints information to the terminal. It takes a variable number of
		//arguments, but how you should be using it for this project is like I have shown below.
		//You will only be passing printf 1 argument, which is a string of characters inside of 
		//quotation marks. The \n at the end of mine represents a newline character, which will
		//print a newline to the terminal, and is necessary in order to get the terminal to actually
		//print the string out
		printf("Please input the number 1 to continue\n");
		
		//scanf is how you receive information from the user at the terminal. In this particular case,
		//we use the " %d" to tell it that we want to take in an integer from the user. the second
		//argument tells scanf where to store this information. Because we are scanning in an integer,
		//we have to pass scanf a reference to the variable, which is why there is an ampersand in front
		//of "instruction". 
		//It is possible that you will not need the space in front of the %d, however I remember distinctly
		//having problems with giving the program input, and this fixed it. It had something to do with
		//sending a newline repeatedly, and this solved that issue. If for some reason you have problems with
		//this, you might try removing the space, but it shouldn't cause you any issues.
		scanf(" %d",&instruction);
		
		//these if statements just make sure that the user actually inputs the value that we wanted
		//since we asked for a 1, then we allow "instruction" to remain as a 1, which will exit the
		//while loop
		if(instruction == 1)
		{
			instruction = 1;
		}//if, however, they do not type in a 1, then we set instruction to 0, which will make the loop repeat
		else
		{
			instruction = 0;
		}
	}
	
	
	
	//then call the forward function
	//forward();
	
	//this calls the function that runs until a white line
	forward_serial_read();
	
	//This takes care of all the shut down stuff for the motors. It has to be
	//at the end of main. 
	OutputExit();

	//then return from main
	return 0;
}
