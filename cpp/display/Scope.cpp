/*
 * Scope.cpp
 *
 *  Created on: 3/05/2013
 *      Author: remnanjona
 */

#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <GL/glut.h>
#include "Scope.h"

namespace std {

Scope::Scope(source *buffer, int w, int h) {
	b = buffer;
	g_values_pre = NULL;

	// view dimensions
	view_scale = 1.0;
	width = w;
	height = h;

	// 44100 cycles in one sec == 44.1 in millisec
	format_hz = 44.1;

}


void Scope::init() {

	// camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, (double) width / (double) height, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// gl state
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_CULL_FACE);
	glPointSize(4.0);

}

void Scope::draw() {
	long pass = 0;
	int g_numPoints = b->available();
	short *g_values = (short *)b->currentBlock();

	if (b->startTime() > 0) {
		timeval timeNow;
		gettimeofday(&timeNow, NULL);
		pass = (timeNow.tv_sec * 1000) + (timeNow.tv_usec / 1000) - b->startTime();
	}

	if (g_values) {
		int perpix = 1000;
		float m = (pass*format_hz*2);

		glLoadIdentity();
		gluLookAt(0.0, 0.0, 100.0*view_scale, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

		glColor3f(0.95f, 0.207, 0.031f);
		for (int i = (int)m; i < ((int)m % g_numPoints) + 24000 && i < g_numPoints;) {
			int total = 0;
			for (int j = 0; j < perpix; ++j) {
				total += abs( g_values[i] );
				++i;
			}

			//glColor3f(0.95f, 0.207, 0.031f);
			//glBegin(GL_POINTS);
			//glVertex3f((float) i / 60 - 24 * view_scale, (float) total / 20000, 0);
			//glEnd();

			glColor3f(0.15f, 0.903, 0.081f);
			glBegin(GL_LINES);
			glVertex3f((float) (i - m) / 1000, (float) total / 400000, 0);
			glVertex3f((float) (i - m) / 1000, (float) -total / 400000, 0);
			glEnd();

			//glColor3f(0.15f, 0.903, 0.081f);
			//glBegin(GL_LINES);
			//glVertex3f((float) i / 60 - 24 * view_scale, (float) g_values[i] / 5000, 0);
			//glVertex3f((float) (i + 1) / 60 - 24 * view_scale, (float) g_values[i + 1] / 5000, 0);
			//glEnd();
		}
	}

	g_values_pre = g_values;
}

Scope::~Scope() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
