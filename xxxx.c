//
//  main.c
//  xxxx
//
//  Created by 刘晓艺 on 12/6/16.
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
int bd[4][4] = {{9,9,0,0},{9,0,0,0},{0,0,0,0},{0,0,0,0}};
// board:
// 0:unknown 1:hole 2:wumpus 4:gold 9:safe -1:car

int poss[4][4][4];
int end=0;

<<<<<<< HEAD
=======
void forward()
{
	ResetAllTachoCounts(OUT_AD);
	SetPower(OUT_A, -10);
	SetPower(OUT_D, -10);
	//Then we turn the motors on
	On(OUT_AD);
	while (MotorRotationCount(OUT_A)> 150)
	{

	}
	Off(OUT_ALL);
}
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435

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
    
    forward();
    
    return; 
}

<<<<<<< HEAD
void forward();
{
    ResetAllTachoCounts(OUT_AD);
    SetPower(OUT_A, -10);
    SetPower(OUT_D, -10);
    //Then we turn the motors on
    On(OUT_AD);
    while (MotorRotationCount(OUT_A)> 150)
    {
        
    }
    Off(OUT_ALL);
}
=======
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435

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
    while (MotorRotationCount(OUT_A)> 150)
    {
        
    }
    Off(OUT_ALL);
    
    return;
}

void move_left()
{
    
    ResetAllTachoCounts(OUT_AD);
    SetPower(OUT_A, 10);
    SetPower(OUT_D, -10);
    On(OUT_AD);
    while (MotorRotationCount(OUT_D)> -155)
    {
        
    }
    Off(OUT_ALL);
    move();
}

void other_left()
{
    ResetAllTachoCounts(OUT_AD);
    SetPower(OUT_A, -10);
    SetPower(OUT_D, 10);
    //Then we turn the motors on
    On(OUT_AD);
    while (MotorRotationCount(OUT_A)> -155)
    {
        
    }
    Off(OUT_ALL);
    move();
}

void safe(int x,int y){
    bd[x][y] = 9;
}

void putCar(int x,int y) // for text only
{
    bd[x][y] = -1;
}

void init(int x, int y)
{
    position[0]=x;
    position[1]=y;
    putCar(x,y); // for test only
}

void printBd() // for test only
{
    printf("\n");
<<<<<<< HEAD
    for(int i=3;i>=0;i--){
        for(int j=0;j<4;j++){
=======
	int i, j;
    for(i=3;i>=0;i--){
        for(j=0;j<4;j++){
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
            printf("%2d ",bd[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int face_edge()
{
    if (position[0] == 3 && d%4 == 0)
        return 1;
    else if (position[0] == 0 && d%4 == 2)
        return 1;
    else if (position[1] == 3 && d%4 == 1)
        return 1;
    else if (position[1] == 0 && d%4 == 3)
        return 1;
    else
        return 0;
}

void left()
{
    d -= 1;
    move_left();
}

void right()
{
    d += 1;
    other_left();
}

void move_forward()
{
    safe(position[0], position[1]);
    while (1) {
         if (face_edge()){
             if (position[0]==0){
                 left();
             }
             else{
                right();
             }           
         }
    else{
        if (d%4 == 0){
            position[0] += 1;
            move();
            break;
        }
        else if (d%4 == 1){
            position[1] += 1;
            move();
            break;
        }
        else if (d%4 == 2){
            position[0] -= 1;
            move();
            break;
        }
        else if (d%4 == 3){
            position[1] -= 1;
            move();
            break;
        }
    }
    }
    
    putCar(position[0], position[1]);
}

void move_back()
{
    safe(position[0], position[1]);
    d = d+2;
    while(1){
        if (face_edge()){
        left();
    }
        else{
            d = d+2;
            if (d%4 == 0){
                position[0] -= 1;
                backup();
                break;
            }
            else if (d%4 == 1){
                position[1] -= 1;
                backup();
                break;
            }
            else if (d%4 == 2){
                position[0] += 1;
                backup();
                break;
            }
            else if (d%4 == 3){
                position[1] += 1;
                backup();
                break;
            }
        }
        }
    putCar(position[0],position[1]);
}

void move_to_that(int x, int y)
{
    safe(x,y);
    safe(position[0], position[1]);
    if (d%4 == 1){
        left();
    }
    else if (d%4 == 2){
        left();
        left();
    }
    else if (d%4 == 3){
        right();
    }

    if (x == position[0]-1){
        move_back();
    }
    else if (x == position[0]+1){
        move_forward();
    }
    else if (y == position[1]-1){
        left();
        move_forward();
    }
    else if (y == position[1]+1){
        right();
        move_forward();
    }
    // position[0] = x;
    // position[1] = y;
    // putCar(position[0],position[1]);
}

void turn_and_move()
{
    int x = position[0];
    int y = position[1];
    
    safe(x, y);
    move_back();
    

    if ((y == 0 || x==3) && x!=0){
        right();
        move_forward();
    }
    else if ((x == 0 || y==3) && y!=0)
    {
        left();
        move_forward();
    }
    else if (x == 0 && y == 0){
        d = 1;
        move_forward();
    }
    else if (x==1 && y==1){
        d = 2;
        move_forward();
        d = 1;
    }
    else{
        right();
        move_forward();
    }
}

 int count_gold()
{
<<<<<<< HEAD
    int num = 0;
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            for (int k=0;k<4;k++)
=======
    int num = 0, i, j, k;
    for (i=0;i<4;i++)
    {
        for (j=0;j<4;j++)
        {
            for (k=0;k<4;k++)
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
            {
                if (poss[i][j][k]==4)
                    num++;
            }
        }
    }
    return num;
}

int count_wumpus()
{
<<<<<<< HEAD
    int num = 0;
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            for (int k=0;k<4;k++)
=======
    int num = 0,i, j, k;
    for (i=0;i<4;i++)
    {
        for (j=0;j<4;j++)
        {
            for (k=0;k<4;k++)
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
            {
                if (poss[i][j][k]==2)
                    num++;
            }
        }
    }
    return num;
}

void clear_(int m, int n)
{
<<<<<<< HEAD
    for (int i=0;i<4;i++)
=======
	int i;
    for (i=0;i<4;i++)
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
    {
        poss[m][n][i] = 0; // 注意 m n
    }
}

void find_gold()
{
<<<<<<< HEAD
    if (count_gold() == 1){
        for (int i=0;i<4;i++)
        {
            for (int j=0;j<4;j++)
            {
                for (int k=0;k<4;k++)
=======
	int i, j, k;
    if (count_gold() == 1){
        for (i=0;i<4;i++)
        {
            for (j=0;j<4;j++)
            {
                for (k=0;k<4;k++)
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                {
                    if (poss[i][j][k]==4){
                        if (bd[i][j]!=9){
                            bd[i][j] = 4;
                        }
                    }
                    
                }
            }
        }
    }
}

void find_wumpus()
{
<<<<<<< HEAD
    if (count_wumpus() == 1){
        for (int i=0;i<4;i++)
        {
            for (int j=0;j<4;j++)
            {
                for (int k=0;k<4;k++)
=======
	int i, j, k;
    if (count_wumpus() == 1)
	{
        for (i=0;i<4;i++)
        {
            for (j=0;j<4;j++)
            {
                for (k=0;k<4;k++)
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                {
                    if (poss[i][j][k]==2)
                        if (bd[i][j]!=9){
                        bd[i][j] = 2;
                        }
                }
            }
        }
    }
}

int know_gold()
{
<<<<<<< HEAD
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
=======
	int i, j;
    for (i=0;i<4;i++)
    {
        for (j=0;j<4;j++)
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
        {
            if (bd[i][j]==4)
                return 1;
        }
    }
    return 0;
}

int count(int poss[4][4][4],int m, int n)
{
<<<<<<< HEAD
    int k=0;
    for (int i=0; i<4; i++)
=======
    int k=0, i;
    for (i=0; i<4; i++)
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
    {
        if (poss[m][n][i] != 0)
            k++;
    }
    return k;
}

void mark_adjacency(int signal, int x, int y)
{
<<<<<<< HEAD
    int adj[4][2] = {{position[0]+1,position[1]},{position[0]-1,position[1]},{position[0],position[1]+1},{position[0],position[1]-1}};
    for (int i=0; i<4; i++)
=======
	int i;
    int adj[4][2] = {{position[0]+1,position[1]},{position[0]-1,position[1]},{position[0],position[1]+1},{position[0],position[1]-1}};
    for (i=0; i<4; i++)
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
    {
        int m = adj[i][0];
        int n = adj[i][1];
        int p = 0;
        
        if (m>3 || m<0 || n>3 || n<0)
        {
            continue;
        }
        else
        {
            if (signal == 0)
            {
                bd[m][n] = 9;
            }
            
            else if (signal == 1)
            {
                if (bd[m][n] == 0) // if unknown
                {
<<<<<<< HEAD
                    for (int i=0;i<4;i++)
=======
                    for (i=0;i<4;i++)
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                    {
                        if (poss[m][n][i] == 1)
                        {
                            bd[m][n] = 1;
                            clear_(m,n);
                            find_gold();
                            find_wumpus();
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
<<<<<<< HEAD
                    for (int i=0;i<4;i++) //i<????
=======
                    for (i=0;i<4;i++) //i<????
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                    {
                        if (poss[m][n][i] == 2)
                        {
                            bd[m][n] = 2;
                            clear_(m,n);
                            find_gold();
                            find_wumpus();
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
<<<<<<< HEAD
                    for (int i=0;i<4;i++) //i<????
=======
                    for (i=0;i<4;i++) //i<????
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                    {
                        if (poss[m][n][i] == 2)
                        {
                            bd[m][n] = 2;
                            clear_(m,n);
                            find_gold();
                            find_wumpus();
                            p++;
                            break;
                        }
                    }
                    
                    if (p==0)
                    {
                        poss[m][n][count(poss,m,n)] = 2;
                    }
                }
                
                if (bd[m][n] == 0)
                {
<<<<<<< HEAD
                    for (int i=0;i<4;i++) //i<????
=======
                    for (i=0;i<4;i++) //i<????
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                    {
                        if (poss[m][n][i] == 1)
                        {
                            bd[m][n] = 1;
                            clear_(m,n);
                            find_gold();
                            find_wumpus();
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
<<<<<<< HEAD
                    for (int i=0;i<4;i++)
=======
                    for (i=0;i<4;i++)
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                    {
                        if (poss[m][n][i] == 4)
                        {
                            bd[m][n] = 4;
                            clear_(m,n);
                            find_gold();
                            find_wumpus();
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
<<<<<<< HEAD
                    for (int i=0;i<4;i++)
=======
                    for (i=0;i<4;i++)
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                    {
                        if (poss[m][n][i] == 4)
                        {
                            bd[m][n] = 4;
                            clear_(m,n);
                            find_gold();
                            find_wumpus();
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
<<<<<<< HEAD
                    for (int i=0;i<4;i++) //i<????
=======
                    for (i=0;i<4;i++) //i<????
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                    {
                        if (poss[m][n][i] == 1)
                        {
                            bd[m][n] = 1;
                            clear_(m,n);
                            find_gold();
                            find_wumpus();
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
<<<<<<< HEAD
                    for (int i=0;i<4;i++)
=======
                    for (i=0;i<4;i++)
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                    {
                        if (poss[m][n][i] == 4)
                        {
                            bd[m][n] = 4;
                            clear_(m,n);
                            find_gold();
                            find_wumpus();
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
<<<<<<< HEAD
                    for (int i=0;i<4;i++) //i<????
=======
                    for (i=0;i<4;i++) //i<????
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                    {
                        if (poss[m][n][i] == 2)
                        {
                            bd[m][n] = 2;
                            clear_(m,n);
                            find_gold();
                            find_wumpus();
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
<<<<<<< HEAD
                    for (int i=0;i<4;i++)
=======
                    for (i=0;i<4;i++)
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                    {
                        if (poss[m][n][i] == 4)
                        {
                            bd[m][n] = 4;
                            clear_(m,n);
                            find_gold();
                            find_wumpus();
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
<<<<<<< HEAD
                    for (int i=0;i<4;i++) //i<????
=======
                    for (i=0;i<4;i++) //i<????
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                    {
                        if (poss[m][n][i] == 2)
                        {
                            bd[m][n] = 2;
                            clear_(m,n);
                            find_gold();
                            find_wumpus();
                            p++;
                            break;
                        }
                    }
                    
                    if (p==0)
                    {
                        poss[m][n][count(poss,m,n)] = 2;
                    }
                }
                
                if (bd[m][n] == 0)
                {
<<<<<<< HEAD
                    for (int i=0;i<4;i++) //i<????
=======
                    for (i=0;i<4;i++) //i<????
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                    {
                        if (poss[m][n][i] == 1)
                        {
                            bd[m][n] = 1;
                            clear_(m,n);
                            find_gold();
                            find_wumpus();
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

void move_d(int dir){
    safe(position[0],position[1]);
    if(dir==0){
        position[0]-=1;
    }else if(dir==1){
        position[1]+=1;
    }else if(dir==2){
        position[0]+=1;
    }else if(dir==3){
        position[1]-=1;
    }
    if(bd[position[0]][position[1]]==4){
        end=1;
    }
    move_to_that(position[0], position[1]);
//    putCar(position[0],position[1]);
}

void back(){
    int step =0;
    
    while(1){
        int x=position[0];
        int y=position[1];
        int posWays[4][2] = {{x-1,y},{x,y+1},{x+1,y},{x,y-1}};
        int i=rand()%4;
        int a=posWays[i][0];
        int b=posWays[i][1];
        if(!(a<0||a>3||b<0||b>3)){
            if(bd[a][b]==2 || bd[a][b]==1 || bd[a][b] == 0){
                for( i=0;i<4;i++){
                    int a=posWays[i][0];
                    int b=posWays[i][1];
                    if(!(a<0||a>3||b<0||b>3)){
                        if(bd[a][b]==9){
                            break;
                        }
                    }
                }
            }
            move_d(i);
            step++;
            if(position[0]==0 && position[1]==0){
                printf("%d\n",step );
                printBd();
                break;
            }
        }   
    }
}

int main()
{
    init(0,0); //initialize
    printBd();
    int signal;
    int p = 0;
    
    while (1)
    {
        scanf("%d",&signal);
        mark_adjacency(signal, position[0], position[1]);
        
        if (signal == 8)
        {
            printBd();
            printf("Found gold\n");
            break;
        }
        else
        {
<<<<<<< HEAD
            if (know_gold())
            {   printBd();
                int p=0;
                int adj[4][2] = {{position[0]+1,position[1]},{position[0]-1,position[1]},{position[0],position[1]+1},{position[0],position[1]-1}};
                for (int i=0;i<4;i++)
=======
            if (know_gold() && (signal == 4 || signal == 0))
            {   printBd();
                int p=0, i;
                int adj[4][2] = {{position[0]+1,position[1]},{position[0]-1,position[1]},{position[0],position[1]+1},{position[0],position[1]-1}};
                for (i=0;i<4;i++)
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                {
                    if (bd[adj[i][0]][adj[i][1]] == 4)
                    {
                        move_to_that(adj[i][0], adj[i][1]);
                        p++;
                        break;
                    }
                }
                if (p==0){
                    move_back();
<<<<<<< HEAD
                    for (int i=0;i<4;i++){
=======
					int i;
                    for (i=0;i<4;i++){
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                        if (bd[adj[i][0]][adj[i][1]] == 4)
                    {
                        move_to_that(adj[i][0], adj[i][1]);
                        break;
                    }
                    }
                    
                }
            }
            else
            {
                if (signal == 0){

                    move_forward();
                }
            
                else if (signal == 1)
                    {
                        turn_and_move();
                    }
                
                else if (signal == 2 || signal == 3){
<<<<<<< HEAD

                    for (int i=0; i<4; i++)
=======
					int i;
                    for (i=0; i<4; i++)
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                    {
                        int adj[4][2] = {{position[0]+1,position[1]},{position[0]-1,position[1]},{position[0],position[1]+1},{position[0],position[1]-1}};
                        if (bd[ adj[i][0] ][ adj[i][1] ] == 2){
                            //kill
                            bd[ adj[i][0] ][ adj[i][1] ] = 9;
                            move_to_that(adj[i][0], adj[i][1]); // 改
                            p++;
                            break;
                        }
                    }
                
                    if (p == 0){
                        turn_and_move();
                    }
                    }
                
                else if (signal == 4 || signal == 5 || signal == 6 || signal == 7){
<<<<<<< HEAD
                    int p=0;
                    int adj[4][2] = {{position[0]+1,position[1]},{position[0]-1,position[1]},{position[0],position[1]+1},{position[0],position[1]-1}};
                    for (int i=0; i<4; i++)
=======
                    int p=0, i;
                    int adj[4][2] = {{position[0]+1,position[1]},{position[0]-1,position[1]},{position[0],position[1]+1},{position[0],position[1]-1}};
                    for ( i=0; i<4; i++)
>>>>>>> b1ba03978861d9c09d5a2f596bcb608d2ec71435
                    {
                        if (bd[ adj[i][0] ][ adj[i][0] ] == 4)
                        {
                            move_to_that(adj[i][0], adj[i][1]);
                            p++;
                            break;
                        }
                        
                        else if (bd[ adj[i][0] ][ adj[i][0] ] == 2)
                        {
                            // kill
                            bd[ adj[i][0] ][ adj[i][1] ] = 9;
                            p++;
                            move_to_that(adj[i][0], adj[i][1]);
                            break;
                        }
                    }
                
                    if (p == 0){
                        turn_and_move();
                    }
                }
            }
        }
        printBd();
        printf("direction: %d\n\n",d%4);
    }
    
    back();
}

