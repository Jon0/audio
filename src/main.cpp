
#include <cmath>
#include <iostream>
#include <thread>

#include <stdlib.h>
#include <GL/glut.h>

#include "window/MainWindow.h"
#include "device/Mixer.h"
#include "device/Source.h"
#include "buffer/FunctionBuffer.h"
#include "buffer/TestBuffer.h"
#include "score/Note.h"
#include "score/Structure.h"
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

	score::Structure s;
	for (int i = 0; i < 7; ++i) {
		cout << i << endl;
		score::Structure next(&s);
		s = next;
	}

	bool on = true;
	bool *oo = &on;
	function<short(long)> f = [&s](long t) -> short {
		return s.values[t % s.values.size()] * 1000.0;
	};


	thread t([f]() {	
		device::Source *b = new FunctionBuffer(f);
		device::Mixer *mixer = new device::Mixer();
		mixer->playall(b);
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



