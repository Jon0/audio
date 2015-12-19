
#include <cmath>
#include <iostream>
#include <thread>

#include <stdlib.h>
#include <GL/glut.h>


#include <device/Mixer.h>
#include <device/Source.h>
#include <buffer/FunctionBuffer.h>
#include <buffer/TestBuffer.h>
#include <score/Note.h>
#include <score/Structure.h>
#include <math/Grid.h>
#include <math/Scale.h>

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

	// score::Structure s;
	// for (int i = 0; i < 7; ++i) {
	// 	cout << i << endl;
	// 	score::Structure next(&s);
	// 	s = next;
	// }

	double amplitude = 1000.0;
	math::Grid g(48);

	function<short(long)> f = [&g, amplitude](long t) -> short {
		return g.get_sample(t) * amplitude;
	};

	device::Source *b = new FunctionBuffer(f);
	device::Mixer *mixer = new device::Mixer();
	mixer->playall(b);


	return EXIT_SUCCESS;
}



