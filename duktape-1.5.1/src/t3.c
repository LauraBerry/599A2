/* CPSC 599 - Assignment 2
 * By: Andrew Lata, Yue Chen, Laura Berry
 * 
 * gcc -std=c99 duktape.c t3.c -lm -lncurses
 */


#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include <libintl.h>
#include <locale.h>
#include "duktape.h"

#define _(STRING) gettext(STRING)

int row;
int column;
int r,c,nrows,ncols;
WINDOW *wnd;
char board[3][3] = {{'E','E','E'},{'E','E','E'},{'E','E','E'}};
int A = 6;
int B = 8;
int C = 10;
int ONE = 10;
int TWO = 12;
int THREE = 14;
char EMPTY = 'E';
char tostring[9];


void init() // Initializing tasks, run when the program starts
{
	wnd = initscr();
	
	clear();
	refresh();
	return;	
}

void messages(int opcode) // This function will be used for printing messages on screen
{ // Used to easily add in language localization
	if(opcode==1) // opcode for user space selection prompt
	{
		mvprintw(13,6,_("Choose an empty space   ")); 
		mvprintw(14,7,"( , )");
	}
	else if(opcode==2) // opcode for resetting space selection output
	{
		mvprintw(14,7,"( , )");
	}
	else if(opcode==3) // opcode for clearing player input prompt
	{
		mvprintw(13,6,"              ");
		mvprintw(14,7,"     ");
	}
	else if(opcode==4) // opcode for showing "space not blank" error
	{
		mvprintw(13,6,_("That space is not empty!"));
	}
	else if(opcode==5)
	{
		mvprintw(13,6,_("X Wins!                   "));
	}
	else if(opcode==6)
	{
		mvprintw(13,6,_("O Wins!                   "));
	}
	else if(opcode==7)
	{
		mvprintw(18,6,_("GAME OVER"));
	}
	return;
}

void drawBoard() // Draws the initial blank board
{
	move(4,8);
	addstr("  1 2 3");
	move(5,8);
	addstr(" -------");
	move(6,8);
	addstr("A| | | |");
	move(7,8);
	addstr(" -------");
	move(8,8);
	addstr("B| | | |");
	move(9,8);
	addstr(" -------");
	move(10,8);
	addstr("C| | | |");
	move(11,8);
	addstr(" -------");
	refresh();
	return;
}

int parseLetterCoord(int coord)
{
	if(coord==1)
	{
		return A;
	}
	else if(coord==2)
	{
		return B;
	}
	else if(coord==3)
	{
		return C;
	}
}

int parseNumCoord(int coord)
{
	if(coord==1)
	{
		return ONE;
	}
	else if(coord==2)
	{
		return TWO;
	}
	else if(coord==3)
	{
		return THREE;
	}
}

void updateBoard(int number, int letter, char player)    // Updates the virtual board that is used to keep track of space played
{
	int x;
	int y;

	if(number==ONE)
	{
		x = 0;
		if(letter==A)
		{
			y = 0;
		}
		else if (letter==B)
		{
			y = 1;
		}
		else if (letter==C)
		{
			y = 2;
		}
	}
	else if(number==TWO)
	{
		x = 1;
		if(letter==A)
		{
			y = 0;
		}
		else if (letter==B)
		{
			y = 1;
		}
		else if (letter==C)
		{
			y = 2;
		}
	}
	else if(number==THREE)
	{
		x = 2;
		if(letter==A)
		{
			y = 0;
		}
		else if (letter==B)
		{
			y = 1;
		}
		else if (letter==C)
		{
			y = 2;
		}
	}
	board[x][y] = player;
	return;
}

bool isBlank(int number, int letter) // Tests if a spot on the game board is empty
{
	int x;
	int y;
	char str[50];
	if(number==ONE)
	{
		x = 0;
		if(letter==A)
		{
			y = 0;
			return (board[x][y]!=EMPTY);    // Return false if the intended space is empty
		}
		else if (letter==B)
		{
			y = 1;
			return (board[x][y]!=EMPTY);    // Return false if the intended space is empty
		}
		else if (letter==C)
		{
			y = 2;
			return (board[x][y]!=EMPTY);    // Return false if the intended space is empty
		}
	}
	else if(number==TWO)
	{
		x = 1;
		if(letter==A)
		{
			y = 0;
			return (board[x][y]!=EMPTY);    // Return false if the intended space is empty
		}
		else if (letter==B)
		{
			y = 1;
			return (board[x][y]!=EMPTY);    // Return false if the intended space is empty
		}
		else if (letter==C)
		{
			y = 2;
			return (board[x][y]!=EMPTY);    // Return false if the intended space is empty
		}
	}
	else if(number==THREE)
	{
		x = 2;
		if(letter==A)
		{
			y = 0;
			return (board[x][y]!=EMPTY);    // Return false if the intended space is empty
		}
		else if (letter==B)
		{
			y = 1;
			return (board[x][y]!=EMPTY);    // Return false if the intended space is empty
		}
		else if (letter==C)
		{
			y = 2;
			return (board[x][y]!=EMPTY);    // Return false if the intended space is empty
		}
	}
	return true;    // If no match is found, return true to continue looping in getPlayerInput()
}

bool isVBlank(int x, int y)
{
	if(board[x][y]==EMPTY)
	{
		return true; // Return true if the space is empty
	}
	else
	{
		return false; // Return false if the space is not empty
	}
}

void getPlayerInput() // This function collects player input for tile to play
{
	messages(1);    // Call to print function
	bool loop = true;
	int letter = -1;
	int number = -1;
	while(loop)
	{
		char choice = getch();
		if (choice == 'a' || choice == 'A')
		{
			mvprintw(14,8,"A");
			letter = A;
		}
		else if (choice == 'b' || choice == 'B')
		{
			mvprintw(14,8,"B");
			letter = B;
		}
		else if (choice == 'c' || choice == 'C')
		{
			mvprintw(14,8,"C");
			letter = C;
		}
		else if (choice == '1')
		{
			mvprintw(14,10,"1");
			number = ONE;
		}
		else if (choice == '2')
		{
			mvprintw(14,10,"2");
			number = TWO;
		}
		else if (choice == '3')
		{
			mvprintw(14,10,"3");
			number = THREE;
		}
		
		if ((number>=0) && (letter>=0))
		{
			loop = isBlank(number,letter);
			if(loop==true)
			{
				number = -1;
				letter = -1;
				messages(2);
				messages(4);
			}
		}
	}
	updateBoard(number, letter, 'X');
	mvprintw(letter,number,"X");
	number = -1;
	letter = -1;
	messages(2);
	return;
}

char testWin() // Tests the board for win conditions and returns who won, if any, and Z if nobody wins
{
	char mid = board[1][1];
	if(mid=='X')
	{
		if(board[0][0]=='X' && board[2][2]=='X')
		{		
			return 'X'; // If diagonal line \ X wins
		}
		if(board[0][1]=='X' && board[2][1]=='X')
		{
			return 'X'; // If vertical line | X wins
		}
		if(board[0][2]=='X' && board[2][0]=='X')
		{
			return 'X'; // If diagonal line / X wins
		}
		if(board[1][0]=='X' && board[1][2]=='X')
		{
			return 'X'; // If horizontal line - X wins
		}
	}
	if(mid=='O')
	{
		if(board[0][0]=='O' && board[2][2]=='O')
		{		
			return 'O'; // If diagonal line \ X wins
		}
		if(board[0][1]=='O' && board[2][1]=='O')
		{
			return 'O'; // If vertical line | X wins
		}
		if(board[0][2]=='O' && board[2][0]=='O')
		{
			return 'O'; // If diagonal line / X wins
		}
		if(board[1][0]=='O' && board[1][2]=='O')
		{
			return 'O'; // If horizontal line - X wins
		}
	}
	if(board[0][0]=='X')
	{
		if(board[0][1]=='X' && board[0][2]=='X')
		{
			return 'X';
		}
		if(board[1][0]=='X' && board[2][0]=='X')
		{
			return 'X';
		}
	}
	if(board[0][0]=='O')
	{
		if(board[0][1]=='O' && board[0][2]=='O')
		{
			return 'O';
		}
		if(board[1][0]=='O' && board[2][0]=='O')
		{
			return 'O';
		}
	}
	if(board[2][2]=='X')
	{
		if(board[2][0]=='X' && board[2][1]=='X')
		{
			return 'X';
		}
		if(board[1][2]=='X' && board[0][2]=='X')
		{
			return 'X';
		}
	}
	if(board[2][2]=='O')
	{
		if(board[2][0]=='O' && board[2][1]=='O')
		{
			return 'O';
		}
		if(board[1][2]=='O' && board[0][2]=='O')
		{
			return 'O';
		}
	}

	return 'Z';
}

void get_coords(int a)
{
	if (a==0)
	{
		updateBoard(ONE,A, 'O');		
		mvprintw(A,ONE,"O");
		return;
	}
	else if (a==1)
	{
		updateBoard(TWO,A, 'O');		
		mvprintw(A,TWO,"O");
		return;
	}
	else if (a==2)
	{
		updateBoard(THREE,A, 'O');		
		mvprintw(A,THREE,"O");
		return;
	}
	else if(a==3)
	{
		updateBoard(ONE,B, 'O');		
		mvprintw(B,ONE,"O");
		return;
	}
	else if (a==4)
	{
		updateBoard(TWO,B, 'O');		
		mvprintw(B,TWO,"O");
		return;
	}
	else if (a==5)
	{
		updateBoard(THREE,B, 'O');		
		mvprintw(B,THREE,"O");
		return;
	}
	else if (a==6)
	{
		updateBoard(ONE,C, 'O');		
		mvprintw(C,ONE,"O");
		return;
	}
	else if (a==7)
	{
		updateBoard(TWO,C, 'O');		
		mvprintw(C,TWO,"O");
		return;
	}
	else if (a==8)
	{
		updateBoard(THREE,C, 'O');		
		mvprintw(C,THREE,"O");
		return;
	}
	return;	
}

int main(int argc, const char *argv[])
{
	setlocale(LC_ALL, "");
	bindtextdomain("t3","locale");
	textdomain("t3");

	char tempString[] = "EEEEEEEEE";

	duk_context *ctx = NULL;
	ctx = duk_create_heap_default();
	if(!ctx)
	{
		printf("Failed to create a Duktape heap.\n");
		exit(1);
	}
// The following code causes running the program to fail
	if(duk_peval_file(ctx,argv[1]) != 0)  // The argument supplied is expected to be the .js strategy to load
	{
		printf("Error: %s\n", duk_safe_to_string(ctx, -1));
		goto finished;
	}
	duk_pop(ctx); // Ignore result

	init();    // Call function to initialize curses
	drawBoard();    // Call to draw the initial blank board
	cbreak();    // Curses call to not require enter key for input
	noecho();    // Curses call to not print input characters
	char game = 'Z';
	bool comp = true;
	int tempInt = 0;
	while(true)
	{
		getPlayerInput();    // This function call gets player input for a space to play
		game = testWin();    // This function tests for a win state
		if(game!='Z')
		{
			break;	
		}

//////////////// Start js computer turn

			duk_push_global_object(ctx);
			duk_get_prop_string(ctx,-1,"strategy");
			tempInt = 0;
			for(int i = 0;i<3;i++)
			{
				for(int j = 0; j<3;j++)
				{
					tempString[tempInt] = board[j][i];
					tempInt++;
				}
			}
//			mvprintw(18,6,tempString);  // Visual confirmaltion of board string formatting properly
			duk_push_string(ctx, tempString);
			if(duk_pcall(ctx,1) != 0)
			{
				printf("Error: %s\n", duk_safe_to_string(ctx,-1));
			}
			else
			{
				int temp = duk_get_int(ctx, -1);
				get_coords(temp);
			}

//////////////// End js computer turn

		game = testWin();    // This function tests for a win state
		if(game!='Z')
		{
			break;
		}
	}
endgame:
	messages(3);
	if(game=='X')
	{
		messages(5);
	}
	else if(game=='O')
	{
		messages(6);
	}
	messages(7);
	refresh();
finished:
	duk_destroy_heap(ctx);

	return 0;
}
