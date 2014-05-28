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
#include "buffer/TestBuffer.h"

using namespace std;

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	srand( time( NULL ) );

	//new MainWindow(800, 600);

	source *b = new TestBuffer();
	Playback *play = new Playback();
	play->playall(b);
	//play->playTest();



	return EXIT_SUCCESS;
}



