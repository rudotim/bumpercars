//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
//
// functions.h
//
// This defines many functions for drawing objects on the screen in
// DirectDraw.
//
//////////////////////////////////////////////////////////////////////

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "car.h"
#include <ddraw.h>
#include <dinput.h>

// A macro to initialize a DirectDraw struct
#define DDRAW_INIT_STRUCT(ddstruct) { memset(&ddstruct,0,sizeof(ddstruct)); ddstruct.dwSize=sizeof(ddstruct); }


unsigned char *DDraw_Lock_Back_Surface();
// DirectDraw has two surfaces, a back and and a front surface
// When the back surface is locked, only drawing on the front surface
// is possible.  This functions locks the surface so no drawing can
// take place.

int DDraw_Unlock_Back_Surface();
// This does the opposite of the above function:
// It unlocks the surface.  Now drawing on the back surface is possible.


// two macros to determine if a keyboard key is up or down
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

// structure for bitmaps 
typedef struct BITMAP_FILE_TAG
{
	BITMAPFILEHEADER bitmapfileheader;  // this contains the bitmapfile header
    BITMAPINFOHEADER bitmapinfoheader;  // this is all the info including the palette
    PALETTEENTRY     palette[256];      // store the palette here
    unsigned char    *buffer;           // pointer to the data

} BITMAP_FILE, *BITMAP_FILE_PTR;


// bitmap image
typedef struct BITMAP_IMAGE_TYP
{
	int state;				// state of bitmap
    int attr;				// attributes of bitmap
    int x,y;				// position of bitmap
    int width, height;		// size of bitmap
    int num_bytes;			// total bytes of bitmap
    unsigned char *buffer;      // pixels of bitmap

} BITMAP_IMAGE, *BITMAP_IMAGE_PTR;


int init_mouse();
// Init mouse initializes the mouse position.  It is used for our 
// goggles in the Choose Your Car screen.


int initialize_DirectDraw();
// This initializes DirectDraw so that all of its methods can be used.
// It also allocates resources that DirectDraw uses.


int release_DirectDraw();
// This deallocates DirectDraw and frees any resources associated
// with it.


int setPalette(LPPALETTEENTRY palette);
// When we want to set DirectDraw's palette to a certain 256 color
// scheme, we use this function.


void Flip_Pages();
// Flips the front and back surfaces to animate the cars and other
// objects.


int check_mouse_pos(int mx, int my);
// Get the current position of the mouse.  It returns a number
// corresponding to the car that the goggles are over.
// (Used for Choose Your Car)


int find_Letter(char letter);
// Return a number for a letter, e.g. 'A' is 0, 'B' is 1, etc.



int Create_Object(LPDIRECTDRAWSURFACE7 * images, int num_frames, int sizeX, int sizeY);
// Create_Object readies surface images for image creation.
// To create the object, its width(X) and height(Y) must be specified,
// along with the amount of frames it is going to take up.
// (For example, the explosion is shown over many frames)


int Load_Frame_Object(LPDIRECTDRAWSURFACE7 & image, BITMAP_FILE_PTR bitmap, int frame,int cx,int cy, int sizeX, int sizeY);
// This loads a surface image with a Bitmap file, bitmap.
// Again, the frame being loaded, and size must be specified.
// cx and cy are the location in the bitmap file where this frame
// can be found.


int Draw_Object(LPDIRECTDRAWSURFACE7 & image, LPDIRECTDRAWSURFACE7 dest,int x, int y, int sizeX, int sizeY); 
// This draws a surface image to a surface (such as front or back) dest.
// Where it should be drawn (x and y), and its size (sizeX and sizeY)
// should be specified.



int Load_Frame(CAR & Car, BITMAP_FILE_PTR bitmap, int frame, int cx, int cy);
// This function loads a section of the carline bitmap that should
// be in one single frame of a car animation.
// A CAR, and bitmap to load for that frame should be passed first, 
// followed by the frame number.
// cx and cy are the location in the bitmap file where this frame
// can be found.


int Create_Car(CAR &Car, int x, int y, int num_frames, int attr, int mem_flags);
// Create_Car readies surface images for image creation.
// x and y should be set to 0.  The num_frames should be the number
// of frames in a car, in our case it is 36.
// For our car attr is 16 | 2, and the mem_flags is
// DDSCAPS_SYSTEMMEMORY, a DirectDraw flag.


int Draw_Car(CAR & Car, IDirectDrawSurface7 *dest);
// This draws a CAR to a surface (such as front or back) dest.
// The CAR being drawn and the surface to draw it on should be passed
// in.


int packMask(BITMAP_FILE_PTR bitmap, int lpitch);
// This is not used explicitly in the game.  It is just a tool we developed
// to aid us in making boards.

int Flip_Bitmap(unsigned char *image, int bytes_per_line, int height);
//  Since bitmaps are loaded in upside down, we need a function to 
//  turn them right side up.
//  image is a pointer to the start of the bitmap image information, bytes_per_line
//  is the width of the bitmap, and height is the height of the bitmap.

int Load_Bitmap_File(BITMAP_FILE_PTR bitmap, char *filename);
// This loads in a bitmap file.
// bitmap is a pointer to a bitmap file, and filename is the name of the file
// we are loading.

int Unload_Bitmap_File(BITMAP_FILE_PTR bitmap);
// Frees memory associated with a bitmap.

int Draw_Bitmap(BITMAP_IMAGE_PTR source_bitmap,unsigned char *dest_buffer, int lpitch, int transparent);
// This draws a bitmap image source_bitmap to a surface dest_buffer.
// lpitch is dependant on the bitmap, and transparent determines if we show the background of
// the object.

int Load_Image_Bitmap(BITMAP_IMAGE_PTR image,BITMAP_FILE_PTR bitmap,int cx,int cy);
// This loads a bitmap file with a bitmap image.  cx and cy are where the bitmap
// can be found in the file.

int DDraw_Fill_Surface(IDirectDrawSurface7 *lpdds,int color);
// Fills a surface with a color.

IDirectDrawSurface7 *DDraw_Create_Surface(int width, int height, int mem_flags);
// Creates a surface with dimensions width and height and sets memory flags that
// DirectDraw uses.

int Create_Bitmap(BITMAP_IMAGE_PTR image, int x, int y, int width, int height);
// Creates a bitmap from image.  width and height form the size of the bitmap, 
// and x and y are the positions where the bitmap should be drawn.

void render_light(BITMAP_IMAGE_PTR bitmap1,BITMAP_IMAGE_PTR bitmap2,unsigned char *dest_buffer,int lpitch,int x, int y);
// This is the function which illuminates the cars on the Choose Car screen.
// bitmap1 and bitmap2 are the two bitmaps being used.

int Destroy_Bitmap(BITMAP_IMAGE_PTR image);
// This function releases the memory associated with a bitmap.

int readMaskData();
// This reads in the mask data for a board and also the mask
// data for the cars.


DWORD Start_Clock();
DWORD Wait_Clock(DWORD count);
DWORD Get_Clock();
// These functions are used to start clocks, and get clock values.
// Wait_Clock waits a certain amount of time count before continuing,
// which we use to slow the game down to 30 frames per second.



// Variables that other .cpps use
extern unsigned char			*back_buffer;
extern int						back_lpitch;
extern DWORD                    start_clock_count;    // used for timing

extern IDirectDraw7				*lpdd4;
extern IDirectDrawSurface7 		*lpddsprimary;
extern IDirectDrawSurface7 		*lpddsback;
extern DDSURFACEDESC2			ddsd;
extern LPDIRECTDRAWPALETTE		lpddpal;
extern PALETTEENTRY				palette[256];
extern LPDIRECTINPUT			lpdi;
extern LPDIRECTINPUTDEVICE      lpdimouse;

extern short maskData[480][640];
extern int carMaskData[32][32];
extern int tempMaskData[32][32];

#endif