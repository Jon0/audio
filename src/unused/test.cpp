/*
 * test.cpp
 *
 *  Created on: Jun 12, 2012
 *      Author: remnanjona
 */

#define wwidth 800
#define wheight 600

#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <sys/time.h>
#include "Display.h"
#include "Scope.h"
#include "Playback.h"
#include "../process/Process.h"
#include "../buffer/TestBuffer.h"
#include "../buffer/WavBuffer.h"
#include "../buffer/Random.h"
#include "../buffer/TestBuffer.h"
#include "../fft/fft.h"

using namespace std;

GLuint g_mainWnd;
source *b;
Display *disp;
Playback *player;
Process *pr = NULL;

static void *begin_playback(void *);
static void *func2(void *);
void Idle();
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void displayCallback();

int notmainold() {
	b = new Random(); //new WavBuffer("shost2.wav"); //new TestBuffer(); //
	disp = new Scope(b, wwidth, wheight);
	player = new Playback();

	srand( time(NULL) ); // create random buffer

	//glutInit(&argc, argv);	//
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(wwidth, wheight);
	g_mainWnd = glutCreateWindow("Audio_Player");

	glutIdleFunc (Idle);
	glutMouseFunc (Mouse);
	glutMotionFunc (Motion);
	glutKeyboardFunc (Keyboard);
	glutDisplayFunc (displayCallback);

	disp->init();

	// run
	glutMainLoop();

    return 0;
}

static void *begin_playback(void *arg) {
	//player->play(b->getBlockLength(), (short *)b->currentBlock());
	//player->playall(b);
	player->playTest();
	return 0;
}

static void *func2(void *arg) {
	pr = new Process(b);
	return 0;
}

void Idle() {
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y) {

}

void Motion(int x, int y) {

}

void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		pthread_t threadId;
		pthread_create(&threadId, NULL, begin_playback, NULL);
		cout << "PLAY" << endl;
		break;
	case 'b':
		//view_scale *= 0.5;
		break;
	case 'n':
		//view_scale *= 2;
		break;
	case 'f':
		//ft->DFT_naive_1()
		break;
	case 'p':
		pthread_t threadId2;
		pthread_create(&threadId2, NULL, func2, NULL);
		break;
	}
}

void displayCallback() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	disp->draw();
	glutSwapBuffers();
}

