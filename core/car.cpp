//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
//
// car.cpp : implementation file of the car class
//
//////////////////////////////////////////////////////////////////////
// CAR.CPP

#include "stdafx.h"

#include <fstream.h>
#include <mmsystem.h>
#include "bumpercars.h"
#include "Multiplayer.h"
#include "car.h"
#include "track.h"
#include "functions.h"
#include "mainplay.h"

extern gameVariables gV;
extern Multiplayer mpDlg;

// This variable is used for the read_sectors() function.  Since it is only needed to run once,
// this variable makes sure that it IS only run once.
static int read=0;

// There are only 36 frames needed to make one bumper car turn completely.
static const int MAX_CAR_FRAMES = 36;

/*
//  The following two arrays are look-up tables for the 360 degree turns that each bumper car is 
//  capable of.  There are 36 indicies that hold 9 degree slices of a 360 degree circle. 
*/

static const double dirx[36] = {
0.0000,
0.173561,
0.341854,
0.49977,
0.642516,
0.76576,
0.86576,
0.939481,
0.984685,
1,
0.984961,
0.940025,
0.866556,
0.766783,
0.643736,
0.501149,
0.34335,
0.175129,
0.000000,
-0.171992,
-0.340357,
-0.49839,
-0.641295,
-0.764735,
-0.864962,
-0.938934,
-0.984406,
-1,
-0.985235,
-0.940567,
-0.86735,
-0.767805,
-0.644954,
-0.502527,
-0.344846,
-0.176697,
 };

static const double diry[36] = {
-1,
-0.985235,
-0.940567,
-0.86735,
-0.767805,
-0.644954,
-0.502527,
-0.344846,
-0.176697,
0.0000,
0.173561,
0.341854,
0.49977,
0.642516,
0.76576,
0.86576,
0.939481,
0.984685,
1,
0.984961,
0.940025,
0.866556,
0.766783,
0.643736,
0.501149,
0.34335,
0.175129,
0.000000,
-0.171992,
-0.340357,
-0.49839,
-0.641295,
-0.764735,
-0.864962,
-0.938934,
-0.984406,
};


/*
//  This is the sector structure that keeps track of collision information.  In the constructing of one
//  bumper car object, there is a linked list created of sector structs, 36 links long.  These links hold
//  the sector data used to designate each section of a bumper car into 36 slices of 9 degrees.
*/

// The sector collision information is read into a linked list of type SECTORS_TYP.  This list is then
// used in the compute_collision function to search in the file carmask.cpp.  This list is overlayed onto the
// track bit information in the respective mask file in the maps directory.  The function then bitwise ands 
// the current position data from maskData[y][x] with carMaskData[y][x].  If the result is true, then there is
// a collision and the respective sector is found from that collision point.  Otherwise there is no collision.

typedef struct SECTORS_TYP {
		int bit;
		int sector;
		SECTORS_TYP * next;
		SECTORS_TYP * prev;

}  SECTOR;

// Create head and rear nodes.
SECTOR * rear_sector = new SECTOR;
SECTOR * head_sector = new SECTOR;

// Default Constructor
CAR::CAR() {
	direction =   36;
	damage =      0;
	x =			  50;
	y =			  50;
	dirIndex =    0;
	accel =       0;
	width =		  32;
	height=		  32;
	width_fill =  0;
	curr_frame =  0;
	num_frames =  36;

	midPointPassed = false;
	lapsCompleted = 0;
	carNumber = 0;
	maxSpeed = 5.0;
	hasFlag = false;
	timeWithFlag = 0;
	explodeSequence = 0;

	// read sectors into linked list once
	if (!read) {
		read_sectors();
		read = 1;
	}
};

// Destructor
CAR::~CAR()
{
	delete images[36];
}

/*
//  This function is responsible for determining if the current car has collided with an object, a wall or 
//  another bumper car.  The ox and oy are the x and y coordinates of the current car, respectively.  The object
//  type is either 1 or 2 depending on whether you're testing for wall collision or car/power-up collision, 
//  respectively.
*/
int CAR::compute_collision(double ox, double oy, int object_type) {

if (damage >= 100)
	explode();

int foreignX = (int)ox;
int foreignY = (int)oy;
int takeX, takeY;
int putX, putY;
int putUntilX, putUntilY;
int dx,dy;
dx = abs((int)x-foreignX);
dy = abs((int)y-foreignY);

int destX = (int)x;
int destY = (int)y;
int once=0;
int fx,fy;
int carY=0, carX=0;
int bitCount=0;
int sector_number=0;
int collided_with_wall=0;
int collided_with_car=0;

	if (object_type==2) {
		// approach foreign object from top left
		if (x+32 > foreignX && x<foreignX)
			if (y+32 > foreignY && y<foreignY)
				return 1;

		// approach foreign object from top right
		if (x<foreignX+16 && x+32 > foreignX)
			if (y+32 > foreignY && y<foreignY)
				return 1;

		// approach foreign object from bottom left
		if (x+32 > foreignX && x<foreignX)
			if (y<foreignY+16 && y>foreignY)
				return 1;
		// approach foreign object from bottom right
		if (x<foreignX+16 && x+32 > foreignX)
			if (y<foreignY+16 && y>foreignY)
				return 1;

		return 0;
	}




if (foreignX>x && foreignY<y) {
	// if foreign car is approaching from top right
	takeX = dx;
	takeY = 32-dy;

	putX = 0;
	putY = dy;

	putUntilX = 32-dx;
	putUntilY = 32;

}
if (foreignX<x && foreignY>y) {
	// if foreign car is approaching from bottom left
	takeX = 32-dx;
	takeY = dy;

	putX = dx;
	putY = 0;

	putUntilX = 32;
	putUntilY = 32-dy;

}

if (foreignX<x && foreignY<y) {
	// if foreign car is approaching top left
	takeX = dx;
	takeY = 32-dy;

	putX = 0;
	putY = dy;

	putUntilX = 32-dx;
	putUntilY = 32;
}

if (foreignX>x && foreignY>y) {
	// if foreign car is approaching from bottom right
	takeX = dx;
	takeY = 32-dy;

	putX = 0;
	putY = dy;

	putUntilX = 32-dx;
	putUntilY = 32;

}

for (fy=destY; fy<(destY+32); fy++) {
	for (fx=destX; fx<(destX+32); fx++) {
		bitCount++;

		switch (object_type)
		{
			// check car collision with track bit data
			case 0:
				collided_with_wall = (maskData[fy][fx] & carMaskData[carY][carX]);
				break;

			// check car collision with other carMask bit data
			case 1:
				if (carY >= putY && carY <= putUntilY) {
					if (carX >= putX && carX <= putUntilX) {
						collided_with_car = (carMaskData[carY][carX] & carMaskData[takeY][takeX]);
						takeX++;
						once=1;
					}
				}
				break;

			default:
				break;
		}


		if (collided_with_wall || collided_with_car) {
			// collision
			// now find head sector
			sector_number = return_collision_sector(bitCount);
			sector_number = collision_type(sector_number);

			if (collided_with_wall)
				raise_damage( (abs(accel)) * 3);	

			return (sector_number); // bottom impact
			
		}
		carX++;
	}
	if (once) {
		takeX=0;
		takeY++;
		once=0;
	}

	carX=0;
	carY++;

}
	return (0);
}

// This function sets the car's speed to the opposite speed of which it is traveling.
void CAR::reverse_speed() {

	accel = -(accel / 1.75);

	if ((accel < 1.0) && (accel > -1.0))
		accel = 0;

}

// This function sets the car's speed.
void CAR::set_speed(double speed) {
	accel = speed;
}

// This function sets the car's position.
void CAR::set_position(double cx, double cy) {

	x = cx;
	y = cy;

	int xMid, xStart;
	int yMid, yStart;

	gV.mainTrack->getMidpoint(xMid, yMid);
	gV.mainTrack->getStart(xStart, yStart);


	if ((x < xStart) && (y < yStart))
	{	
		if (midPointPassed == true)
		{
			lapsCompleted++;

			if (lapsCompleted > gV.numberOfLaps)
				lapsCompleted = gV.numberOfLaps;
				
			midPointPassed = false;
		}
	}
	else
	{
		if ((x > xMid) && (y > yMid))
		{
			midPointPassed = true;		
		}
	}
}

// This function returns the position of the car in the variables cx and cy.
void CAR::get_position(double &cx, double &cy) {
	cx = x;
	cy = y;
}

// This function decrements the turn counter for a bumper car by 1.
void CAR::turn_left() {
	direction--;

	if (direction < 1)
		direction = 36;

}

// This function increments the turn counter for a bumper car by 2.
void CAR::turn_right() {
	direction++;

	if (direction > 36)
		direction = 1;
}


// This function returns the head sector of the current car.
int CAR::get_head_sector() {
	return direction;
}

// This function sets the head sector of the current car.
void CAR::set_head_sector(int sector) {
	direction = sector;
}

// This function increments the current car's speed by 0.1.
void CAR::accelerate() {
	accel+=0.1;

	if (accel > maxSpeed)
		accel = maxSpeed;

}

// THis function updates the car's position.
void CAR::move() {

	double tempx;
	double tempy;

	tempx = x + dirx[(direction-1)] * accel;
	tempy = y + diry[(direction-1)] * accel;
	
	set_position(tempx, tempy);
}

// THis function decrements the car's speed by 0.1.
void CAR::decelerate() {
	accel-=0.1;

	if (accel < -2.0)
		accel = -2.0;
}

// This function returns the car's speed.
double CAR::get_speed() {
	return accel;
}

// THis function raises the damage of the car after it has collided with an object.  If the damage
// goes over 99, the explode function is called and that car is destroyed.
void CAR::raise_damage(int damageAmount) {
	damage+=damageAmount;

	if (damage < 0)
		damage = 0;

	if (damage >= 100)
		explode();

}

// This function returns the damage amount of the current car.
int CAR::get_damage() {
	return damage;
}

// This function sets the number of animation sequence frames the the car's animation.
void CAR::set_num_frames(int frames) {
	num_frames = frames;
}

// This function sets the DirectDraw surface attributes for each image of the car's image surface array.
void CAR::set_attr(int attr_val) {
	attr = attr_val;
}

// This function increments the highest possible speed for the current car.
// The min and max values of this are 3 and 7.
void CAR::increment_max_speed() {
	if (maxSpeed < 7)
		maxSpeed++;
}

// This function increments the lowerst possible speed for the current car.
// The min and max values of this are 3 and 7.

void CAR::decrement_max_speed() {
	if (maxSpeed > 3)
		maxSpeed--;
}

// THis function returns the current animation frame number of the current car.
int CAR::get_curr_frame() {
	return curr_frame;
}

// This function sets the current animatoin frame of the current car.
void CAR::set_curr_frame(int frame) {
	curr_frame = frame;
}

// This function returns all the car's private variables to their default settings.
void CAR::reset() {
	accel = 0.0;
	damage = 0;
	lapsCompleted = 0;
	midPointPassed = false;
	hasFlag = false;
	maxSpeed = 5.0;
	timeWithFlag = 0;
}

// This function returns the player number of the current car.
int CAR::getCarNumber() const
{
	return carNumber;
}

// THis function sets the player number of the current car.
void CAR::setCarNumber(int number)
{
	carNumber = number;
}

// This function controls the explode sequence of a car.  If the damage goes over 99, this funciton
// is called and an explosion animation is played.  After this, the car is reset and restarted at the 
// beginning of the track it is on.

void CAR::explode()
{
	
	drawMainWindow();

	explodeSequence++;

	// explode animation sequence is 15 frames long.
	// We wail till 15 frames go by till we reset the car data.
	if (explodeSequence >= 15)
	{
		PlaySound("explode.wav", NULL, SND_FILENAME | SND_ASYNC);

		double x, y;
		gV.mainTrack->getStartingPosition(carNumber, x, y);
		set_position(x, y);
		set_head_sector(gV.mainTrack->getStartingDirection());

		if (hasFlag)
		{
			gV.canCapture = true;
			gV.whoHasFlag = -1;
		}

		damage = 0;
		accel = 0.0;
		midPointPassed = false;
		maxSpeed = 5.0;
		hasFlag = false;
		explodeSequence = 0;

		if (gV.multiplayerEnabled)
			mpDlg.m_DirectPlay.Send_UnAcquire_Message_To_All();
	}
}

// THis function returns the lap counter of the current car.  It checks how many complete laps
// the car has completed.
int CAR::getLapsCompleted() const
{
	return lapsCompleted;
}

// This function tells the current car that it now has the flag
void CAR::acquire_flag() {
	hasFlag = true;
}

// THis function tells the current car that it has lost the flag.
void CAR::lose_flag() {
	hasFlag = false;
}

// THis function checks to see if the current car has control of the flag.
bool CAR::get_flag_status() {
	return hasFlag;
}

// THis function increments the flag timer of the current car.
void CAR::increment_flag() {
	timeWithFlag++;
}

// This function returns the flag timer of the current car.
int CAR::get_flag_time() {
	return (timeWithFlag / 4);
}

// THis function returns the explosion sequence number of the explosion animation.
int CAR::get_explode_sequence() {
	return explodeSequence;
}

// THis function returns the opposite sector of the sector passed.
int CAR::collision_type(int collide_sector) {

//	/*
	int temp = collide_sector+18;
//	if (temp>36)
//		temp = (temp-36);

	return (temp);
}

	
// This function returns the sector number of the collision point of a bumper car.
int CAR::return_collision_sector(int bit) {
	SECTOR * ptr;
	ptr = head_sector;

	while (ptr->next != NULL) {
		if (ptr->bit == bit) {
			return ptr->sector;
		}
		ptr = ptr->next;
	}
	return 0;
}

/////////////////////////////////////////////////////////////////
// THis function reads the sector information in the file settings.txt into the car collision
// linked list.  This is later used to tell which sector the car collided at.
//
int CAR::read_sectors() {

	SECTOR * ptr;
	head_sector = NULL;
	rear_sector = NULL;

	ifstream fine;
	fine.open("settings.txt",ios::in);
	char tmp[4];
	char sec[4];
	
	while (!fine.eof()) {
		fine >> tmp;
		if (!(strcmp(tmp, "***")) ) {
			fine >> tmp;
			strcpy(sec,tmp);
		} else {
			SECTOR * add = new SECTOR;  // create new node
			add->sector  = atoi(sec);   // insert sector number
   			add->bit     = atoi(tmp);   // insert bit value
			add->next    = NULL;

			if (head_sector == NULL) {
				add->prev = NULL;
				head_sector = add;
			} else {
				add->prev = rear_sector;
				rear_sector->next = add;
			}

			rear_sector = add;
		}
	}
	
	fine.close();

	ptr = head_sector;
    return (1);
	
}

 
