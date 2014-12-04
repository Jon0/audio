/*
 * ViewSpline.cpp
 *
 *  Created on: 30/08/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <string>
#include <GL/glut.h>
#include "AudioView.h"

namespace std {

AudioView::AudioView(): Ortho() {
	time = 0.0;
	play = false;
}

AudioView::~AudioView() {
	// TODO Auto-generated destructor stub
}

int AudioView::mouseClicked(int button, int state, int x, int y) {
	if (button == 2 && state) {
		message.clear();
		message += "click ";
		message += to_string(x);
		message += ", ";
		message += to_string(y);
		return 1;
	}
	return 0;
}

int AudioView::mouseDragged(int x, int y) {
	return 0;
}

void AudioView::display() {

}

void AudioView::messageSent(string s) {
	cout << s << endl;
	if (s == "play") {
		time = 0.0;
		play = true;
	}
}

} /* namespace std */
