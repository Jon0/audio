#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#include "Mixer.h"

namespace device {

Mixer::Mixer() {
	lock = 0;
	if (!Init("plughw:0,0", 44100, 1)) {

		// revert to alsa default
		std::cout << "trying default" << std::endl;
		Init("default", 44100, 1);
	}
}

Mixer::~Mixer() {
	snd_pcm_drain(_soundDevice);
	snd_pcm_close(_soundDevice);
}

/*
 * Initialise device
 */
bool Mixer::Init(const char *name, int desiredRate, int channels) {
	int err;
	snd_pcm_hw_params_t *hw_params;

	if (name == NULL) {
		// Try to open the default device
		err = snd_pcm_open( &_soundDevice, "plughw:0,0", SND_PCM_STREAM_PLAYBACK, SND_PCM_NONBLOCK );
	}
	else {
		// Open the device we were told to open.
		err = snd_pcm_open (&_soundDevice, name, SND_PCM_STREAM_PLAYBACK, SND_PCM_NONBLOCK );
	}

	// Check for error on open.
	if (err < 0) {
		std::cout << "Init: cannot open audio device " << " (" << snd_strerror (err) << ")" << std::endl;
		return false;
	}
	else {
		std::cout << "Audio device opened successfully." << std::endl;
	}

	// Allocate the hardware parameter structure.
	if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
		std::cout << "Init: cannot allocate hardware parameter structure (" << snd_strerror(err) << ")" << std::endl;
		return false;
	}

	if ((err = snd_pcm_hw_params_any (_soundDevice, hw_params)) < 0) {
		std::cout << "Init: cannot initialize hardware parameter structure (" << snd_strerror(err) << ")" << std::endl;
		return false;
	}

	// Enable resampling.
	unsigned int resample = 1;
	err = snd_pcm_hw_params_set_rate_resample(_soundDevice, hw_params, resample);
	if (err < 0) {
		std::cout << "Init: Resampling setup failed for playback: " << snd_strerror(err) << std::endl;
		return err;
	}

	// Set access to RW interleaved.
	if ((err = snd_pcm_hw_params_set_access (_soundDevice, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		std::cout << "Init: cannot set access type (" << snd_strerror (err) << ")" << std::endl;
		return false;
	}

	if ((err = snd_pcm_hw_params_set_format (_soundDevice, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
		std::cout << "Init: cannot set sample format (" << snd_strerror (err) << ")" << std::endl;
		return false;
	}

	// Set channels to stereo (2).
	if ((err = snd_pcm_hw_params_set_channels (_soundDevice, hw_params, channels)) < 0) {
		std::cout << "Init: cannot set channel count (" << snd_strerror (err) << ")" << std::endl;
		return false;
	}

	// Set sample rate.
	//unsigned int desiredRate = 44100;
	unsigned int actualRate = desiredRate;
	if ((err = snd_pcm_hw_params_set_rate_near (_soundDevice, hw_params, &actualRate, 0)) < 0) {
		std::cout << "Init: cannot set sample rate to " << desiredRate << ". (" << snd_strerror (err) << ")" << std::endl;
		return false;
	}
	if(actualRate != desiredRate) {
		std::cout << "Init: sample rate does not match requested rate. (" << desiredRate << " requested, " << actualRate << " acquired)" << std::endl;
	}

	// Apply the hardware parameters that we've set.
	if ((err = snd_pcm_hw_params (_soundDevice, hw_params)) < 0) {
		std::cout << "Init: cannot set parameters (" << snd_strerror (err) << ")" << std::endl;
		return false;
	}
	else {
		std::cout << "Audio device parameters have been set successfully." << std::endl;
	}

	// Get the buffer size.
	snd_pcm_hw_params_get_buffer_size( hw_params, &bufferSize );
	// If we were going to do more with our sound device we would want to store
	// the buffer size so we know how much data we will need to fill it with.
	std::cout << "Init: Buffer size = " << bufferSize << " frames." << std::endl;

	// Display the bit size of samples.
	std::cout << "Init: Significant bits for linear samples = " << snd_pcm_hw_params_get_sbits(hw_params) << std::endl;

	// Free the hardware parameters now that we're done with them.
	snd_pcm_hw_params_free (hw_params);

	// Set non-blocking
	if ((err = snd_pcm_nonblock(_soundDevice, SND_PCM_NONBLOCK)) < 0) {
		std::cout << "Init: cannot set non-block mode (" << snd_strerror (err) << ")" << std::endl;
		return false;
	}
	else {
		std::cout << "Non-blocking mode set." << std::endl;
	}

	// Prepare interface for use.
	if ((err = snd_pcm_prepare(_soundDevice)) < 0) {
		std::cout << "Init: cannot prepare audio interface for use ("<< snd_strerror(err) << ")" << std::endl;
		return false;
	} else {
		std::cout << "Audio device has been prepared for use." << std::endl;
	}

	return true;
}

int Mixer::play(long length, short *buffer) {
	if (lock > 0) return 1;
	lock++;
	int blocksize = 1024*2;
	int divide = length / blocksize;
	snd_pcm_sframes_t written = 0;
	for (int i = 0; i < divide;) {
		snd_pcm_wait(_soundDevice, -1);
		snd_pcm_sframes_t msg = snd_pcm_writei(_soundDevice, &buffer[i * blocksize], blocksize/2 - written);
		if (msg < 0) {
			std::cout << "playback failed: " << snd_strerror(msg) << std::endl;
		} else if (written + msg < blocksize/2) {
			std::cout << "incomplete write: " << msg << std::endl;
			written += msg;
		} else {
			++i;
			written = 0;
		}

	}

	snd_pcm_prepare (_soundDevice);
	// cout << "done" << endl;
	lock--;
	return 0;
}

int Mixer::playnext(device::Source *b) {
	return play(b->available(), (short *)b->currentBlock());
}

int Mixer::playall(device::Source *b) {
	snd_pcm_uframes_t available = 0;
	short *next = 0;

	while (1) {
		if (next) {
			b->setStart();	// update frame start time
			snd_pcm_wait(_soundDevice, -1);
			snd_pcm_sframes_t msg = snd_pcm_writei(_soundDevice, next, available);
			if (msg < 0) {
				std::cout << "playback failed: " << snd_strerror(msg) << std::endl;
				break;
			} else if (msg < available) {
				// incomplete write
				available -= msg;
				next += msg;
			} else {
				available = b->available();
				next = (short *)b->next();
			}
		}
		else {
			available = b->available();
			next = (short *)b->next();
		}
	}
	return 0;
}

int Mixer::playTest() {
	int written = 0;
	int blocksize = 1024;
	short *block = new short [blocksize];
	float f = 0;
	while (1) {
		snd_pcm_wait(_soundDevice, -1);
		snd_pcm_sframes_t msg = snd_pcm_writei(_soundDevice, &block[written], blocksize - written );
		if (msg < 0) {
			std::cout << "playback failed: " << snd_strerror(msg) << std::endl;
		} else if (written + msg < blocksize) { //blocksize/2 for stereo
			std::cout << "incomplete write: " << msg << std::endl;
			written += msg;
		} else {
			written = 0;
			for (int i = 0; i < blocksize; ++i) {
				block[i] = sin(f) * 1024*16;
				f += 0.1;
			}
		}
	}
}

} /* namespace device */
