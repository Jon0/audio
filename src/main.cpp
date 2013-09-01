/*
 * main.cpp
 *
 *  Created on: 29/08/2013
 *      Author: asdf
 */

#include <stdlib.h>
#include <GL/glut.h>

#include "window/MainWindow.h"
#include "playback/Playback.h"
#include "playback/source.h"
#include "buffer/Random.h"

using namespace std;

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	//new MainWindow(800, 600);

	source *b = new Random();
	Playback *play = new Playback();
	play->playall(b);
	//play->playTest();



	return EXIT_SUCCESS;
}



