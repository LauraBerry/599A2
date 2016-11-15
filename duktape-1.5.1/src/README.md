# CPSC 599 Assignment 2
# Programmed By:
# Andrew Lata, Yue Chen, Laura Berry
# 
# This program, at it's core, is a demonstration of programming for curses
# in the C language. It also incorporates internationalization for three 
# languages other than english (french, spanish, german) as well as user 
# ability to script AI techniques and strategies using the JavaScript
# language.
# 
# On the user's turn, the program waits for valid input, and will only
# update the screen when a valid key is pressed (A-C, 1-3). When a full
# set of coordinates are provided (Ex. A,3) the game piece for the player
# is drawn to the appropriate space on the screen.
# 
# The computer player's turn starts by writing the board state to a string
# that is passed to a JavaScript function. 
# The .js filename can be variable, but the function name must be 
# "strategy(input)". The string passed to JavaScript, in this example 
# "input", is a 1-d representation of the board. The script is meant to 
# parse the string to look for empty spaces denoted by the character 'E', and 
# the function is expected to return an integer index of the 'E' (a value 
# from 0 to 8) to replace with an 'O', which is then interpretted by the 
# C program.
# 
# After each of the player and the AI makes a move on the board, the win
# condition is tested for each possible 'win state' and if one of these states
# is found then the game ends and the winner is printed to the screen along 
# with a "GAME OVER" message.
