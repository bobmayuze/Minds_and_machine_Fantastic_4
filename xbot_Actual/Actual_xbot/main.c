//
//  main.c
//  Actual_xbot
//
 // # 　　　┏┓　　　┏┓
 // # 　　┏┛┻━━━┛┻┓
 // # 　　┃　　　　　　　 ┃
 // # 　　┃　　　━　　　 ┃
 // # 　　┃　┳┛　┗┳　┃
 // # 　　┃　　　　　　　 ┃
 // # 　　┃　　　┻　　　 ┃
 // # 　　┃　　　　　　　 ┃
 // # 　　┗━┓　　　┏━┛Codes are far away from bugs with the animal protecting
// # 　　　　┃　　　┃    神兽保佑,代码无bug
// # 　　　　┃　　　┃
// # 　　　　┃　　　┗━━━┓
// # 　　　　┃　　　　　 ┣┓
// # 　　　　┃　　　　 ┏┛
// # 　　　　┗┓┓┏━┳┓┏┛
// # 　　　　　┃┫┫　┃┫┫
// # 　　　　　┗┻┛　┗┻┛
// #
//  Created by 刘晓艺 on 12/8/16.
//  Copyright © 2016 刘晓艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "ev3_output.h"
#include "ev3_command.h"
#include "ev3_button.h"
#include "ev3_timer.h"
#include "ev3_lcd.h"
#include "serial_read.h"
#include <time.h>
#include <math.h>

int position[2];
int d = 0;
// direction:
// 0:up 1:right 2:down 3:left
int input = 8;
// int adj[4][2] = {{position[0]+1,position[1]},{position[0]-1,position[1]},{position[0],position[1]+1},{position[0],position[1]-1}};
int bd[4][4] = {{9,9,0,0},{9,0,0,0},{0,0,0,0},{0,0,0,0}};
// board:
// 0:unknown 1:hole 2:wumpus 4:gold 9:safe -1:car
int path[4][4] = {{1,0,0,0},{1,0,0,0},{0,0,0,0},{0,0,0,0}};
int poss[4][4][4];
int end=0;

void forward()
{
	ResetAllTachoCounts(OUT_AD);
	SetPower(OUT_A, -21);
	SetPower(OUT_D, -20);
	//Then we turn the motors on
	On(OUT_AD);
	printf("3.1\n");
	while (MotorRotationCount(OUT_A)> -700)
	{

	}
	printf("3.2\n");
	Off(OUT_ALL);
}

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
	printf("2.1\n");
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
	printf("2.2\n");
    Off(OUT_ALL);
    Wait(100);
    
    if (sensor > sensor2)
    {
        On(OUT_D);
		printf("2.3\n");
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
		printf("2.4\n");
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
	printf("2.5\n");
    forward();
    
    return; 
}


void backup()
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
	SetPower(OUT_AD, 20);

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

	ResetAllTachoCounts(OUT_AD);
	SetPower(OUT_A, 10);
	SetPower(OUT_D, 10);
	//Then we turn the motors on
	On(OUT_AD);
	while (MotorRotationCount(OUT_A) < 240)
	{

	}
	Off(OUT_ALL);

	return;

}

void turn_left()
{
	ResetAllTachoCounts(OUT_AD);
	SetPower(OUT_A, 11);
	SetPower(OUT_D, -10);
	On(OUT_AD);
	while (MotorRotationCount(OUT_D)> -200)
	{

	}
	Off(OUT_ALL);
	wait(100);
	// move();
}

void turn_right()
{
	ResetAllTachoCounts(OUT_AD);
	SetPower(OUT_A, -11);
	SetPower(OUT_D, 10);
	//Then we turn the motors on
	On(OUT_AD);
	while (MotorRotationCount(OUT_A)> -200)
	{

	}
	Off(OUT_ALL);
	wait(100);
	// move();
}

void safe(int x,int y){
    bd[x][y] = 9;
}

void putCar(int x,int y){
    bd[x][y] = -1;
}

void init(int x, int y){
    position[0]=x;
    position[1]=y;
    putCar(x,y); // for test only
}

void printBd(){
    printf("\n");
    for(int i=3;i>=0;i--){
        for(int j=0;j<4;j++){
            printf("%2d ",bd[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int face_edge(){
    if (position[0] == 3 && (d%4 == 0 || d%4==-4))
        return 1;
    else if (position[0] == 0 && (d%4 == 2 || d%4==-2))
        return 1;
    else if (position[1] == 3 && (d%4 == 1 || d%4==-3))
        return 1;
    else if (position[1] == 0 && (d%4 == 3 || d%4==-1))
        return 1;
    else
        return 0;
}

void left(){
    d -= 1;
    turn_left();
}

void right(){
    d += 1;
    turn_right();
}

void move_forward(){
	safe(position[0], position[1]);
	while (1){
		if (face_edge()){
			if (position[0]==0){
				left();
			}
			else{
				right();
			}
        }
		if (d%4 == 0 || d%4 == -4){
            position[0] += 1;
            move();
            break;
        }
        else if (d%4 == 1 || d%4 ==-3){
            position[1] += 1;
            move();
            break;
        }
        else if (d%4 == 2 || d%4 ==-2){
            position[0] -= 1;
            move();
            break;
        }
        else if (d%4 == 3 || d%4 ==-1){
            position[1] -= 1;
            move();
            break;
        }
	}
    putCar(position[0], position[1]);
}

void move_back(){
    safe(position[0], position[1]);
    if (d%4 == 0 || d%4==-4){
        position[0] -= 1;
        backup();
    }
    else if (d%4 == 1 || d%4==-3){
        position[1] -= 1;
        backup();
    }
    else if (d%4 == 2 || d%4==-2){
        position[0] += 1;
        backup();
    }
    else if (d%4 == 3 || d%4==-1){
        position[1] += 1;
        backup();
    }
    putCar(position[0],position[1]);
}

void that(int x, int y){
    while (position[0]!=x || position[1]!=y){
        if (x<=position[0]){
            while ((bd[position[0]-1][position[1]] == 9 ||bd[position[0]-1][position[1]] ==4||bd[position[0]-1][position[1]] ==2) && position[0]!=x){
                if (d%4 == 0 || d%4==-4){
                    left();
                    left();
                }
                else if (d%4 == 1 || d%4==-3){
                    right();
                }
                else if (d%4 == 3 || d%4==-1){
                    left();
                }
                if (bd[position[0]-1][position[1]]==2){
                    printf("FIRE!!!!");
                }
                move_forward();
                printBd();
                printf("direction: %d",d);
            }
            if (y<=position[1]){
                while ((bd[position[0]][position[1]-1]==9 ||bd[position[0]][position[1]-1]== 4 || bd[position[0]][position[1]-1]==2)&& position[1]!=y){
                    if (d%4 == 1 || d%4==-3){
                        left();
                        left();
                    }
                    else if (d%4 == 2 || d%4==-2){
                        right();
                    }
                    else if (d%4 == 0 || d%4==-4){
                        left();
                    }
                    if (bd[position[0]][position[1]-1]==2){
                        printf("FIRE!!!!");
                    }
                    move_forward();
                    printBd();
                    printf("direction: %d",d);
                    
                }
            }
            else if (y>=position[1]){
                while ((bd[position[0]][position[1]+1]==9 || bd[position[0]][position[1]+1]==4 ||bd[position[0]][position[1]+1]==2) && position[1]!=y){
                    if (d%4 == 3 || d%4==-1){
                        left();
                        left();
                    }
                    else if (d%4 == 2 || d%4==-2){
                        left();
                    }
                    else if (d%4 == 0 || d%4==-4){
                        right();
                    }
                    if (bd[position[0]][position[1]+1]==2){
                        printf("FIRE!!!!");
                    }
                    move_forward();
                    printBd();
                    printf("direction: %d",d);
                }
                
            }
        }
        else if (x>=position[0]){
            while ((bd[position[0]+1][position[1]] == 9 || bd[position[0]+1][position[1]] == 4 || bd[position[0]+1][position[1]]==2)&& position[0]!=x){
                if (d%4 == 2 || d%4==-2){
                    left();
                    left();
                }
                else if (d%4 == 1 || d%4==-3){
                    left();
                }
                else if (d%4 == 3 || d%4==-1){
                    right();
                }
                if (bd[position[0]+1][position[1]]==2){
                    printf("FIRE!!!!");
                }
                move_forward();
                printBd();
                printf("direction: %d",d%4);
            }
        }
        
        if (y<=position[1]){
            while ((bd[position[0]][position[1]-1]==9 || bd[position[0]][position[1]-1]==4 || bd[position[0]][position[1]-1]==2)&& position[1]!=y){
                if (d%4 == 1 || d%4==-3){
                    left();
                    left();
                }
                else if (d%4 == 2 || d%4==-2){
                    right();
                }
                else if (d%4 == 0 || d%4==-4){
                    left();
                }
                if (bd[position[0]][position[1]-1]==2){
                    printf("FIRE!!!!");
                }
                move_forward();
                printBd();
                printf("direction: %d",d);
                
                
            }
        }
        if (y<=position[1]){
            while ((bd[position[0]][position[1]-1]==9 ||bd[position[0]][position[1]-1]== 4 ||bd[position[0]][position[1]-1]==2)&& position[1]!=y){
                if (d%4 == 1 || d%4==-3){
                    left();
                    left();
                }
                else if (d%4 == 2 || d%4==-2){
                    right();
                }
                else if (d%4 == 0 || d%4==-4){
                    left();
                }
                if (bd[position[0]][position[1]-1]==2){
                    printf("FIRE!!!!");
                }
                move_forward();
                printBd();
                printf("direction: %d",d);
            }
        }
        else if (y>=position[1]){
            while ((bd[position[0]][position[1]+1]==9 || bd[position[0]][position[1]+1]==4 ||bd[position[0]][position[1]+1]==2) && position[1]!=y){
                if (d%4 == 3 || d%4==-1){
                    left();
                    left();
                }
                else if (d%4 == 2 || d%4==-2){
                    left();
                }
                else if (d%4 == 0 || d%4==-4){
                    right();
                }
                if (bd[position[0]][position[1]-1]==2){
                    printf("FIRE!!!!");
                }
                move_forward();
                printBd();
                printf("direction: %d",d%4);
                
            }
            
        }
    }
    
}

int count_th(int x){
    int num = 0,i,j,k;
    for (i=0;i<4;i++)
    {
        for (j=0;j<4;j++)
        {
            for (k=0;k<4;k++)
            {
                if (poss[i][j][k]==x)
                    num++;
            }
        }
    }
    return num;
}

void clear_one(int m, int n){
    for (int i=0;i<4;i++)
    {
        poss[m][n][i] = 0; // 注意 m n
    }
}

void clear_th(int x){
	int i,j,k;
    for (i=0;i<4;i++)
    {
        for (j=0;j<4;j++)
        {
            for (k=0;k<4;k++)
            {
                if (poss[i][j][k]==x)
                    poss[i][j][k]=0;
            }
        }
    }
}

void find_th(int x){
	int i,j,k;
    if (count_th(x) == 1){
        for (i=0;i<4;i++)
        {
            for (j=0;j<4;j++)
            {
                for (k=0;k<4;k++)
                {
                    if (poss[i][j][k]==x){
                        if (bd[i][j]!=9){
                            bd[i][j] = x;
                            clear_th(x);
                        }
                    }
                }
            }
        }
    }
}

int know_th(int x){
	int i,j;
    for (i=0;i<4;i++)
    {
        for (j=0;j<4;j++)
        {
            if (bd[i][j]==x){
                return 1;
            }
        }
    }
    return 0;
}

int count(int poss[4][4][4], int m, int n){
    int k=0;
    int i;
    for (i=0; i<4; i++){
        if (poss[m][n][i] != 0)
            k++;
    }
    return k;
}

void mark_adjacency(int signal, int x, int y){
	int adj[4][2] = {{position[0]+1,position[1]},{position[0]-1,position[1]},{position[0],position[1]+1},{position[0],position[1]-1}};
   	int i,j;
   	for (i=0;i<4;i++){
   		int m = adj[i][0];
        int n = adj[i][1];

        if (m>3 || m<0 || n>3 || n<0)
        {
            continue;
        }
        else
        {
            if (signal == 0)
            {
                bd[m][n] = 9;
                clear_one(m, n);
            }

            else if (signal == 1)
            {
                if (bd[m][n] == 0) // if unknown
                {
                	int p=0;
                    for (j=0;j<4;j++)
                    {
                        if (poss[m][n][j] == 1)
                        {
                            bd[m][n] = 1;
                            clear_one(m,n);
                            find_th(4);
                            find_th(2);
                            p++;
                            break;
                        }
                    }
                    
                    if (p==0)
                    {
                        poss[m][n][count(poss,m,n)] = 1;
                    }
                }
            }

            else if (signal == 2)
            {            	
                if (bd[m][n] == 0)
                {    
                	int p=0;
                    for (j=0;j<4;j++) //i<????
                    {
                        if (poss[m][n][j] == 2)
                        {
                            bd[m][n] = 2;
                            clear_one(m,n);
                            clear_th(2);
                            find_th(4);
                            p++;
                            break;
                        }
                    }
                    
                    if (p==0)
                    {
                        poss[m][n][count(poss,m,n)] = 2;
                    }
                }
            }

            else if (signal == 3)
            {

                if (bd[m][n] == 0)
                {
                	int p=0;
                    for (j=0;j<4;j++) //i<????
                    {
                        if (poss[m][n][j] == 2)
                        {
                            bd[m][n] = 2;
                            clear_one(m,n);
                            clear_th(2);
                            find_th(4);
                            p++;
                            break;
                        }
                    }
                    
                    if (p==0)
                    {
                        poss[m][n][count(poss,m,n)] = 2;
                    }
                }
                
                if (bd[m][n] == 0) // if unknown
                {
                	int p=0;
                    for (j=0;j<4;j++)
                    {
                        if (poss[m][n][j] == 1)
                        {
                            bd[m][n] = 1;
                            clear_one(m,n);
                            find_th(4);
                            find_th(2);
                            p++;
                            break;
                        }
                    }
                    
                    if (p==0)
                    {
                        poss[m][n][count(poss,m,n)] = 1;
                    }
                }
            }

            else if (signal == 4)
            {
                if (bd[m][n] == 0)
                {
                    int p = 0;
                    for (j=0;j<4;j++)
                    {
                        if (poss[m][n][j] == 4)
                        {
                            bd[m][n] = 4;
                            clear_one(m,n);
                            clear_th(4);
                            find_th(2);
                            p++;
                            break;
                        }
                    }
                    
                    if ( p==0)
                    {
                        poss[m][n][count(poss,m,n)] = 4;
                    }
                }
            }

            else if (signal == 5)
            {
            	if (bd[m][n] == 0)
                {
                    int p = 0;
                    for (j=0;j<4;j++)
                    {
                        if (poss[m][n][j] == 4)
                        {
                            bd[m][n] = 4;
                            clear_one(m,n);
                            clear_th(4);
                            find_th(2);
                            p++;
                            break;
                        }
                    }
                    
                    if ( p==0)
                    {
                        poss[m][n][count(poss,m,n)] = 4;
                    }
                }


                if (bd[m][n] == 0) // if unknown
                {
                	int p=0;
                    for (j=0;j<4;j++)
                    {
                        if (poss[m][n][j] == 1)
                        {
                            bd[m][n] = 1;
                            clear_one(m,n);
                            find_th(4);
                            find_th(2);
                            p++;
                            break;
                        }
                    }
                    
                    if (p==0)
                    {
                        poss[m][n][count(poss,m,n)] = 1;
                    }
                }
            }

            else if (signal == 6)
            {
            	if (bd[m][n] == 0)
                {
                    int p = 0;
                    for (j=0;j<4;j++)
                    {
                        if (poss[m][n][j] == 4)
                        {
                            bd[m][n] = 4;
                            clear_one(m,n);
                            clear_th(4);
                            find_th(2);
                            
                            p++;
                            break;
                        }
                    }
                    
                    if ( p==0)
                    {
                        poss[m][n][count(poss,m,n)] = 4;
                    }
                }

                if (bd[m][n] == 0)
                {    
                	int p=0;
                    for (j=0;j<4;j++) //i<????
                    {
                        if (poss[m][n][j] == 2)
                        {
                            bd[m][n] = 2;
                            clear_one(m,n);
                            clear_th(2);
                            find_th(4);
                            p++;
                            break;
                        }
                    }
                    
                    if (p==0)
                    {
                        poss[m][n][count(poss,m,n)] = 2;
                    }
                }
            }

            else if (signal == 7)
            {
            	if (bd[m][n] == 0)
                {
                    int p = 0;
                    for (j=0;j<4;j++)
                    {
                        if (poss[m][n][j] == 4)
                        {
                            bd[m][n] = 4;
                            clear_one(m,n);
                            find_th(4);
                            find_th(2);
                            clear_th(4);
                            p++;
                            break;
                        }
                    }
                    
                    if ( p==0)
                    {
                        poss[m][n][count(poss,m,n)] = 4;
                    }
                }

            	if (bd[m][n] == 0)
                {    
                	int p=0;
                    for (j=0;j<4;j++) //i<????
                    {
                        if (poss[m][n][j] == 2)
                        {
                            bd[m][n] = 2;
                            clear_one(m,n);
                            clear_th(2);
                            find_th(4);
                            p++;
                            break;
                        }
                    }
                    
                    if (p==0)
                    {
                        poss[m][n][count(poss,m,n)] = 2;
                    }
                }

                if (bd[m][n] == 0) // if unknown
                {
                	int p=0;
                    for (j=0;j<4;j++)
                    {
                        if (poss[m][n][j] == 1)
                        {
                            bd[m][n] = 1;
                            clear_one(m,n);
                            find_th(4);
                            find_th(2);
                            p++;
                            break;
                        }
                    }
                    
                    if (p==0)
                    {
                        poss[m][n][count(poss,m,n)] = 1;
                    }
                }
            }
   		}
    }
}

void turn_and_move(){
	int near[8][2] = {{position[0]+1,position[1]},{position[0],position[1]+1},{position[0],position[1]-1},{position[0]+1,position[1]+1},{position[0]-1,position[1]-1},{position[0]+1,position[1]-1},{position[0]-1,position[1]+1},{position[0]-1,position[1]}};

	int i;
    int p=0;
	for (i=0;i<8;i++){
		int m=near[i][0];
		int n=near[i][1];
        
        if (!(m>3||m<0||n>3||n<0)){
            if (bd[m][n]==9 && path[m][n]==0){
                printf("%d %d\n",m,n);
                that(m,n);
                p++;
                break;
            }
        }
	}
    
    if (p==0){
        move_back();
    }
}

int main(){

	init(0,0);
	printBd();
	int signal;
	OutputInit();

	while(1)
	{
		scanf("%d",&signal);
//		if (path[position[0]][position[1]]==0){
			mark_adjacency(signal,position[0],position[1]);
//		}
		
		if (signal >= 8){
			printBd();
			printf("Found gold\n");
			break;
		}
		else{
            find_th(4);
//            find_th(2);
			if (know_th(4)){
                int i,j;
                int p=0;
                for (i=0;i<4;i++)
                {
                    for (j=0;j<4;j++)
                    {
                        if (bd[i][j]==4){
                            that(i,j);
                            p++;
                            break;
                            
                        }
                        
                        if (p!=0){
                            break;
                        }
                    }
                }
			}
            else if (know_th(2)){
                int i,j;
                int p=0;
                for (i=0;i<4;i++)
                {
                    for (j=0;j<4;j++)
                    {
                        if (bd[i][j]==2){
                            printf("%d %d\n",i,j);
                            printBd();
                            that(i,j);
                            // printf("%d %d",position[0],position[1]);
                            printf("FIRE!!!");
                            p++;
                            break;
                        }
                        if (p!=0){
                            break;
                        }
                    }
                }
            }
			else{
				if (signal == 0){
					move_forward();
				}

				else if (signal == 1){
					turn_and_move();
				}

				else if (signal == 2 || signal ==3){
					int i,p=0;
					for (i=0; i<4; i++)
                    {
                       	int adj[4][2] = {{position[0]+1,position[1]},{position[0]-1,position[1]},{position[0],position[1]+1},{position[0],position[1]-1}};
                        if (bd[ adj[i][0] ][ adj[i][1] ] == 2){
                            //kill
                            bd[ adj[i][0] ][ adj[i][1] ] = 9;
                            that(adj[i][0], adj[i][1]);
                            p++;
                            break;
                        }
                    }

                    if (p == 0){
                        turn_and_move();
                    }
				}
                
                else if (signal==4){
                    move_forward();
                }
                
				else if ( signal == 5 || signal == 6 || signal == 7){
                    int p=0;
                    int adj[4][2] = {{position[0]+1,position[1]},{position[0]-1,position[1]},{position[0],position[1]+1},{position[0],position[1]-1}};
                    for (int i=0; i<4; i++)
                    {
                        if (bd[ adj[i][0] ][ adj[i][0] ] == 4)
                        {
                            that(adj[i][0], adj[i][1]);
                            p++;
                            break;
                        }
                        
                        else if (bd[ adj[i][0] ][ adj[i][0] ] == 2)
                        {
                            // kill
                            bd[ adj[i][0] ][ adj[i][1] ] = 9;
                            p++;
                            that(adj[i][0], adj[i][1]);
                            break;
                        }
                    }
                
                    if (p == 0){
                        turn_and_move();
                    }
                } 
			}
		}
        path[position[0]][position[1]]=1;
		printBd();
		printf("\nDirection: %d\n\n",d%4);
	}
	that(0,0);
	OutputExit();
	return 0;
}