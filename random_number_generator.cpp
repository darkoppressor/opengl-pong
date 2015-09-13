/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#include "random_number_generator.h"

#include <iostream>
#include <cstdlib>

using namespace std;

/**This function randomly selects a number from lownum to highnum and then returns it to where it was called.
Using this we can randomly generate numbers anywhere in the game whenever we need them.*/
int random_range(int lownum, int highnum)
{
	if(lownum > highnum)
	swap(lownum, highnum);
	int range = highnum - lownum + 1;
	return lownum + int(range * rand()/(RAND_MAX + 1.0));
}
