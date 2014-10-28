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
#include "buffer/FunctionBuffer.h"
#include "buffer/TestBuffer.h"
#include "math/Scale.h"

using namespace std;

int main(int argc, char *argv[]) {
	srand( time( NULL ) );
	// glutInit(&argc, argv);
	//new MainWindow(800, 600);
	//source *b = new TestBuffer();

	//Scale s; s.get(t);

	function<short(long)> f = [&](long t) -> short {
		long td = t / 3;

		short s1 = (td*(td >> 5 | td >> 8))>>(td>>16);
		short s2 =  6 * (td|td>>7|td>>9)+
					4 * (td&td>>13|td>>9)+
					2 * ((td+64)|td>>27|td>>9);

		short s3 = (td>>7|td|td>>6)*6+4*(td&td>>13|td>>6);



		short s4 = (td|td>>7|(td>>6 % 3)) + ((td+64)|td>>27|(td>>9 % 3));

		short s5 =  ((td>>5|td|td>>9)*6^4*(td&td>>11|td>>9))>>((td>>11)*(td>>13) % 3);

		return (s5 & 0xff) * 100;
	};

	source *b = new FunctionBuffer(f);
	Playback *play = new Playback();
	play->playall(b);


	return EXIT_SUCCESS;
}



