//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
//
// mainplay.cpp : implementation file of the functions used by the
// main game loop plus other auxiliary functions.
//
//////////////////////////////////////////////////////////////////////



#include "stdafx.h"
#include "functions.h"
#include "bumpercars.h"
#include "bumpercarsDlg.h"
#include "multiplayer.h"
#include "mainplay.h"

#include <fstream.h>
#include <mmsystem.h>

//***********         Global Variable Section     ***********//

BITMAP_FILE			bmpFile;             // an 8 bit BMP file
										 // temp variable

// BITMAPS FOR MAIN PLAY
BITMAP_IMAGE		track;
BITMAP_IMAGE		gear;
BITMAP_IMAGE		medikit;
BITMAP_IMAGE		oil;
BITMAP_IMAGE		dynamite;

// BITMAPS FOR MENU SYSTEM
// These are used for the choose car screen
static BITMAP_IMAGE dark_cars;      // the background dark_cars 
static BITMAP_IMAGE goggles_norm;	// the goggles images
static BITMAP_IMAGE goggles_red;
static BITMAP_IMAGE light_cars;		// the light cars that the goggles
									// "reveal" when positioned over		

// GLOBALS ////////////////////////////////////////////////
// If EXIT is 0, we stay in the DirectDraw window.  If it is 1,
// we leave the window.
static int EXIT=0;

// Mouse variables
static int mouse_x=320, mouse_y=240;

// Tells us if the class has been registered to windows
static bool classRegistered = false;

// Access our multiplayer functions plus our game variables
extern Multiplayer mpDlg;
extern gameVariables gV;

// Our all-important car variables
CAR * Cars = new CAR[4];

// windows vars
HWND      main_window_handle = NULL; // globally track main window
HINSTANCE main_instance      = NULL; // globally track hinstance

static char filename[80];			 // a temp variable used for filenames
static LPDIRECTDRAWSURFACE7 letters[27]; // the bitmap images for font
static LPDIRECTDRAWSURFACE7 explode[15]; // explode sequence
static LPDIRECTDRAWSURFACE7 flag;		 // the flag
static LPDIRECTDRAWSURFACE7 fire;		 // the small fire

#define BITMAP_ID            0x4D42 // universal id for a bitmap
#define MAX_COLORS_PALETTE   256

// default screen size
#define SCREEN_WIDTH    640  // size of screen
#define SCREEN_HEIGHT   480
#define SCREEN_BPP      8    // bits per pixel

#define WINDOW_CLASS_NAME "WINCLASS1"

#define VK_A 65
#define VK_D 68
#define VK_S 83
#define VK_W 87


//////////////////////////////////////////////////////////////////////
//							runGame(int)
//////////////////////////////////////////////////////////////////////
// runGame opens up a DirectDraw window and starts the main game
// runMode = 0:  open up the main game play window
// runMode = 1:  open up the choose car screen

int runGame(int runMode)
{
// To begin with, we do not want to exit this window
EXIT = 0;
int returnValue;

WNDCLASSEX winclass; // this will hold the class we create
HWND	   hwnd;	 // generic window handle
MSG		   msg;		 // generic message

// first fill in the window class stucture
winclass.cbSize         = sizeof(WNDCLASSEX);
winclass.style			= CS_DBLCLKS | CS_OWNDC | 
                          CS_HREDRAW | CS_VREDRAW;
winclass.lpfnWndProc	= WindowProc;
winclass.cbClsExtra		= 0;
winclass.cbWndExtra		= 0;
winclass.hInstance		= AfxGetInstanceHandle();
winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
winclass.hCursor		= LoadCursor(NULL, IDC_ARROW); 
winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
winclass.lpszMenuName	= NULL;
winclass.lpszClassName	= WINDOW_CLASS_NAME;
winclass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

// save hinstance in global
main_instance = AfxGetInstanceHandle();

// register the window class
// if it has already been registered, then skip this if statement
// if it registered successfully, then set classRegistered equal to true
if (!classRegistered)
{
	if (!RegisterClassEx(&winclass))
		return 0;
	else
		classRegistered = true;
}



// create the window
if (!(hwnd = CreateWindowEx(NULL,                  // extended style
                            WINDOW_CLASS_NAME,     // class
						    "Bumper Cars", // title
						    WS_POPUP | WS_VISIBLE,
					 	    0,0,	  // initial x,y
						    SCREEN_WIDTH,SCREEN_HEIGHT,  // initial width, height
							NULL,	  // handle to parent 
						    NULL,	  // handle to menu
						    main_instance,// instance of this application
						    NULL)))	// extra creation parms
return(0);



// save main window handle
main_window_handle = hwnd;

// Initialize the game
Game_Init();

// Stop showing the cursor
ShowCursor(FALSE);


// Start playing "rev" sound for choose_car screen
if (runMode == 1)
{
	check_palette(8);
	PlaySound("loop.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}

// enter main event loop
while (TRUE)
	{
    // test if there is a message in queue, if so get it
	if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	{
		if (msg.message == WM_CLOSE)
			break;

		// Translate and dispatch the message
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// break if exit is true
	if (EXIT)
		break;

	switch (runMode)
	{
	   case 0:
		   // Return 1 in this mode (value not important)
	       returnValue = Game_Main();
		   break;
	   case 1:
		   // Return the number of the car that has been chosen
		   returnValue = choose_car();
		   break;
	}
	   
} // end while

// Stop playing the "rev" sound on the choose car screen.
if (runMode == 1)
	PlaySound(NULL, NULL, NULL);

// closedown game here
// show the cursor again
ShowCursor(TRUE);
Game_Shutdown();

// If we have used the choose_car mode, then we want to return
// the car the user has picked.  Otherwise if Game_Main() has been
// used, this will just return 1.
return returnValue;

}
//////////////////////////////////////////////////////////////////////



// This is a function used by Windows to process window messages
// We basically destroy the window and update our mouse position
// when it is called, otherwise we let the Windows default function
// process the message.

LRESULT CALLBACK WindowProc(HWND hwnd, 
						    UINT msg, 
                            WPARAM wparam, 
                            LPARAM lparam)
{
	// this is the main message handler of the system

	// what is the message 
	switch(msg)
		{
			case WM_MOUSEMOVE:
				mouse_x = (int)LOWORD(lparam);
				mouse_y = (int)HIWORD(lparam);
				break;
			case WM_CLOSE:
				DestroyWindow(hwnd);
				break;
			default:
				break;

		} // end switch

	// process any messages that we didn't take care of 
	return (DefWindowProc(hwnd, msg, wparam, lparam));

} // end WinProc





int Game_Main() {

	short i, j;
	int collide_sector, swap;
	int Car0 = gV.localCar[0];	// Do this so we do not use the
	int Car1 = gV.localCar[1];	// index operator a large number of times
	double x, y;
	short compDamage;
	BOOL goForwards = FALSE;
	short type;

	// This is useful later on
	if (!gV.twoPlayers)
		Car1 = -1;

	// If the user presses ESC, then we leave the window
	if (KEY_DOWN(VK_ESCAPE))
	{
		EXIT = 1;
		PostMessage(main_window_handle, WM_CLOSE,0,0);
	}
	
	// Start our clock.  When we reach Wait_Clock( ) in drawMainWindow()
	// then we will have waited the correct amount of time (e.g. 30 frames
	// per second in non-multiplayer mode)
	Start_Clock();

	// Do one player buttons first
	// Depending on the button pressed, we do different things to the car, such as move it
	// right, left, up, down, etc.
	// The next section of code does these things for the 2 cars.

	if (KEY_DOWN(VK_RIGHT))
		Cars[Car0].turn_right();
	else 
		if (KEY_DOWN(VK_LEFT))
			Cars[Car0].turn_left();

	if (KEY_DOWN(VK_UP)) {
		Cars[Car0].accelerate();
		Cars[Car0].move();
	}
	else
	{
		if (KEY_DOWN(VK_DOWN)) {
			Cars[Car0].decelerate();
			Cars[Car0].move();
		}
	}

	if (KEY_UP(VK_UP) && KEY_UP(VK_DOWN) && (Cars[Car0].get_speed() != 0.0)) {

		// if the car was moving forward
		if (Cars[Car0].get_speed() > 0.0)
		{
			Cars[Car0].decelerate();
			if ((Cars[Car0].get_speed() > 0.2) || (Cars[Car0].get_speed() < -0.2))
				Cars[Car0].move();
		} else {
			Cars[Car0].accelerate();
			if ((Cars[Car0].get_speed() > 0.2) || (Cars[Car0].get_speed() < -0.2))
				Cars[Car0].move();
		}
	}
	//End one player buttons

	//Start two player buttons
	if (gV.twoPlayers)
	{
		if (KEY_DOWN(VK_D))
			Cars[Car1].turn_right();
		else 
			if (KEY_DOWN(VK_A))
				Cars[Car1].turn_left();

		if (KEY_DOWN(VK_W)) {
			Cars[Car1].accelerate();
			Cars[Car1].move();
		}
		else
		{
			if (KEY_DOWN(VK_S)) {
				Cars[Car1].decelerate();
				Cars[Car1].move();
			}
		}

		if (KEY_UP(VK_W) && KEY_UP(VK_S) && (Cars[Car1].get_speed() != 0.0)) {

			// if the car was moving forward
			if (Cars[Car1].get_speed() > 0.0)
			{
				Cars[Car1].decelerate();
				if ((Cars[Car1].get_speed() > 0.2) || (Cars[Car1].get_speed() < -0.2))
					Cars[Car1].move();
			} else {
				Cars[Car1].accelerate();
				if ((Cars[Car1].get_speed() > 0.2) || (Cars[Car1].get_speed() < -0.2))
					Cars[Car1].move();
			}
		}
	}
	//Done two player buttons




	// For multiplayer games, we must check for collisions with other
	// cars.  This big looping statment does that.

	// If it is multiplayer mode...
	if (gV.multiplayerEnabled)
	{
		// Check for collisions for each player on our machine...
		for (i = 0; i < gV.localPlayers; i++)
		{
			// ...with collisions for players on other machines.
			for (j = 0; j < gV.totalPlayers; j++)
			{
				// We do not want to check for collisions with ourself
				// or the other local car
				if ((Car0 != j) && (Car1 != j))
				{
					// Retrieve the remote player's position
					Cars[j].get_position(x, y);

					// Check for a collision
					collide_sector = Cars[gV.localCar[i]].compute_collision(x, y, 1);

					// If there is a collision...
					if (collide_sector != 0)
					{
						PlaySound("crash.wav", NULL, SND_FILENAME | SND_ASYNC);

						// We compute the damage that each car will take
						if (abs(Cars[gV.localCar[i]].get_speed()) >= abs(Cars[j].get_speed()))
						{
							compDamage = abs(Cars[gV.localCar[i]].get_speed()) * 2;

							if (abs(Cars[gV.localCar[i]].get_speed()) == abs(Cars[j].get_speed()))
								Cars[gV.localCar[i]].raise_damage( (abs(Cars[j].get_speed()) * 2) );
						}
						else
							compDamage = 0;
	
						// We check if the cars are going in the same direction
						if (checkIfSameDirection(Cars[gV.localCar[i]].get_head_sector(), Cars[j].get_head_sector()))

							goForwards = TRUE;
						else
							goForwards = FALSE;

						// We send a bump message to everybody playing.  The correct car
						// should get this message and update its damage and position.
						mpDlg.m_DirectPlay.Send_Bump_Message_To_All(&j, &compDamage, &goForwards);

						// We move our car backwards
						Cars[gV.localCar[i]].set_speed(-3.0);
						Cars[gV.localCar[i]].move();

					}	//if a collision
				}	//if not your car
			}	//totalPlayers
		}	//localPlayers
	} //multiplayerEnabled

	//begin non-multiplayer code

	x = 0.0, y = 0.0;

	// This computes collisions for each car with the wall
	// Damage is automatically incremented in the compute_collision
	// function.
	for (i = 0; i < gV.localPlayers; i++)
	{
		collide_sector = Cars[gV.localCar[i]].compute_collision(x, y, 0);
		if (collide_sector != 0) 
		{
			PlaySound("bump.wav", NULL, SND_FILENAME | SND_ASYNC);

			// If there has been a collision, move the car backwards
			Cars[gV.localCar[i]].reverse_speed();
			Cars[gV.localCar[i]].move();
		}
	}

	// If there are two players locally, we must check to see if they
	// are colliding with each other
	if (gV.twoPlayers)
	{
		// Get Player 2's position, and check for a collision
		// with Player 1
		Cars[Car1].get_position(x, y);
		collide_sector = Cars[Car0].compute_collision(x, y, 1);

		if (collide_sector != 0) 
		{
			PlaySound("crash.wav", NULL, SND_FILENAME | SND_ASYNC);

			// If there is a collision, raise damage appropriately
			if (abs(Cars[Car0].get_speed()) >= abs(Cars[Car1].get_speed()))
			{
				Cars[Car1].raise_damage( (abs(Cars[Car0].get_speed()) * 2) );
				if (abs(Cars[Car0].get_speed()) == abs(Cars[Car1].get_speed()))
					Cars[Car0].raise_damage( (abs(Cars[Car1].get_speed()) * 2) );
			}
			else
			{
				Cars[Car0].raise_damage( (abs(Cars[Car1].get_speed()) * 2) );
				swap = Car0;
				Car0 = Car1;
				Car1 = swap;
			}

			// If the cars are facing the same direction, move 
			// them appropriately
			if (checkIfSameDirection(Cars[Car0].get_head_sector(), Cars[Car1].get_head_sector()))
				Cars[Car1].set_speed(2.5);
			else
				Cars[Car1].set_speed(-3.0);


			Cars[Car0].set_speed(-3.0);

			Cars[Car1].move();
			Cars[Car0].move();
		}
	}


	// Now check for powerups
	for (i = 0; i < gV.localPlayers; i++)
	{
		// The formula for checking for power-ups works like this:
		// (1) If there is a collision...
		// (2) Play the sound
		// (3) Release the position so the track can use the position
		//	   for another power-up
		// (4) Take appropriate action to the car (raise damage, 
		//		send a random direction, etc.)
		// (5) Stop drawing the object
		// (6) If multiplayer is enabled, send an UnDraw message to
		//		all those playing
		// This repeats for each power-up every time it has been run over.

		collide_sector = Cars[gV.localCar[i]].compute_collision(medikit.x, medikit.y, 2);
		if ((collide_sector != 0) && (gV.drawMedikit == true))
		{
			PlaySound("powerup.wav", NULL, SND_FILENAME | SND_ASYNC);

			gV.mainTrack->releasePosition(medikit.x, medikit.y);
			Cars[gV.localCar[i]].raise_damage(-15);
			gV.drawMedikit = false;
			type = 1;

			if (gV.multiplayerEnabled)
				mpDlg.m_DirectPlay.Send_Undraw_Message_To_All(&type, (short*)&medikit.x, (short*)&medikit.y);
		}

		collide_sector = Cars[gV.localCar[i]].compute_collision(gear.x, gear.y, 2);
		if ((collide_sector != 0) && (gV.drawGear == true))
		{
			PlaySound("powerup.wav", NULL, SND_FILENAME | SND_ASYNC);

			gV.mainTrack->releasePosition(gear.x, gear.y);
			Cars[gV.localCar[i]].increment_max_speed();
			gV.drawGear = false;
			type = 2;

			if (gV.multiplayerEnabled)
				mpDlg.m_DirectPlay.Send_Undraw_Message_To_All(&type, (short*)&gear.x, (short*)&gear.y);
		}

		collide_sector = Cars[gV.localCar[i]].compute_collision(oil.x, oil.y, 2);
		if ((collide_sector != 0) && (gV.drawOil == true))
		{
			PlaySound("powerdown.wav", NULL, SND_FILENAME | SND_ASYNC);

			gV.mainTrack->releasePosition(oil.x, oil.y);
		
			if (Cars[gV.localCar[i]].get_head_sector() < 19)
				Cars[gV.localCar[i]].set_head_sector( rand()%18 + 1);
			else
				Cars[gV.localCar[i]].set_head_sector( rand()%18 + 18);

			gV.drawOil = false;
			type = 3;

			if (gV.multiplayerEnabled)
				mpDlg.m_DirectPlay.Send_Undraw_Message_To_All(&type, (short*)&oil.x, (short*)&oil.y);
		}

		collide_sector = Cars[gV.localCar[i]].compute_collision(dynamite.x, dynamite.y, 2);
		if ((collide_sector != 0) && (gV.drawDynamite == true))
		{
			PlaySound("dynamite.wav", NULL, SND_FILENAME | SND_ASYNC);

			gV.mainTrack->releasePosition(dynamite.x, dynamite.y);
			Cars[gV.localCar[i]].decrement_max_speed();

			gV.drawDynamite = false;
			type = 4;

			if (gV.multiplayerEnabled)
				mpDlg.m_DirectPlay.Send_Undraw_Message_To_All(&type, (short*)&dynamite.x, (short*)&dynamite.y);
		}
	}
	// end checking for power-ups

	//Now check for the flag if it is capture the flag

	if (gV.playMode == 2)
	{
		for (i = 0; i < gV.localPlayers; i++)
		{
			collide_sector = Cars[gV.localCar[i]].compute_collision(302, 238, 2);
			if ((collide_sector != 0) && (gV.canCapture == true))
			{
				PlaySound("powerup.wav", NULL, SND_FILENAME | SND_ASYNC);

				Cars[gV.localCar[i]].acquire_flag();
				gV.whoHasFlag = gV.localCar[i];
				gV.canCapture = false;

				if (gV.multiplayerEnabled)
					mpDlg.m_DirectPlay.Send_Acquire_Message_To_All((short*)&gV.localCar[i]);
			}
		}
	}

	// If we are playing multiplayer, then receive any messages
	// waiting in the queue
	if (gV.multiplayerEnabled)
		mpDlg.Receive();

	// Draw the main window (function below)
	drawMainWindow();

	return (1);
}


//////////////////////////////////////////////////////////////////////
//						drawMainWindow()
//////////////////////////////////////////////////////////////////////
// This draws the cars, track, and other objects on our window.

void drawMainWindow()
{
	short i;
	double x, y;

	// Now start drawing the actual cars
	// clear the drawing surface
	DDraw_Fill_Surface(lpddsback, 0);

	// Lock the back surface so we cannot draw on it
	DDraw_Lock_Back_Surface();

		// Draw the track, and power-ups if required
		Draw_Bitmap(&track, back_buffer, back_lpitch, 0);
		if (gV.drawMedikit) 
			Draw_Bitmap(&medikit, back_buffer, back_lpitch,0);
		if (gV.drawGear) 
			Draw_Bitmap(&gear, back_buffer, back_lpitch,1);
		if (gV.drawOil)
			Draw_Bitmap(&oil, back_buffer, back_lpitch,1);
		if (gV.drawDynamite)
			Draw_Bitmap(&dynamite, back_buffer, back_lpitch,1);

	// Now it is OK to draw on the back surface
	DDraw_Unlock_Back_Surface();

	// Draw player 1's text
	draw_Text(0);

	// Draw player 2's text
	if (gV.twoPlayers)
		draw_Text(1);

	// If we have a winner draw the info on the screen
	if ((gV.winner != -1) && (gV.playMode != 0))
		draw_Text(-1);

	// If multiplayer is enabled, we draw all the cars
	// If their damage is >= 100, we draw the fire image.
	if (gV.multiplayerEnabled)
	{
		for (i = 0; i < gV.totalPlayers; i++)
			if (Cars[i].get_damage() < 100)
				Draw_Car(Cars[i], lpddsback);
			else
			{
				Cars[i].get_position(x, y);
				(int)x; (int)y;
				Draw_Object(fire, lpddsback, x, y, 32, 32);
			}
	}
	else
	{
		// If multiplayer is not enabled, we draw our local cars
		// If their damage is >= 100, we draw the explode sequence
		for (i = 0; i < gV.localPlayers; i++)
			if (Cars[gV.localCar[i]].get_damage() < 100)
				Draw_Car(Cars[gV.localCar[i]], lpddsback);
			else
			{
				Cars[gV.localCar[i]].get_position(x, y);
				(int)x; (int)y;
				Draw_Object(explode[Cars[gV.localCar[i]].get_explode_sequence()], lpddsback, x, y, 64, 64);
			}
	}

	// If it is capture the flag mode, we have to draw the flag
	// If it cannot be captured we draw it at the middle of the board
	if (gV.playMode == 2)
	{
		if (gV.canCapture)
			Draw_Object(flag, lpddsback, 302, 238, 24,24);
		else
		{
			// If it is on a car, find out which car has it, and draw it
			Cars[gV.whoHasFlag].get_position(x, y);
			(int)x; (int)y;
			if (Cars[gV.whoHasFlag].get_damage() < 100)
				Draw_Object(flag, lpddsback, x + 4, y + 4, 24, 24);
			else
				Draw_Object(fire, lpddsback, x, y, 32, 32);
		}
	}


	// Animate the front and back surfaces
	Flip_Pages();

	if (gV.multiplayerEnabled)
		Wait_Clock(26);
	else
		Wait_Clock(30); // wait for 30 fps, so the game does not too 
						// fast (important for fast computers)

}
//////////////////////////////////////////////////////////////////////


// Initialize game here.  
// Init direct draw, read in bitmaps, initialize mouse and fill arrays and linked lists with collision data.
int Game_Init() {

	// initialize game here
	initialize_DirectDraw();

	readMaskData();

	Read_BMPs();

	init_mouse();

	return (1);
}



int Read_BMPs() {
	// This function reads in all the bitmaps from the maps directory.  This includes every bitmap 
	// used in the game except those in dialog boxes.

	// NOTE:  If one or more bitmaps are missing and the game cannot locate them, then the game will
	// not start and will exit abruptly.  It is a windows error that occurs
	// because the file is unable to be found.

	// Read in respective track bitmap from information received in Choose Track dialog box.
	switch (gV.trackChosen)
	{
		case 1:
			sprintf(filename, "maps\\track256.bmp");
			break;
		case 2:
			sprintf(filename, "maps\\junkyard.bmp");
			break;
		case 3:
			sprintf(filename, "maps\\trmetal.bmp");
			break;
		case 4:
			sprintf(filename, "maps\\thnksgiv.bmp");
			break;
		case 5:
			sprintf(filename, "maps\\beach.bmp");
			break;

		default:
			break;
	}

	// Load all single frame pictures
	Load_Bitmap_File(&bmpFile, filename);
	Create_Bitmap(&track, 0,0, 640, 480);
	Load_Image_Bitmap(&track,&bmpFile,0,0);
	Unload_Bitmap_File(&bmpFile);

	// Set palette to Chosen Track's palette
	check_palette(gV.trackChosen);

	sprintf(filename, "maps\\dark_cars.bmp");
    Load_Bitmap_File(&bmpFile, filename);
    Create_Bitmap(&dark_cars, 0,0, 640, 480);
    Load_Image_Bitmap(&dark_cars,&bmpFile,0,0);
    Unload_Bitmap_File(&bmpFile);

	sprintf(filename, "maps\\goggles_norm.bmp");
	Load_Bitmap_File(&bmpFile, filename);
	Create_Bitmap(&goggles_norm,0,0,170,100);
	Load_Image_Bitmap(&goggles_norm, &bmpFile, 0,0);
	Unload_Bitmap_File(&bmpFile);

	sprintf(filename, "maps\\goggles_red.bmp");
	Load_Bitmap_File(&bmpFile, filename);
	Create_Bitmap(&goggles_red,0,0,170,100);
	Load_Image_Bitmap(&goggles_red, &bmpFile, 0,0);
	Unload_Bitmap_File(&bmpFile);

	sprintf(filename, "maps\\light_cars.bmp");
	Load_Bitmap_File(&bmpFile, filename);
	Create_Bitmap(&light_cars,0,0,640,480);
	Load_Image_Bitmap(&light_cars, &bmpFile, 0,0);
	Unload_Bitmap_File(&bmpFile);

	sprintf(filename, "maps\\medikit.bmp");
	Load_Bitmap_File(&bmpFile, filename);
	Create_Bitmap(&medikit,0,0,16,16);
	Load_Image_Bitmap(&medikit, &bmpFile, 0,0);
	Unload_Bitmap_File(&bmpFile);

	sprintf(filename, "maps\\gear.bmp");
	Load_Bitmap_File(&bmpFile, filename);
	Create_Bitmap(&gear,0,0,16,16);
	Load_Image_Bitmap(&gear, &bmpFile, 0,0);
	Unload_Bitmap_File(&bmpFile);

	sprintf(filename, "maps\\oil.bmp");
	Load_Bitmap_File(&bmpFile, filename);
	Create_Bitmap(&oil,0,0,16,16);
	Load_Image_Bitmap(&oil, &bmpFile, 0,0);
	Unload_Bitmap_File(&bmpFile);

	sprintf(filename, "maps\\fire.bmp");
	Load_Bitmap_File(&bmpFile, filename);
	Create_Object(&fire, 1, 32, 32);
	Load_Frame_Object(fire, &bmpFile, 0, 0, 0, 32,32);
	Unload_Bitmap_File(&bmpFile);

	sprintf(filename, "maps\\dynamite.bmp");
	Load_Bitmap_File(&bmpFile, filename);
	Create_Bitmap(&dynamite,0,0,16,16);
	Load_Image_Bitmap(&dynamite, &bmpFile, 0,0);
	Unload_Bitmap_File(&bmpFile);

	// Load multiple frame animations

	// Since font.bmp is more than one picture in one single bitimap, we must read in each part and save
	// it as a seperate surface.
	sprintf(filename, "maps\\font.bmp");
	Load_Bitmap_File(&bmpFile, filename);
	int tmp=0;
	Create_Object(letters, 26, 16, 16);
	for (int io = 0; io<26; io++)
	{
		Load_Frame_Object(letters[io],&bmpFile,io,tmp,0, 16,16);
		tmp+=16;
	}
	Unload_Bitmap_File(&bmpFile);

	sprintf(filename, "maps\\flag.bmp");
	Load_Bitmap_File(&bmpFile, filename);
	Create_Object(&flag, 1, 24, 24);
	Load_Frame_Object(flag,&bmpFile,0,0,0, 24,24);
	Unload_Bitmap_File(&bmpFile);

	// Since CARLINE.BMP is more than one picture in one single bitimap, we must read in each part and save
	// it as a seperate surface.
    int frame = 0;
	int i;
    int step=0,y_line=0;
	sprintf(filename, "maps\\CARLINE.BMP");
	Load_Bitmap_File(&bmpFile,filename);

	// Loop 4 times because there are 4 rows of each car.
	for(i=0; i<4; i++) 
	{
		frame=0;
		Create_Car(Cars[i],0,0,36, 16 | 2 ,DDSCAPS_SYSTEMMEMORY);
		// load in new bitmap file
		for (y_line = step; y_line < (128 + step); y_line+=32) 
		{
			// Load in each frame
			Load_Frame(Cars[i],&bmpFile, frame, 0, y_line);
			Load_Frame(Cars[i],&bmpFile,1+frame,32, y_line);  
			Load_Frame(Cars[i],&bmpFile,2+frame,64, y_line); 
			Load_Frame(Cars[i],&bmpFile,3+frame,96, y_line); 
			Load_Frame(Cars[i],&bmpFile,4+frame,128,y_line); 
			Load_Frame(Cars[i],&bmpFile,5+frame,160,y_line); 
			Load_Frame(Cars[i],&bmpFile,6+frame,192,y_line); 
			Load_Frame(Cars[i],&bmpFile,7+frame,224,y_line); 
			Load_Frame(Cars[i],&bmpFile,8+frame,256,y_line); 
			frame+=9;
		}
		step+=(4*32);
	}	

    Unload_Bitmap_File(&bmpFile);

	// now to read in exploding bitmap sequence
	sprintf(filename, "maps\\explode.bmp");
	Load_Bitmap_File(&bmpFile, filename);
	Create_Object(explode, 15, 64, 64);
	// Since explode.bmp is more than one picture in one single bitimap, we must read in each part and save
	// it as a seperate surface.
	tmp=0;
	int j;
	int yo=0;
	int frame_count=0;

	for(i = 0; i < 3; i++)
	{
		for (j = 0; j < 5; j++)
		{		
			Load_Frame_Object(explode[frame_count],&bmpFile,frame_count,tmp,yo, 64, 64);
			tmp+=64;
			frame_count++;			
		}
		yo+=64;
		tmp=0;
	}

	Unload_Bitmap_File(&bmpFile);

	return (1);
}



// Release acquired memory back to environment.
int Game_Shutdown() {
	release_DirectDraw();
	Destroy_Bitmap(&light_cars);
	Destroy_Bitmap(&dark_cars);
	Destroy_Bitmap(&track);
	Destroy_Bitmap(&goggles_norm);
	Destroy_Bitmap(&gear);
	Destroy_Bitmap(&medikit);
	Destroy_Bitmap(&oil);
	Destroy_Bitmap(&dynamite);

	return (1);
}

// this function is used to choose the color of your car.  It is only effective in 1 or two player
// modes.  
int choose_car() {

	// Press escape to choose your car and go back to main window screen
	if (KEY_DOWN(VK_ESCAPE))
	{
		EXIT = 1;
		PostMessage(main_window_handle, WM_CLOSE,0,0);
	}

	int option = 0;
	int i, j;

	// Call option function to see if mouse cursor is over a valid car choice.
	option = check_mouse_pos(mouse_x, mouse_y);

	Start_Clock();
	// clear the drawing surface
	
	// right 
	if (mouse_x+(172/2) >= 640)
		mouse_x = 640-(172/2);

	// left
	if (mouse_x<=(172/2))
		mouse_x =(172/2);

	// top
	if (mouse_y<=50)
		mouse_y =50;

	// bottom
	if (mouse_y+50 >= 480)
		mouse_y = 430;

	// Clear surface memory
	DDraw_Fill_Surface(lpddsback, 0);
	
	// Lock back buffer for manipulation
	DDraw_Lock_Back_Surface();

		// Draw onto back buffer
		Draw_Bitmap(&dark_cars, back_buffer, back_lpitch, 0);

		if (!option)
			render_light(&light_cars, &goggles_norm, back_buffer, back_lpitch, (mouse_x-(goggles_norm.width/2)), (mouse_y-(goggles_norm.height/2)));
		else
			render_light(&light_cars, &goggles_red, back_buffer, back_lpitch, (mouse_x-(goggles_red.width/2)), (mouse_y-(goggles_red.height/2)));

	// Unlock back surface
	DDraw_Unlock_Back_Surface();

	CString message = "PRESS ESC TO EXIT";

	j = 0;
	for (i = 0; i < message.GetLength(); i++)
	{
		int temp;
		temp = find_Letter(message[i]);
		Draw_Object(letters[temp],lpddsback,j,10, 16, 16);
		j+=13;
	}

	// Flip pages because there is DD animation
	Flip_Pages();
	// Keep animation at 30 fps
	Wait_Clock(30); 

	return (option);
}



//////////////////////////////////////////////////////////////////////
//						check_palette(int)
//////////////////////////////////////////////////////////////////////
// This function makes sure the palette is changed to the track
// we are using.

int check_palette(int in_menu) {

	// Pick a file depending on what is passed in.
	switch (in_menu)
	{
		case 1:
			sprintf(filename, "maps\\track256.bmp");
			break;
		case 2:
			sprintf(filename, "maps\\junkyard.bmp");
			break;
		case 3:
			sprintf(filename, "maps\\trmetal.bmp");
			break;
		case 4:
			sprintf(filename, "maps\\thnksgiv.bmp");
			break;
		case 5:
			sprintf(filename, "maps\\beach.bmp");
			break;
		case 8:
			sprintf(filename, "maps\\light_cars.bmp");
			break;
		default:
			break;		
	}

	// Load in the file and set the palette
	Load_Bitmap_File(&bmpFile, filename);
	setPalette(bmpFile.palette );
	Unload_Bitmap_File(&bmpFile);

	return (1);
}
//////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////
//						draw_Text(int)
//////////////////////////////////////////////////////////////////////
// This function draws text on the screen using standard Windows GDI
// text routines.

void draw_Text(int whichCar)
{
	HDC hdc;
	char cstr[5];
	CString message;
	int chars, yVal, xVal;

	// Make sure we are the only ones drawing on the surface
	lpddsback->GetDC(&hdc);

	// If whichCar is -1, then we draw the winner message
	// If it is 0 we draw Player 1's data, and 
	// if it is 1 we draw Player 2's data
	switch (whichCar)
	{
		case -1:
			SetTextColor(hdc, RGB(0, 0, 0));
			message = gV.playerNames[gV.winner] + " has won the game!!!";
			TextOut(hdc, 450, 440, message, message.GetLength());

			// Return control and exit the function
			lpddsback->ReleaseDC(hdc);
			return;
			break;
		case 0:
			yVal = 390;
			xVal = 10;
			break;
		case 1:
			yVal = 390;
			xVal = 95;
			break;

		default:
			break;
	}

	// We set the text color depending on which car we are drawing
	// data for.
	switch (gV.localCar[whichCar])
	{
		case 0:
			SetTextColor(hdc, RGB(0, 0, 255));
			break;
		case 1:
			SetTextColor(hdc, RGB(255, 0, 0));
			break;
		case 2:
			SetTextColor(hdc, RGB(0, 255, 0));
			break;
		case 3:
			SetTextColor(hdc, RGB(200, 200, 0));
			break;
		default:
			break;
	}

	// Output some headings and the player's name
	TextOut(hdc, xVal, yVal, gV.playerNames[whichCar], gV.playerNames[whichCar].GetLength());
	TextOut(hdc, xVal, (yVal + 20), "Speed: ", 7);
	TextOut(hdc, xVal, (yVal + 40), "Damage: ", 8);

	// Convert the int speed to a string, and then display it on screen
	itoa(int(Cars[gV.localCar[whichCar]].get_speed()), cstr, 10);
	chars = strlen(cstr);
	TextOut(hdc, (xVal + 50), (yVal + 20), cstr, chars);

	// Convert damage to a string and display that
	itoa(Cars[gV.localCar[whichCar]].get_damage(), cstr, 10);
	chars = strlen(cstr);
	TextOut(hdc, (xVal + 63), (yVal + 40), cstr, chars);

	// Depending on the game mode we either display laps completed,
	// or time with the flag
	if (gV.playMode == 1)
	{
		TextOut(hdc, xVal, (yVal + 60), "Laps: ", 6);
		itoa(Cars[gV.localCar[whichCar]].getLapsCompleted(), cstr, 10);
		chars = 1;
		TextOut(hdc, (xVal + 41), (yVal + 60), cstr, chars);
	}
	else if (gV.playMode == 2)
	{	
		TextOut(hdc, xVal, (yVal + 60), "Time: ", 6);
		itoa(Cars[gV.localCar[whichCar]].get_flag_time(), cstr, 10);
		chars = strlen(cstr);
		TextOut(hdc, (xVal + 41), (yVal + 60), cstr, chars);
	}

	// Return control so that other parts of the program can
	// write on the back surface
	lpddsback->ReleaseDC(hdc);

}
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//					checkIfSameDirection(int, int)
//////////////////////////////////////////////////////////////////////
// This function checks to see if the two cars are facing the same
// direction.  If they are, the function returns true (1).
// Otherwise it is false (0).

int checkIfSameDirection(int direction1, int direction2)
{
	if ((direction1 <= 18) && (direction2 <= 18))
		return 1;
	else if ((direction1 > 18) && (direction2 > 18))
			return 1;

	return 0;
}
//////////////////////////////////////////////////////////////////////