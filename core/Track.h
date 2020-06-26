//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
//
// This track object is used to determine starting positions, starting
// positions, and midpoints for the different tracks.
//
// The track is first initialized with hard-coded values when it is
// constructed.  From that point on, the methods of the class retrieve the
// values so that the cars can determine when they have passed the starting
// line, which direction to face, where to start, etc.
//
// Track.h: interface for the Track class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRACK_H__B0BC34D2_3653_47C9_814E_FF318BC081B3__INCLUDED_)
#define AFX_TRACK_H__B0BC34D2_3653_47C9_814E_FF318BC081B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define	 RANDOMSPOTS	5

class Track  
{
	public:
		Track(int whichBoard);
		// Default constructor.  A value from 1 to n, with n being the
		// number of tracks, must be passed in.
		
		void getMidpoint(int &x, int &y) const;
		// This retrieves the x and y values of the midpoint.
		// Note that x is a minimum value, and y is a maximum value, 
		// so the car must check values > x and < y.  This sets up a 
		// rectangle of sorts that the car must be in.

		void getStart(int &x, int &y) const;
		// This retrieves the x and y values of the starting line.
		// This is similar to the midpoint function although this time
		// we are using the starting line of the track.

		void getStartingPosition(int car, double &x, double &y) const;
		// Retrieve the starting position of a specific car.  A car 
		// number from 1 to 4 must be passed in.

		int getStartingDirection() const;
		// Retrieves the default starting position of the car, so that
		// all cars line up correctly when they start on the starting
		// line.

		void getRandomPosition(int &x, int &y);
		// This retrieves a random position from the track, so that
		// a power-up or other item can be placed there.  This is needed
		// so that the power-ups are not placed in walls or other places
		// where the cars cannot get to them.

		void releasePosition(int x, int y);
		// Tell the track object we are no longer using this random
		// point.

	private:
		// These are the x and y values of the midpoint and starting
		// lines
		int xMidpoint;
		int xStart;
		int yMaxMidpoint;
		int yMinStart;

		// This is the direction that the cars face in each track
		int startingDirection;

		// These are the x and y values of the starting position
		// of each car.
		double startPositionxCar[4];
		double startPositionyCar[4];

		// The random positions of the power-ups, and whether or not
		// they are in use
		int randomPositionsx[RANDOMSPOTS];
		int randomPositionsy[RANDOMSPOTS];
		bool inUse[RANDOMSPOTS];

};

#endif // !defined(AFX_TRACK_H__B0BC34D2_3653_47C9_814E_FF318BC081B3__INCLUDED_)
