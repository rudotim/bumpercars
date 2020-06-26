//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
//
// Track.cpp: implementation of the Track class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bumpercars.h"
#include "Track.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Constructor			Track::Track(int)
//////////////////////////////////////////////////////////////////////

Track::Track(int whichBoard)
{
	// Depending on the number of the board passed in, the values for
	// midpoint, starting line, etc. are saved in the track class.

	for (int i = 0; i < RANDOMSPOTS; i++)
		inUse[i] = false;

	switch (whichBoard)
	{
		case 1:
			xMidpoint = 382;
			xStart = 270;
			yMaxMidpoint = 220;
			yMinStart = 194;

			startingDirection = 27;

			startPositionxCar[0] = 282.0;
			startPositionyCar[0] = 144.0;
			startPositionxCar[1] = 282.0;
			startPositionyCar[1] = 74.0;
			startPositionxCar[2] = 320.0;
			startPositionyCar[2] = 144.0;
			startPositionxCar[3] = 320.0;
			startPositionyCar[3] = 74.0;

			randomPositionsx[0] = 600;
			randomPositionsy[0] = 400;
			randomPositionsx[1] = 184;
			randomPositionsy[1] = 430;
			randomPositionsx[2] = 486;
			randomPositionsy[2] = 38;
			randomPositionsx[3] = 60;
			randomPositionsy[3] = 58;
			randomPositionsx[4] = 250;
			randomPositionsy[4] = 252;

			break;
		case 2:
			xMidpoint = 520;
			xStart = 180;
			yMaxMidpoint = 152;
			yMinStart = 182;

			startingDirection = 27;

			startPositionxCar[0] = 194.0;
			startPositionyCar[0] = 68.0;
			startPositionxCar[1] = 194.0;
			startPositionyCar[1] = 128.0;
			startPositionxCar[2] = 224.0;
			startPositionyCar[2] = 68.0;
			startPositionxCar[3] = 224.0;
			startPositionyCar[3] = 128.0;

			randomPositionsx[0] = 22;
			randomPositionsy[0] = 36;
			randomPositionsx[1] = 40;
			randomPositionsy[1] = 440;
			randomPositionsx[2] = 536;
			randomPositionsy[2] = 24;
			randomPositionsx[3] = 598;
			randomPositionsy[3] = 410;
			randomPositionsx[4] = 468;
			randomPositionsy[4] = 228;

			break;
		case 3:
			xMidpoint = 312;
			xStart = 312;
			yMaxMidpoint = 128;
			yMinStart = 122;

			startingDirection = 27;

			startPositionxCar[0] = 333.0;
			startPositionyCar[0] = 45.0;
			startPositionxCar[1] = 333.0;
			startPositionyCar[1] = 85.0;
			startPositionxCar[2] = 383.0;
			startPositionyCar[2] = 45.0;
			startPositionxCar[3] = 383.0;
			startPositionyCar[3] = 85.0;

			randomPositionsx[0] = 220;
			randomPositionsy[0] = 432;
			randomPositionsx[1] = 392;
			randomPositionsy[1] = 436;
			randomPositionsx[2] = 36;
			randomPositionsy[2] = 390;
			randomPositionsx[3] = 578;
			randomPositionsy[3] = 52;
			randomPositionsx[4] = 38;
			randomPositionsy[4] = 86;

			break;
		case 4:
			xMidpoint = 423;
			xStart = 187;
			yMaxMidpoint = 395;
			yMinStart = 136;

			startingDirection = 27;

			startPositionxCar[0] = 212.0;
			startPositionyCar[0] = 49.0;
			startPositionxCar[1] = 212.0;
			startPositionyCar[1] = 98.0;
			startPositionxCar[2] = 262.0;
			startPositionyCar[2] = 49.0;
			startPositionxCar[3] = 262.0;
			startPositionyCar[3] = 98.0;

			randomPositionsx[0] = 165;
			randomPositionsy[0] = 205;
			randomPositionsx[1] = 596;
			randomPositionsy[1] = 385;
			randomPositionsx[2] = 52;
			randomPositionsy[2] = 433;
			randomPositionsx[3] = 405;
			randomPositionsy[3] = 32;
			randomPositionsx[4] = 505;
			randomPositionsy[4] = 336;

			break;
		case 5:
			// Capture the flag board, we do not have to count laps
			xMidpoint = 0;
			xStart = 0;
			yMaxMidpoint = 0;
			yMinStart = 0;

			startingDirection = 27;

			startPositionxCar[0] = 560.0;
			startPositionyCar[0] = 58.0;
			startPositionxCar[1] = 38.0;
			startPositionyCar[1] = 76.0;
			startPositionxCar[2] = 36.0;
			startPositionyCar[2] = 348.0;
			startPositionxCar[3] = 534.0;
			startPositionyCar[3] = 368.0;

			randomPositionsx[0] = 82;
			randomPositionsy[0] = 56;
			randomPositionsx[1] = 120;
			randomPositionsy[1] = 442;
			randomPositionsx[2] = 382;
			randomPositionsy[2] = 30;
			randomPositionsx[3] = 536;
			randomPositionsy[3] = 292;
			randomPositionsx[4] = 432;
			randomPositionsy[4] = 214;

			break;

		default:
			break;
	}
}


//////////////////////////////////////////////////////////////////////
//				Track::getMidpoint(int &, int &) const
//////////////////////////////////////////////////////////////////////
// This is called when the midpoint of the track is needed.

void Track::getMidpoint(int &x, int &y) const
{
	x = xMidpoint;
	y = yMaxMidpoint;
}

//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//				Track::getStart(int &, int &) const
//////////////////////////////////////////////////////////////////////
// This is called when the starting point of the track is needed.

void Track::getStart(int &x, int &y) const
{
	x = xStart;
	y = yMinStart;
}

//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//		Track::getStartingPosition(int, double &, double &) const
//////////////////////////////////////////////////////////////////////
// This is called when the starting position of a particular car is
// needed.

void Track::getStartingPosition(int car, double &x, double &y) const
{
	x = startPositionxCar[car];
	y = startPositionyCar[car];
}

//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//			Track::getStartingDirection() const
//////////////////////////////////////////////////////////////////////
// This returns the starting direction for the cars when they are
// on the starting line.

int Track::getStartingDirection() const
{
	return startingDirection;
}

//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//			Track::getRandomPosition(int &, int &)
//////////////////////////////////////////////////////////////////////
// This returns a random position where a power-up or other item
// can be placed on the track.

void Track::getRandomPosition(int &x, int &y)
{	
	bool done = false;
	int i = 0;

	while (!done)
	{
		// If we find a position not being used, then return
		// that position, and put it inUse
		if ((i < RANDOMSPOTS) && (inUse[i] != true))
		{
			x = randomPositionsx[i];
			y = randomPositionsy[i];
			inUse[i] = true;
			done = true;
		}

		// If we have no free positions then return dummy values
		// of 0, 0
		else if (i == RANDOMSPOTS)
		{
			x = 0;
			y = 0;
			done = true;
		}
		i++;
	}
}

//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//				Track::releasePosition(int, int)
//////////////////////////////////////////////////////////////////////
// This releases a position so that another powerup can use it.

void Track::releasePosition(int x, int y)
{
	int i;

	// Check every random position we have in the track.  If it matches
	// what was passed in, then release it.  If nothing matches then
	// this for will be pretty much useless and nothing will happen.
	for (i = 0; i < RANDOMSPOTS; i++)
	{
		if ((x == randomPositionsx[i]) && (y == randomPositionsy[i]))
		{
			inUse[i] = false;
		}
	}
}

//////////////////////////////////////////////////////////////////////

