#include <stdlib.h>
#include <GL/glut.h>

#include "window/MainWindow.h"
#include "playback/Playback.h"
#include "playback/source.h"
#include "buffer/FunctionBuffer.h"
#include "buffer/TestBuffer.h"
#include "math/Note.h"
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

	// TODO: visualisation
	// glutInit(&argc, argv);
	//new MainWindow(800, 600);
	//source *b = new TestBuffer();
	//Scale s; s.get(t);

	vector<math::Note> ns;
	int c1 = rand(), c2 = rand();
	for (int i = 0; i < 120; ++i) {
		int c3 = c1 + c2;
		c1 = c2;
		c2 = c3;
		double f = (100.0 + (c3 % 10) * 50.0);
		ns.push_back({f});
	}

	function<short(long)> f = [ns](long t) -> short {
		short r = 0;
		int ind = static_cast<int>(t / 10000.0) % ns.size();
		r = ns[ind].get(t);
		return r;
	};

	source *b = new FunctionBuffer(f);
	Playback *play = new Playback();
	play->playall(b);


	return EXIT_SUCCESS;
}



