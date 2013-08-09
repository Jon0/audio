/*
 * Scope.cpp
 *
 *  Created on: 3/05/2013
 *      Author: remnanjona
 */

#include <stdlib.h>
#include <sys/time.h>
#include <GL/glut.h>
#include "Scope.h"

namespace std {

Scope::Scope(buffer *buffer, int w, int h) {
	b = buffer;
	startTime = -1;
	view_scale = 1.0;
	width = w;
	height = h;
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

void Scope::start() {
	timeval timeNow;
	gettimeofday(&timeNow, NULL);
	startTime = (timeNow.tv_sec * 1000) + (timeNow.tv_usec / 1000);
}

void Scope::draw() {
	long pass = 0;
	if (startTime > 0) {
		timeval timeNow;
		gettimeofday(&timeNow, NULL);
		pass = (timeNow.tv_sec * 1000) + (timeNow.tv_usec / 1000) - startTime;
	}

	// 44100 in one sec
	// 44.1 in millisec
	float m = pass*44.1*2;

	glLoadIdentity();
	gluLookAt((float)m/60, 0.0, 100.0*view_scale, (float)m/60, 0.0, 0.0, 0.0, 1.0, 0.0);

	long g_numPoints = b->getLength();
	short *g_values = b->getData();

	glColor3f(0.95f, 0.207, 0.031f);
	for (int i = m; i < m+4000 && i < g_numPoints; ++i) {
		glColor3f(0.95f, 0.207, 0.031f);
		glBegin(GL_POINTS);
		glVertex3f((float)i/60-24*view_scale, (float)g_values[i]/5000, 0);
		glEnd();
		glColor3f(0.15f, 0.203, 0.081f);
		glBegin(GL_LINES);
		glVertex3f((float)i/60-24*view_scale, (float)g_values[i]/5000, 0);
		glVertex3f((float)(i+1)/60-24*view_scale, (float)g_values[i+1]/5000, 0);
		glEnd();
	}
}

Scope::~Scope() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
