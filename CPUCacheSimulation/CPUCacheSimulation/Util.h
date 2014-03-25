#pragma once

static int powbase2(int);

static int powbase2(unsigned int power)
{
	int result = 1;
	for (unsigned int i = 0; i < power; i++)
		result *= 2;
	return result;
}

// could write a static report() function for printing messages to screen
// report function does nothing if bool debug = false