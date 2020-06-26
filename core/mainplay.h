//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
//
// mainplay.h
//
// This file declares functions used in mainplay.cpp
//////////////////////////////////////////////////////////////////////

#ifndef MAINPLAY_H
#define MAINPLAY_H


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
// function used by Windows to handle window procedures


int runGame(int runMode);
// This functions opens up a DirectDraw window and, for all intents
// and purposes, "starts" a game.
// runMode = 0:  "regular" main game play screen
// runMode = 1:	 choose car screen


int Game_Init();
// Initialize things such as DirectDraw, read in mask data, initialize
// the mouse, etc.


int Read_BMPs();
// Read in all BMPs needed for game play with this function.


int Game_Shutdown();
// Release DirectDraw and deallocate memory from unused bitmaps.


int Game_Main();
// The main game loop which checks to see which which button has been
// pressed, and calculates collisions with other cars.


int check_palette(int whichPalette);
// Changes the palette to the track specified in whichPalette


void draw_Text(int howToDraw);
// Draws text on the screen
// howToDraw = -1:  draws a winner message down the bottom
// howToDraw = 0:   draws Player 1 info
// howToDraw = 1:	draws Player 2 info


int checkIfSameDirection(int direction1, int direction2);
// This is used to check if two cars are facing the same direction.
// When cars collide, this is called to determine which way 
// to bump the cars.


int choose_car();
// Instead of Game_Main(), this can be called to open up the 
// Choose Car screen.


void drawMainWindow();
// Animates the screen by updating positions of cars and power-ups



#endif
