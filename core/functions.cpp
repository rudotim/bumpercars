//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
//
// Functions.cpp defines functions used in functions.h
//
//////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN

#include "stdafx.h" 

#include <fstream.h>
#include <io.h>
#include <ddraw.h>
#include <dinput.h>

#include "bumpercars.h"
#include "car.h"
#include "functions.h"

///////////////////////////////////////////////////////////////////////////////
extern HINSTANCE main_instance; // save the instance
extern HWND main_window_handle;
extern gameVariables gV;
///////////////////////////////////////////////////////////////////////////////

// Pointer to DirectDraw interface.
IDirectDraw7			*lpdd4 = NULL;
// Pointer to Primary Surface
IDirectDrawSurface7		*lpddsprimary = NULL;
// Pointer to Secondary Surface or back buffer.
IDirectDrawSurface7		*lpddsback = NULL;

DDSURFACEDESC2			ddsd;
// Palette object for Primary and Secondary surfaces
LPDIRECTDRAWPALETTE		lpddpal = NULL;
// Array of 256 RGB entries 
PALETTEENTRY			palette[256];
// DirectInput object for manipulating mouse.
LPDIRECTINPUTDEVICE		lpdimouse = NULL;
// DirectInput interface.
LPDIRECTINPUT			lpdi;

unsigned char			*back_buffer;
int						back_lpitch;
DWORD                   start_clock_count;    

// These arrays hold the collision masking data for the maps and cars
// used during the game.
short maskData[480][640];
int carMaskData[32][32];
int tempMaskData[32][32];

// Maximum amount of pictures for rotating car.
// There are 360 degrees in a full circle so there are 36 frames used
// to make one car rotate completely.  Each frame is the car rotated 9 degrees.
const int MAX_CAR_FRAMES = 36;

///////////////////////////////////////////////////////////////////////////////
//  This function acquires and initializes the DirectDraw 7 interface.
///////////////////////////////////////////////////////////////////////////////
int initialize_DirectDraw() {

	// temporary DirectDraw object only used before query
	LPDIRECTDRAW lpdd = NULL;

	// Attempt to aquire basic DirectDraw Interface
	if (FAILED(DirectDrawCreate(NULL,&lpdd,NULL)))
	{
		// error
		return (0);
	}
	
	// Once basic interface is aquired... we now attempt to
	// retrieve the DirectDraw 7 interface
	if (FAILED(lpdd->QueryInterface (IID_IDirectDraw7,(LPVOID *)&lpdd4)))
	{
		// error
		return (2);
	}

	// Set attributes for DirectDraw 7
	// We want DirectDraw to be able to run FullScreen, allow ModeX screen sizes,
	// ....
    if (FAILED(lpdd4->SetCooperativeLevel (main_window_handle,
														DDSCL_FULLSCREEN |
														DDSCL_ALLOWMODEX |
														DDSCL_EXCLUSIVE |
														DDSCL_ALLOWREBOOT)))
	{
		// error
		return (3);
	}


	// Set display to standard 8 bit (640 x 480) screen mode
	if (FAILED(lpdd4->SetDisplayMode(640,480,8,0,0)))
	{
		// error
		return (4);
	}


	// Release standard interface that we previously aquired for 
	// the basic DirectDraw.
	lpdd->Release ();
	lpdd = NULL;

	// Prepare to create and attach primary drawing surface.
    memset(&ddsd,0,sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;

	// Set DirectDraw surface capabilities.
	// We will be using a complex surface - 
	// This means that our surface is a page flippable surface - 
	// It will be the primary surface
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;

	// This tells DirectDraw that we will need a secondary surface for use for page
	// flipping.  Since we are only double buffering, we only need one two surfaces.
	// Primary and Seoncdary
    ddsd.dwBackBufferCount = 1;

	// This creates the Primary Surface
	if (FAILED(lpdd4->CreateSurface (&ddsd, &lpddsprimary, NULL)))
	{
		// error
		return (5);
	}


	// 
	ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;

	// This attaches the Secondary Surface to the Primary Surface so that 
	// page flipping is possible.
	if (FAILED(lpddsprimary->GetAttachedSurface(&ddsd.ddsCaps, &lpddsback))) {
		// error
		return (6);
	}

	// Clear memory for all entries of palette.
	memset(palette,0,256*sizeof(PALETTEENTRY));

	// fill palette with random colors just so that there are
	// some values in there.
	for (int color = 1; color < 255; color++) {
		palette[color].peRed = rand()%256;
		palette[color].peBlue = rand()%256;
		palette[color].peGreen = rand()%256;
		palette[color].peFlags = PC_NOCOLLAPSE;
	}

	// Set first and last entries specifically.
	// First entry is always (0,0,0) or black
	palette[0].peRed = 0;
	palette[0].peBlue = 0;
	palette[0].peGreen = 0;

	// Last entry is (255,255,255) or white
	palette[255].peRed = 255;
	palette[255].peBlue = 255;
	palette[255].peGreen = 255;

	// Set specifications of palette.
	// Palette for DirectDraw surfaces will be 8 bit, 256 color.
	lpdd4->CreatePalette(DDPCAPS_8BIT | DDPCAPS_ALLOW256 |
						 DDPCAPS_INITIALIZE,
						 palette, &lpddpal, NULL);
	
	lpddsprimary->SetPalette(lpddpal);

	return (1);
}

//////////////////////////////////////////////////////////////////////////////
// We call this at the end of our program.
// It releases the DirectDraw components and frees memory they occupied.
//////////////////////////////////////////////////////////////////////////////
int release_DirectDraw() {
	// restore old display mode
	if (FAILED(lpdd4->RestoreDisplayMode()))
	{
		// error
		return (0);
	}

	// Return CooperativeLevel back to normal window mode.
	if (FAILED(lpdd4->SetCooperativeLevel(main_window_handle, DDSCL_NORMAL)))
	{
		return 0;
	}

	// Release palette object.
	if (lpddpal) {
		lpddpal->Release ();
		lpddpal = NULL;
	}

	// Release primary surface pointer.
	if (lpddsprimary) {
		lpddsprimary->Release();
		lpddsprimary = NULL;
	}

	// Release DirectDraw 7 interface
	if (lpdd4) {
		lpdd4->Release();
		lpdd4 = NULL;
	}

	// Unacquire Mouse object
	if (lpdimouse)
		lpdimouse->Unacquire();

	// Release Mouse Object
	if (lpdimouse)
	{
		lpdimouse->Release ();
	}

	return (1);

}

///////////////////////////////////////////////////////////////////////////////
// This function replaces current screen palette with one specified in the paramater.
///////////////////////////////////////////////////////////////////////////////
int setPalette(LPPALETTEENTRY set_palette) {
	
// first save the new palette in shadow
memcpy(palette, set_palette,256*sizeof(PALETTEENTRY));

// now set the new palette
lpddpal->SetEntries(0,0,256,palette);

	return (1);
}


//////////////////////////////////////////////////////////////////////////
// This function lock's the Secondary surface for DirectDraw so that it can
// be manipulated.
//////////////////////////////////////////////////////////////////////////
unsigned char *DDraw_Lock_Back_Surface(void) {


    DDRAW_INIT_STRUCT(ddsd);
	lpddsback->Lock(NULL, &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);

	back_buffer = (unsigned char *)ddsd.lpSurface;
	back_lpitch = ddsd.lPitch;

	return (back_buffer);
}



//////////////////////////////////////////////////////////////////////////
// This unlock's the Secondary Surface so that nothing can be written
// to it.
//////////////////////////////////////////////////////////////////////////
int DDraw_Unlock_Back_Surface(void) {
	lpddsback->Unlock(NULL);

	back_buffer = NULL;
	back_lpitch = 0;
	return (1);
}

//////////////////////////////////////////////////////////////////////////
// Simple function to flip Primary and Secondary surfaces.
// This is where the animation is created.  The images are generated and moved
// around on the secondary surface and then flipped in one instant onto the
// Primary Surface.
//////////////////////////////////////////////////////////////////////////
void Flip_Pages() {
	lpddsprimary->Flip(NULL, DDFLIP_WAIT);
}

///////////////////////////////////////////////////////////////////////////////
// This is a modified function to load a bitmap image from a file onto a 
// DirectDraw surface.
///////////////////////////////////////////////////////////////////////////////
int Load_Image_Bitmap(BITMAP_IMAGE_PTR image, // bitmap image to load with data
                      BITMAP_FILE_PTR bitmap,    // bitmap to scan image data from
                      int cx,int cy)   // cell or absolute pos. to scan image from
                              // if 0 then cx,cy is cell position, else 
                                    // cx,cy are absolute coords
{
// this function extracts a bitmap out of a bitmap file

unsigned char *source_ptr,   // working pointers
              *dest_ptr;

// extract bitmap data
source_ptr = bitmap->buffer +
      cy*bitmap->bitmapinfoheader.biWidth+cx;

// assign a pointer to the bimap image
dest_ptr = (unsigned char *)image->buffer;

// iterate thru each scanline and copy bitmap
for (int index_y=0; index_y<image->height; index_y++)
    {
    // copy next line of data to destination
    memcpy(dest_ptr, source_ptr,image->width);

    // advance pointers
    dest_ptr   += image->width;
    source_ptr += bitmap->bitmapinfoheader.biWidth;
    } // end for index_y

// return success
return(1);

} // end Load_Image_Bitmap

//////////////////////////////////////////////////////////////////////////
//  This is another modified function that load's a bitmap file from a 
//  specified path.
//////////////////////////////////////////////////////////////////////////
int Load_Bitmap_File(BITMAP_FILE_PTR bitmap, char *filename)
{
// this function opens a bitmap file and loads the data into bitmap

int file_handle,  // the file handle
    index;        // looping index

unsigned char   *temp_buffer = NULL; // used to convert 24 bit images to 16 bit
OFSTRUCT file_data;          // the file data information

// open the file if it exists
if ((file_handle = OpenFile(filename,&file_data,OF_READ))==-1)
   return(0);

// now load the bitmap file header
_lread(file_handle, &bitmap->bitmapfileheader,sizeof(BITMAPFILEHEADER));


// now we know this is a bitmap, so read in all the sections

// first the bitmap infoheader

// now load the bitmap file header
_lread(file_handle, &bitmap->bitmapinfoheader,sizeof(BITMAPINFOHEADER));

// now load the color palette if there is one
if (bitmap->bitmapinfoheader.biBitCount == 8)
   {
   _lread(file_handle, &bitmap->palette,256*sizeof(PALETTEENTRY));

   // now set all the flags in the palette correctly and fix the reversed 
   // BGR RGBQUAD data format
   for (index=0; index < 256; index++)
       {
       // reverse the red and green fields
       int temp_color                = bitmap->palette[index].peRed;
       bitmap->palette[index].peRed  = bitmap->palette[index].peBlue;
       bitmap->palette[index].peBlue = temp_color;
       
       // always set the flags word to this
       bitmap->palette[index].peFlags = PC_NOCOLLAPSE;
       } // end for index

    } // end if

// finally the image data itself
_lseek(file_handle,-(int)(bitmap->bitmapinfoheader.biSizeImage),SEEK_END);

// now read in the image

if (bitmap->bitmapinfoheader.biBitCount==8 || bitmap->bitmapinfoheader.biBitCount==16 || 
    bitmap->bitmapinfoheader.biBitCount==24)
   {
   // delete the last image if there was one
   if (bitmap->buffer)
       free(bitmap->buffer);

   // allocate the memory for the image
   if (!(bitmap->buffer = (unsigned char *)malloc(bitmap->bitmapinfoheader.biSizeImage)))
      {
      // close the file
      _lclose(file_handle);

      // return error
      return(0);
      } // end if

   // now read it in
   _lread(file_handle,bitmap->buffer,bitmap->bitmapinfoheader.biSizeImage);

   } // end if
else
   {
   // serious problem
   return(0);

   } // end else

// close the file
_lclose(file_handle);

// flip the bitmap
Flip_Bitmap(bitmap->buffer, 
            bitmap->bitmapinfoheader.biWidth*(bitmap->bitmapinfoheader.biBitCount/8), 
            bitmap->bitmapinfoheader.biHeight);

// return success
return(1);

} // end Load_Bitmap_File

///////////////////////////////////////////////////////////
// This releases the memory used to read in the bitmap
///////////////////////////////////////////////////////////
int Unload_Bitmap_File(BITMAP_FILE_PTR bitmap)
{
// this function releases all memory associated with "bitmap"
if (bitmap->buffer)
   {
   // release memory
   free(bitmap->buffer);

   // reset pointer
   bitmap->buffer = NULL;

   } // end if

// return success
return(1);

} // end Unload_Bitmap_File

//////////////////////////////////////////////////////////////////////////
//  Since bitmaps are loaded in upside down, we need a function to 
//  turn them right side up.
//  This function does just that.
//////////////////////////////////////////////////////////////////////////
int Flip_Bitmap(unsigned char *image, int bytes_per_line, int height)
{
// this function is used to flip bottom-up .BMP images

unsigned char *buffer; // used to perform the image processing
int index;     // looping index

// allocate the temporary buffer
if (!(buffer = (unsigned char *)malloc(bytes_per_line*height)))
   return(0);

// copy image to work area
memcpy(buffer,image,bytes_per_line*height);

// flip vertically
for (index=0; index < height; index++)
    memcpy(&image[((height-1) - index)*bytes_per_line],
           &buffer[index*bytes_per_line], bytes_per_line);

// release the memory
free(buffer);

// return success
return(1);

} // end Flip_Bitmap
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// This function draws a bitmap image onto one of the surfaces.  
// The surface to be drawn on is typically the Secondary Surface
//////////////////////////////////////////////////////////////////////////
int Draw_Bitmap(BITMAP_IMAGE_PTR source_bitmap,unsigned char *dest_buffer, int lpitch, int transparent)
{
// this function draws the bitmap onto the destination memory surface
// if transparent is 1 then color 0 will be transparent
// note this function does NOT clip, so be carefull!!!

unsigned char *dest_addr,   // starting address of bitmap in destination
      *source_addr; // starting adddress of bitmap data in source

unsigned char pixel;        // used to hold pixel value

int index,          // looping vars
    pixel_x;

// test if this bitmap is loaded

//if (source_bitmap->attr & BITMAP_ATTR_LOADED)
//   {
   // compute starting destination address
   dest_addr = dest_buffer + source_bitmap->y*lpitch + source_bitmap->x;

   // compute the starting source address
   source_addr = source_bitmap->buffer;

   // is this bitmap transparent
   if (transparent)
   {
   // copy each line of bitmap into destination with transparency
   for (index=0; index<source_bitmap->height; index++)
       {
       // copy the memory
       for (pixel_x=0; pixel_x<source_bitmap->width; pixel_x++)
           {
           if ((pixel = source_addr[pixel_x])!=0)
               dest_addr[pixel_x] = pixel;

           } // end if

       // advance all the pointers
       dest_addr   += lpitch;
       source_addr += source_bitmap->width;

       } // end for index
   } // end if
   else
   {
   // non-transparent version
   // copy each line of bitmap into destination

   for (index=0; index<source_bitmap->height; index++)
       {
       // copy the memory
       memcpy(dest_addr, source_addr, source_bitmap->width);

       // advance all the pointers
       dest_addr   += lpitch;
       source_addr += source_bitmap->width;

       } // end for index

   } // end else

   // return success
   return(1);

//   } // end if
//else
//   return(0);

} // end Draw_Bitmap

/////////////////////////////////////////////////////////////////////////////
// This function clears the memory for the Primary Surface so that
// we have a clean drawing surface.
//////////////////////////////////////////////////////////////////////////

int DDraw_Fill_Surface(IDirectDrawSurface7 *lpdds,int color)
{
DDBLTFX ddbltfx; // this contains the DDBLTFX structure


// clear out the structure and set the size field 
DDRAW_INIT_STRUCT(ddbltfx);


// set the dwfillcolor field to the desired color
ddbltfx.dwFillColor = color; 

// ready to blt to surface
lpdds->Blt(NULL,       // ptr to dest rectangle
           NULL,       // ptr to source surface, NA            
           NULL,       // ptr to source rectangle, NA
           DDBLT_COLORFILL | DDBLT_WAIT,   // fill and wait                   
           &ddbltfx);  // ptr to DDBLTFX structure

// return success
return(1);
} // end DDraw_Fill_Surface

//////////////////////////////////////////////////////////////
/*
IDirectDrawSurface7 *DDraw_Create_Surface(int width, int height, int mem_flags)
{
// this function creates an offscreen plain surface

DDSURFACEDESC2 ddsd;         // working description
IDirectDrawSurface7 *lpdds;  // temporary surface
    
// set to access caps, width, and height
memset(&ddsd,0,sizeof(ddsd));
ddsd.dwSize  = sizeof(ddsd);
ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;

// set dimensions of the new bitmap surface
ddsd.dwWidth  =  width;
ddsd.dwHeight =  height;

// set surface to offscreen plain
ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | mem_flags;

// create the surface
if (FAILED(lpdd4->CreateSurface(&ddsd,&lpdds,NULL)))
   return(NULL);

// set color key to color 0
DDCOLORKEY color_key; // used to set color key
color_key.dwColorSpaceLowValue  = 0;
color_key.dwColorSpaceHighValue = 0;

// now set the color key for source blitting
lpdds->SetColorKey(DDCKEY_SRCBLT, &color_key);

// return surface
return(lpdds);
} // end DDraw_Create_Surface
*/
/////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// This function creates a DirectDraw surface and then copies the 
// the data from a bitmap onto it.
///////////////////////////////////////////////////////////////////////////////
int Create_Bitmap(BITMAP_IMAGE_PTR image, int x, int y, int width, int height)
{
// this function is used to intialize a bitmap

// allocate the memory
if (!(image->buffer = (unsigned char *)malloc(width*height)))
   return(0);

// initialize variables
//image->state     = BITMAP_STATE_ALIVE;
image->attr      = 0;
image->width     = width;
image->height    = height;
image->x         = x;
image->y         = y;
image->num_bytes = width*height;

// clear memory out
memset(image->buffer,0,width*height);

// return success
return(1);

} // end Create_Bitmap

///////////////////////////////////////////////////////////////////////////////
// This functions is used during the choose car section of the menu.
// It reads a bitmap with bright colors and draws them onto the same bitmap
// image only with darker colors to produce a lighting effect.
///////////////////////////////////////////////////////////////////////////////
void render_light(BITMAP_IMAGE_PTR bitmap1,
				  BITMAP_IMAGE_PTR bitmap2,
				  unsigned char *dest_buffer,
				  int lpitch,
				  int x, int y) {

unsigned char pixel;

unsigned char *dest_addr,   // starting address of bitmap in destination
      *source_addr; // starting adddress of bitmap data in source

int index;
int indey;

	// bitmap1 = landscape
	// bitmap2 = light beam
	dest_addr = dest_buffer + bitmap1->y*lpitch + bitmap1->x + x+y*lpitch;
	source_addr = bitmap1->buffer +x +y*lpitch;

   for (index=0; index<bitmap2->height; index++)
       {
       // copy the memory
       memcpy(dest_addr, source_addr, bitmap2->width);

       // advance all the pointers
       dest_addr   += lpitch;
       source_addr += bitmap1->width;

    } // end for index

   // so now the car background is copied into the dest_addr pointer
   // Now it's time to copy the light_beam bitmap over the dest_addr



    // source is now beam bitmap
	dest_addr = dest_buffer + bitmap2->y*lpitch + bitmap2->x +x +y*lpitch;
	source_addr = bitmap2->buffer;

	for (index = 0; index < bitmap2->height; index++) {
		for (indey = 0; indey < bitmap2->width; indey++) {

			pixel = source_addr[indey];

			if ( pixel !=0)
				dest_addr[indey] = pixel;
		}

		dest_addr += lpitch;
		source_addr += bitmap2->width;
	}
}

///////////////////////////////////////////////////////////
// This function is used to keep track of timing for different parts
// of gameplay
///////////////////////////////////////////////////////////////////////////////
DWORD Start_Clock(void)
{
// this function starts the clock, that is, saves the current
// count, use in conjunction with Wait_Clock()

return(start_clock_count = Get_Clock());

} // end Start_Clock

////////////////////////////////////////////////////////////
//  This function is used to keep a loop executing for a specific number 
//  frames.  We use this to force bumper cars to run at 30 frames per second...
//  regardless of the speed of computer it is executed on.
///////////////////////////////////////////////////////////////////////////////
DWORD Wait_Clock(DWORD count)
{
// this function is used to wait for a specific number of clicks
// since the call to Start_Clock

while((Get_Clock() - start_clock_count) < count);
return(Get_Clock());

} // end Wait_Clock

///////////////////////////////////////////////////////////
DWORD Get_Clock(void)
{
// this function returns the current tick count

// return time
return(GetTickCount());

} // end Get_Clock

//////////////////////////////////////////////////////
//  Releases the bitmap data
///////////////////////////////////////////////////////////////////////////////
int Destroy_Bitmap(BITMAP_IMAGE_PTR image)
{
// this function releases the memory associated with a bitmap

if (image && image->buffer)
   {
   // free memory and reset vars
   free(image->buffer);

   // set all vars in structure to 0
   memset(image,0,sizeof(BITMAP_IMAGE));

   // return success
   return(1);

   } // end if
else  // invalid entry pointer of the object wasn't initialized
   return(0);

} // end Destroy_Bitmap

///////////////////////////////////////////////////////////
//  This checks if the mouse cursor is over a special section of the screen
//  such as in the choose car screen.
///////////////////////////////////////////////////////////////////////////////
int check_mouse_pos(int mx, int my) {


		if (mx > 100 && mx < 200)
			if (my > 220 && my < 270)
				return (0);


		if (mx > 260 && mx < 370)
			if (my > 220 && my < 270)
				return (2);

		
		if (mx > 430 && mx < 530)
			if (my > 220 && my < 270)
				return (1);

		
		if (mx > 245 && mx < 380)
			if (my > 275 && my < 350)
				return (3);

	return (7);
}

///////////////////////////////////////////////////////////////////////////////
//  This function initializes the mouse using DirectInput
///////////////////////////////////////////////////////////////////////////////
int init_mouse() {
	
	if (FAILED(DirectInputCreate(main_instance,
								DIRECTINPUT_VERSION,
								&lpdi, NULL))) {
		// error
		return (1);
	}

	if (FAILED(lpdi->CreateDevice(GUID_SysMouse, 
		&lpdimouse, NULL))) {
		// error 
		return (2);
	}

	if (FAILED(lpdimouse->SetCooperativeLevel(
		main_window_handle,
		DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))) {
		// error
		return (3);
	}

	if (FAILED(lpdimouse->SetDataFormat (&c_dfDIMouse))) {
		// error
		return (4);
	}

	if (FAILED(lpdimouse->Acquire())) {
		// error
		return (5);
	}

	return (0);
}

///////////////////////////////////////////////////////////////////////////////
//  This function is for reading the track collision mask files into
//  the track array.
///////////////////////////////////////////////////////////////////////////////
int readMaskData() {
	// read map data into array
	ifstream fin;
	char tmp;
	const char * fmp = &tmp;
	int y,x;

	switch (gV.trackChosen)
	{
		case 1:
			fin.open ("maps\\track256.txt",ios::in);
			break;
		case 2:
			fin.open ("maps\\mjunk1.txt",ios::in);
			break;
		case 3:
			fin.open ("maps\\metalmask.txt",ios::in);
			break;
		case 4:
			fin.open ("maps\\mthnks.txt",ios::in);
			break;
		case 5:
			fin.open ("maps\\beach.txt",ios::in);
			break;

		default:
			break;
	}

	// now read in map data
	for (y=0; y<480; y++) {
		for (x=0; x<640; x++) {
			fin >> tmp;
            maskData[y][x] = atoi(fmp);
		} // end for x
	} // end for y
	fin.close();

	fin.open("maps\\carMask.txt",ios::in);
	// now read in map data
	for (y=0; y<32; y++) {
		for (x=0; x<32; x++) {
			fin >> tmp;
			carMaskData[y][x] = atoi(fmp);
		} // end for x
	} // end for y

	fin.close();
	return (1);
}

//////////////////////////////////////////////////////////////////////////////////////////
//  This function creates the DirectDraw surfaces for each of the 36 car frames for each
//  of the 4 cars
///////////////////////////////////////////////////////////////////////////////
int Create_Car(CAR &Car,int x, int y, int num_frames, int attr, int mem_flags) {

DDSURFACEDESC2 ddsd; // used to create surface
int index;           // looping var

Car.set_num_frames(num_frames);
Car.set_attr(attr);

// set all images to null
for (index=0; index<MAX_CAR_FRAMES; index++)
    Car.images[index] = NULL;

// now create each surface
for (index=0; index<36; index++)
    {
    // set to access caps, width, and height
    memset(&ddsd,0,sizeof(ddsd));
    ddsd.dwSize  = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;

    ddsd.dwWidth  = 32; 
    ddsd.dwHeight = 32;

    // set surface to offscreen plain
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | mem_flags;

    // create the surfaces, return failure if problem
    if (FAILED(lpdd4->CreateSurface(&ddsd,&(Car.images[index]),NULL)))
        return(0);

    // set color key to color 0
    DDCOLORKEY color_key; // used to set color key
    color_key.dwColorSpaceLowValue  = 0;
    color_key.dwColorSpaceHighValue = 0;

    // now set the color key for source blitting
    (Car.images[index])->SetColorKey(DDCKEY_SRCBLT, &color_key);
    
    } // end for index


// return success
return (1);


}

///////////////////////////////////////////////////////////////////////////////////////////////
//  This function loads a section of the carline bitmap that should be in one
//  single frame of a car animation.  
///////////////////////////////////////////////////////////////////////////////
int Load_Frame(CAR & Car, BITMAP_FILE_PTR bitmap, int frame,int cx,int cy) {

UCHAR *source_ptr,*dest_ptr;

DDSURFACEDESC2 ddsd;  //  direct draw surface description 


// extract bitmap data
source_ptr = bitmap->buffer + cy*bitmap->bitmapinfoheader.biWidth+cx;

// get the addr to destination surface memory

// set size of the structure
ddsd.dwSize = sizeof(ddsd);

// lock the display surface
if (FAILED((Car.images[frame])->Lock(NULL,
                           &ddsd,
                           DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR,
                           NULL))) {
	return (0);
}

// assign a pointer to the memory surface for manipulation
dest_ptr = (UCHAR *)ddsd.lpSurface;

// iterate thru each scanline and copy bitmap
// car.getheight
for (int index_y=0; index_y<32; index_y++)
    {
    // copy next line of data to destination
    memcpy(dest_ptr, source_ptr, 32);

    // advance pointers
	dest_ptr   += 32;
    source_ptr += bitmap->bitmapinfoheader.biWidth;
    } // end for index_y

// unlock the surface 
(Car.images[frame])->Unlock(NULL);
	return (1);
}

///////////////////////////////////////////////////////////////////////////////////
//  This function displays one of the car animation frames on the Primary Surface
///////////////////////////////////////////////////////////////////////////////
int Draw_Car(CAR &Car, IDirectDrawSurface7 *dest) 
{
// draw a CAR at the x,y defined in the CAR object
// on the destination surface defined in dest

RECT dest_rect,   // the destination rectangle
     source_rect; // the source rectangle                             

double new_x, new_y;
Car.get_position(new_x, new_y);
// fill in the destination rect
dest_rect.left   = (long)new_x;
dest_rect.top    = (long)new_y;
dest_rect.right  = (long)new_x+32;
dest_rect.bottom = (long)new_y+32;

// fill in the source rect
source_rect.left    = 0;
source_rect.top     = 0;
source_rect.right   = 32;
source_rect.bottom  = 32;

// blt to destination surface
if (FAILED(dest->Blt(&dest_rect, Car.images[(Car.get_head_sector()-1)],
          &source_rect,(DDBLT_WAIT | DDBLT_KEYSRC),
          NULL))) {
    return(0);
}

// return success
return(1);
} 

int Create_Object(LPDIRECTDRAWSURFACE7 * images, int num_frames, int sizeX, int sizeY) {


DDSURFACEDESC2 ddsd; // used to create surface
int index;           // looping var

// set all images to null
for (index=0; index<num_frames; index++)
    images[index] = NULL;

// now create each surface
for (index=0; index<num_frames; index++)
    {
    // set to access caps, width, and height
    memset(&ddsd,0,sizeof(ddsd));
    ddsd.dwSize  = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;

    ddsd.dwWidth  = sizeX; 
    ddsd.dwHeight = sizeY;

    // set surface to offscreen plain
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;

    // create the surfaces, return failure if problem
    if (FAILED(lpdd4->CreateSurface(&ddsd,&images[index],NULL)))
        return(0);

    // set color key to color 0
    DDCOLORKEY color_key; // used to set color key
    color_key.dwColorSpaceLowValue  = 0;
    color_key.dwColorSpaceHighValue = 0;

    // now set the color key for source blitting
	//Car.setColorKey(index, DDCKEY_SRCBLT, &color_key);
    images[index]->SetColorKey(DDCKEY_SRCBLT, &color_key);
    
    } // end for index


// return success
return (1);


}

int Draw_Object(LPDIRECTDRAWSURFACE7 & image, LPDIRECTDRAWSURFACE7 dest,int x, int y, int sizeX, int sizeY) 
{
// draw a CAR at the x,y defined in the CAR object
// on the destination surface defined in dest

RECT dest_rect,   // the destination rectangle
     source_rect; // the source rectangle                             

int new_x = x;
int new_y = y;

// fill in the destination rect
dest_rect.left   = (long)new_x;
dest_rect.top    = (long)new_y;
dest_rect.right  = (long)new_x+sizeX;
dest_rect.bottom = (long)new_y+sizeY;

// fill in the source rect
source_rect.left    = 0;
source_rect.top     = 0;
source_rect.right   = sizeX;
source_rect.bottom  = sizeY;

// blt to destination surface
if (FAILED(dest->Blt(&dest_rect, image,
          &source_rect,(DDBLT_WAIT | DDBLT_KEYSRC),
          NULL))) {
    return(0);
}

// return success
return(1);
} 


int Load_Frame_Object(LPDIRECTDRAWSURFACE7 & image, BITMAP_FILE_PTR bitmap, int frame,int cx,int cy,int sizeX, int sizeY) {

UCHAR *source_ptr,*dest_ptr;

DDSURFACEDESC2 ddsd;  //  direct draw surface description 

// extract bitmap data
source_ptr = bitmap->buffer + cy*bitmap->bitmapinfoheader.biWidth+cx;

// get the addr to destination surface memory

// set size of the structure
ddsd.dwSize = sizeof(ddsd);

// lock the display surface
if (FAILED(image->Lock(NULL,
                           &ddsd,
                           DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR,
                           NULL))) {
	return (0);
}

// assign a pointer to the memory surface for manipulation
dest_ptr = (UCHAR *)ddsd.lpSurface;

// iterate thru each scanline and copy bitmap
// car.getheight
for (int index_y=0; index_y<sizeY; index_y++)
    {
    // copy next line of data to destination
    memcpy(dest_ptr, source_ptr, sizeX);

    // advance pointers
	dest_ptr   += sizeX;
    source_ptr += bitmap->bitmapinfoheader.biWidth;
    } // end for index_y

	// unlock the surface 
	image->Unlock(NULL);
	return (1);
}

int find_Letter(char letter)
{
	// Using this scheme, 0 will be the index for 'A', 1 for 'B', etc.
	return (__toascii(letter) - 65);
}











int packMask(BITMAP_FILE_PTR bitmap, int lpitch) {

	UCHAR * source_ptr;
	ofstream out;
	out.open("out.txt", ios::out);

    // extract bitmap data
    source_ptr = bitmap->buffer;

	for (int y=0; y<bitmap->bitmapinfoheader.biHeight; y++) {

		for (int x=0; x<bitmap->bitmapinfoheader.biWidth; x++) {

			if (*source_ptr == 0) {
			 out << "0";
			} else {
		     out << "1";
			}
			source_ptr++;
		}
		out << endl;
	}

	out.close();
	return (1);
}





