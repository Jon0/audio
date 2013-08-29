/*
 * main.cpp
 *
 *  Created on: 29/08/2013
 *      Author: asdf
 */

#include <stdlib.h>
#include "playback/Pulse.h"

using namespace std;

int main(int argc, char *argv[]) {
	Pulse *p = new Pulse(argv[0]);
	delete p;

	return EXIT_SUCCESS;
}



