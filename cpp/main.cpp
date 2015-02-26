
#include <cmath>
#include <iostream>
#include <thread>

#include <stdlib.h>
#include <GL/glut.h>

#include "window/MainWindow.h"
#include "playback/Playback.h"
#include "playback/source.h"
#include "buffer/FunctionBuffer.h"
#include "buffer/TestBuffer.h"
#include "score/Note.h"
#include "math/Scale.h"

using namespace std;

/*
 * some other interesting patterns:
 *
 * short s1 = (td*(td >> 5 | td >> 8))>>(td>>16);
 * short s1 =  6 * (td|td>>7|td>>9)+
 * 			4 * (td&td>>13|td>>9)+
 * 			2 * ((td+64)|td>>27|td>>9);
 * 
 * short s1 = (td>>7|td|td>>6)*6+4*(td&td>>13|td>>6);
 * 
 * short s1 = (td|td>>7|(td>>6 % 3)) + ((td+64)|td>>27|(td>>9 % 3));
 * 
 * short s1 =  ((td>>5|td|td>>9)*6^4*(td&td>>11|td>>9))>>((td>>11)*(td>>13) % 3);
*/
short example(long t) {
	// adjust sample rate
	long td = t / 3;

	short s1 =  (((td>>5|td|td>>9)*6^4*(td&td>>11|td>>9))>>((td>>11)*(td>>13) % 3))|(td>>(13-((td>>7)*(td>>23) % 13)));

	// 8 bit output with volume adjustment
	return (s1 & 0xff) * 200;
}

int main(int argc, char *argv[]) {
	srand( time( NULL ) );

	bool on = true;
	bool *oo = &on;
	function<short(long)> f = [oo](long t) -> short {
		short r = 0;
		if (*oo) {
			r = sin(t / 20.0f) * 500.0;
 		}
		return r;
	};


	thread t([f]() {	
		source *b = new FunctionBuffer(f);
		Playback *play = new Playback();
		play->playall(b);
	});


	while (true) {
		string s;
		getline(cin, s, ' ');
		cout << "here" << endl;
		on = !on;
	}


	t.join();
	return EXIT_SUCCESS;
}



