#include "Player_EF.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>


Helper::Helper()
{
	win_pos = { { // An array with cell numbers, when filling in which the game will end
	{1,2,3,4},
	{5,6,7,8},
	{9,10,11,12},
	{13,14,15,16},
	{4,8,12,16},
	{1,5,9,13},
	{2,6,10,14},
	{3,7,11,15},
	{1,6,11,16},
	{4,7,10,13}
	} };

	corners = { 1, 4, 13, 16, 0 }; // board corners positions

	curr_sit_1 = { 0,0,0,0,0,0,0,0,0,0 };
	curr_sit_2 = { 0,0,0,0,0,0,0,0,0,0 };

}

bool Helper::isFree(int field[],int pos)
{
	if (field[pos] == 0) return true;
	else return false;
}


int Helper::getCorner(int field[])
{
	int i = 0;
	int pos;
	do
	{
		pos = corners[i];
		i++;
	} while (isFree(field, pos) == false && i < 5);
	return pos;
}


void Helper::getCurrSit(int field[])
{
	// reset the arrays and move counter
	curr_sit_1 = { 0,0,0,0,0,0,0,0,0,0 }; 
	curr_sit_2 = { 0,0,0,0,0,0,0,0,0,0 };
	move_count = 0;
	//walking across the field
	for (int k = 1; k <= 16; k++)
	{
		if (field[k] != 0 && field[k] != 3) move_count++; // if there is "x" or "o"
		// walking across the array with winnig or losing lanes
		for(int i=0; i < 10; i++)
			for (int j = 0; j < 4; j++)
			{
				if (field[k] == 1 && win_pos[i][j] == k) // if the cell is occupied by player 1 and this cell is on the winning or losing line 
				{
					curr_sit_1[i]++; // increase the number of marks of player 1 on the "i" line
				}
				if (field[k] == 2 && win_pos[i][j] == k)
				{
					curr_sit_2[i]++; // increase the number of marks of player 2 on the "i" line
				}
			}
	}
	
}

//Filling in information about the player
Player_EF::Player_EF()
{
	name_of_developer = std::string("Faizrakhmanov_Emil");
	player_no = 77;
}

Player_EF::~Player_EF()
{
	
}

/*Calculation of move position.*/
int Player_EF::getNextMove(int fld_status[])
{
	srand((unsigned)time(NULL));
	int toplace_pos; // chose position variable
	Helper helper; // help functions object

	helper.getCurrSit(fld_status); // Calculating current situation on the board.

	/* 
	* If this is the first 4 turns of the game, the player will trye to fill 2 corners.
	*/
	if (helper.move_count <= 4)
	{
		toplace_pos = helper.getCorner(fld_status);
		if (toplace_pos == 0) {} //if corners is not available, do nothing and try choose other positions
		else
		{
			return toplace_pos; // return corner position index
		}
	}
	/*
	* Calculating profitable position if it's not first 4 moves in the game or all corners are busy*/
	for (int i = 0; i < 10; i++) //walking across the arrays with players moves on the lane
	{
		if (helper.curr_sit_1[i] == 3 || helper.curr_sit_2[i] == 3) // check if there is several elements in lane close to loss or win.
		{
			//if we find 3 moves in the lane, we need to block other player or make our move to win
			for (int j = 0; j < 4; j++)//walking across positions in the "i" lane
			{
				if (helper.isFree(fld_status, helper.win_pos[i][j]) == true) //check if current cell on the lane is available
				{
					toplace_pos = helper.win_pos[i][j]; // assign the variable position returned by the function with a free cell in the line
					return toplace_pos;
				}
			}	
		}
	}
	/*
	* If there is no situation close to the end of the game (win or loss),
	* Choose the first avaiable element on the lane*/
	for (int i=0; i<10; i++) // walk through the array with line coordinates
		for (int j = 0; j < 4; j++)
		{
			/*if position is available and there is free cells, choose the positin and return it*/
			if (helper.isFree(fld_status, helper.win_pos[i][j]) == true && fields_left(fld_status)) 																
			{
				toplace_pos = helper.win_pos[i][j];
				return toplace_pos;
			} 
		}//if there is no available positions, choose another lane
	toplace_pos = -1; // if we can't find any available moves, return -1
	return toplace_pos;
}