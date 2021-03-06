/* CPSC 599 - Assignment 2
 * By: Yue Chen, Laura Berry, Andrew Lata
 * 
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
		mvprintw(13,6,_("X Wins!"));
	}
	else if(opcode==6)
	{
		mvprintw(13,6,_("O Wins!"));
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

void initVBoard() // Initialize the virtual board to blank -- BROKEN
{
	int x=0;
	int y=0;
//	board = {{'E','E','E'},{'E','E','E'},{'E','E','E'}};
	while(x<3)
	{
		while(y<3)
		{
			board[x][y]=EMPTY; // Set the space on the board with an invalid character
			y++;
		}
		x++;
	}
	return;
}

void testDraw() // Just a sanity check
{
	mvprintw(6,10,"X"); // 6,10
	mvprintw(6,12,"X");
	move(13,6);
	refresh();	
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

void getComputerInput()
{
	messages(3); // clear player's prompts
	// **ADD** Computer player code, include scripting abilitiy
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
		else if(board[0][1]=='X' && board[2][1]=='X')
		{
			return 'X'; // If vertical line | X wins
		}
		else if(board[0][2]=='X' && board[2][0]=='X')
		{
			return 'X'; // If diagonal line / X wins
		}
		else if(board[1][0]=='X' && board[1][2]=='X')
		{
			return 'X'; // If horizontal line - X wins
		}
	}
	else if(mid=='O')
	{
		if(board[0][0]=='O' && board[2][2]=='O')
		{		
			return 'O'; // If diagonal line \ X wins
		}
		else if(board[0][1]=='O' && board[2][1]=='O')
		{
			return 'O'; // If vertical line | X wins
		}
		else if(board[0][2]=='O' && board[2][0]=='O')
		{
			return 'O'; // If diagonal line / X wins
		}
		else if(board[1][0]=='O' && board[1][2]=='O')
		{
			return 'O'; // If horizontal line - X wins
		}
	}
	else if(board[0][0]=='X')
	{
		if(board[0][1]=='X' && board[0][2]=='X')
		{
			return 'X';
		}
		else if(board[1][0]=='X' && board[2][0]=='X')
		{
			return 'X';
		}
	}
	else if(board[0][0]=='O')
	{
		if(board[0][1]=='O' && board[0][2]=='O')
		{
			return 'O';
		}
		else if(board[1][0]=='O' && board[2][0]=='O')
		{
			return 'O';
		}
	}
	else if(board[2][2]=='X')
	{
		if(board[2][0]=='X' && board[2][1]=='X')
		{
			return 'X';
		}
		else if(board[1][2]=='X' && board[0][2]=='X')
		{
			return 'X';
		}
	}
	else if(board[2][2]=='O')
	{
		if(board[2][0]=='O' && board[2][1]=='O')
		{
			return 'O';
		}
		else if(board[1][2]=='O' && board[0][2]=='O')
		{
			return 'O';
		}
	}

	return 'Z';
}

int main(int argc, const char *argv[])
{
	duk_context *ctx = NULL;
	ctx = duk_create_heap_default();
	if(!ctx)
	{
		printf("Failed to create a Duktape heap.\n");
		exit(1);
	}
	if(duk_preval_file(ctx,argv[1]) != 0)
	{
		printf("Error: %s\n", duk_safe_to_string(ctx, -1);
		goto finished;
	}
	
	setlocale(LC_ALL, "");
	bindtextdomain("t3","/fr/LC_MESSAGES/t3.mo");
	bindtextdomain("t3","/es/LC_MESSAGES/t3.mo");
	bindtextdomain("t3","/de/LC_MESSAGES/t3.mo");
	textdomain("t3");

	init();    // Call function to initialize curses
	drawBoard();    // Call to draw the initial blank board
	cbreak();    // Curses call to not require enter key for input
	noecho();    // Curses call to not print input characters
	char game = 'Z';
	while(true)
	{
		getPlayerInput();    // This function call gets player input for a space to play
		getComputerInput();
		game = testWin();    // This function tests for a win state
		if(game!='Z')
		{
			break;
		}
	}
	messages(3);
	if(game=='X')
	{
		messages(5);
	}
	else if(game=='O')
	{
		messages(6);
	}

	refresh();
finished:
	duk_destroy_heap(ctx);
	mvprintw(18,6,"GAME OVER");
	return 0;
}

