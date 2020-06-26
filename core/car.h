//////////////////////////////////////////////////////////////////////
// Tim Rudowski
// Christopher Bubeck
// Senior Project
// Due Date:  11/29/00
//
// car.h : The CAR class is our main data structure.  It contains
// variables and methods for manipulating the CAR data object.
//
//////////////////////////////////////////////////////////////////////

#ifndef CAR_H
#define CAR_H


#include <ddraw.h>

class CAR 
{
	public:
		// default constructor
		CAR();

		// default destructor
		~CAR();

		// returns sector of collision
		int compute_collision(double ox, double oy, int object_type);

		// sets position
		void set_position(double cx, double cy);

		// returns position to paramaters of function call
		void get_position(double &cx, double &cy);

		// turn left by one increment
		void turn_left();

		// same for right
		void turn_right();

		// returns sector number that car is facing
		int get_head_sector();
		void set_head_sector(int sector);

		// increment speed by 0.1
		void accelerate();

		// Update current car's position
		void move();

		// Set car's speed to opposite speed.
		void reverse_speed();

		// decrement speed by 0.1
		void decelerate();

		// Increase maximum possible speed
		void increment_max_speed();

		// Decrease maximum possible speed
		void decrement_max_speed();

		// set speed of car
		void set_speed(double speed);

		// return opposite sector of given sector
		int collision_type(int collide_sector);

		// retrieve speed for conservation of energy cases
		double get_speed();

		// raises the damage according to collisions from other cars
		void raise_damage(int damageAmount);

		// returns damage amount
		int get_damage();

		// sets number of animation frames
		void set_num_frames(int frames);

		// sets current animation frame
		void set_curr_frame(int frame);

		// sets attributes for DD surface of car animations.
		void set_attr(int attr_val);
		
		// gets current animation frame
		int get_curr_frame();

		// gets number of laps successfully completed in racing mode.
		int getLapsCompleted() const;

		// returns player number of current car
		int getCarNumber() const;

		// sets player number of current car
		void setCarNumber(int number);

		// resets car variables to default setting
		void reset();

		// tells current car that it has posession of the flag
		void acquire_flag();

		// tells car that it has lost posession of the flag
		void lose_flag();

		// tells car if it has the flag or not
		bool get_flag_status();

		// increments flag holding timer
		void increment_flag();

		// returns amount of time that flag has been held.
		int get_flag_time();

		// returns explosion frame number
		int get_explode_sequence();

		// array of DD images for car animation.
		LPDIRECTDRAWSURFACE7 images[36]; // the bitmap images DD surfaces

	protected:

		// explodes car and boots player
		void explode();

		// returns sector that car has collided in
		int return_collision_sector(int bit);

		// reads in linked list of sector information from settings.txt
		int read_sectors();

	private:
		int attr;			// attributes for DD surfaces of car images
		int num_frames;	    // total number of frames for car animation
        int curr_frame;     // current animation frame
		int curr_animation; // index of current animation
        int anim_counter;   // used to time animation transitions
        int anim_index;     // animation element index
        int anim_count_max; // number of cycles before animation
	    int direction;	    // sector number that car is facing
		int dirIndex;		// index of look-up table
		double accel;		// acceleration number for car
		int damage;			// damage amount of current car
        double x,y;         // position bitmap will be displayed at
		double maxSpeed;    // maximum speed possible

		bool midPointPassed; // has midPoint been passed on a track?
		int lapsCompleted;   // number of laps successsfully completed 
		int carNumber;       // player number of car
		bool hasFlag;        // has flag or not?
		int timeWithFlag;    // how long have we had the flag?
		int explodeSequence; // explosion sequence counter

		int width;	
		int height;  // the width and height of the car
		int width_fill;

};

#endif