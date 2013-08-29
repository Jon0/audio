/*
 * Pulse.cpp
 *
 *  Created on: 29/08/2013
 *      Author: remnanjona
 */

#include <stdio.h>
#include <pulse/error.h>
#include "Pulse.h"

namespace std {

Pulse::Pulse(const char *name) {
	pa_sample_spec ss;
	ss.format = PA_SAMPLE_S16NE;
	ss.channels = 2;
	ss.rate = 44100;
	s = pa_simple_new(NULL,               // Use the default server.
						name,           // Our application's name.
						PA_STREAM_PLAYBACK,
						NULL,               // Use the default device.
						"Test",            // Description of our stream.
						&ss,                // Our sample format.
						NULL,               // Use default channel map
						NULL,               // Use default buffering attributes.
						NULL               // Ignore error code.
	                  	  );


	int error = 0;
	pa_usec_t latency = pa_simple_get_latency(s, &error);
	//if (latency == (pa_usec_t) -1) {
	//	printf(": pa_simple_get_latency() failed: %s\n", pa_strerror(error));
	//}

	//fprintf(stderr, "%0.0f usec \r", (float)latency);
}

Pulse::~Pulse() {
	pa_simple_free(s);
}

} /* namespace std */
