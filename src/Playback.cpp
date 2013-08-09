/*
 * Playback.cpp
 *
 *  Created on: Mar 11, 2013
 *      Author: remnanjona
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Playback.h"

namespace std {

Playback::Playback() {
	lock = 0;
	if (!Init("hw:0,0")) {
		cout << "trying default" << endl;
		Init("default");
	}
}

bool Playback::Init(const char *name)
{
	int err;
	snd_pcm_hw_params_t *hw_params;

	if( name == NULL )
	{
		// Try to open the default device
		err = snd_pcm_open( &_soundDevice, "plughw:0,0", SND_PCM_STREAM_PLAYBACK, SND_PCM_NONBLOCK );
	}
	else
	{
		// Open the device we were told to open.
		err = snd_pcm_open (&_soundDevice, name, SND_PCM_STREAM_PLAYBACK, SND_PCM_NONBLOCK );
	}

	// Check for error on open.
	if( err < 0 )
	{
		cout << "Init: cannot open audio device " << " (" << snd_strerror (err) << ")" << endl;
		return false;
	}
	else
	{
		cout << "Audio device opened successfully." << endl;
	}

	// Allocate the hardware parameter structure.
	if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0)
	{
		cout << "Init: cannot allocate hardware parameter structure (" << snd_strerror(err) << ")" << endl;
		return false;
	}

	if ((err = snd_pcm_hw_params_any (_soundDevice, hw_params)) < 0)
	{
		cout << "Init: cannot initialize hardware parameter structure (" << snd_strerror(err) << ")" << endl;
		return false;
	}

	// Enable resampling.
	unsigned int resample = 1;
	err = snd_pcm_hw_params_set_rate_resample(_soundDevice, hw_params, resample);
	if (err < 0)
	{
		cout << "Init: Resampling setup failed for playback: " << snd_strerror(err) <<
				endl;
		return err;
	}

	// Set access to RW interleaved.
	if ((err = snd_pcm_hw_params_set_access (_soundDevice, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
	{
		cout << "Init: cannot set access type (" << snd_strerror (err) << ")" << endl;
		return false;
	}

	if ((err = snd_pcm_hw_params_set_format (_soundDevice, hw_params, SND_PCM_FORMAT_S16_LE)) < 0)
	{
		cout << "Init: cannot set sample format (" << snd_strerror (err) << ")" << endl;
		return false;
	}

	// Set channels to stereo (2).
	if ((err = snd_pcm_hw_params_set_channels (_soundDevice, hw_params, 2)) < 0)
	{
		cout << "Init: cannot set channel count (" << snd_strerror (err) << ")" << endl;
		return false;
	}

	// Set sample rate.
	unsigned int desiredRate = 44100;
	unsigned int actualRate = desiredRate;
	if ((err = snd_pcm_hw_params_set_rate_near (_soundDevice, hw_params, &actualRate, 0)) < 0)
	{
		cout << "Init: cannot set sample rate to " << desiredRate << ". (" << snd_strerror (err) << ")" << endl;
		return false;
	}
	if( actualRate != desiredRate )
	{
		cout << "Init: sample rate does not match requested rate. (" << desiredRate << " requested, " << actualRate << " acquired)" << endl;
	}

	// Apply the hardware parameters that we've set.
	if ((err = snd_pcm_hw_params (_soundDevice, hw_params)) < 0)
	{
		cout << "Init: cannot set parameters (" << snd_strerror (err) << ")" << endl;
		return false;
	}
	else
	{
		cout << "Audio device parameters have been set successfully." << endl;
	}

	// Get the buffer size.
	snd_pcm_hw_params_get_buffer_size( hw_params, &bufferSize );
	// If we were going to do more with our sound device we would want to store
	// the buffer size so we know how much data we will need to fill it with.
	cout << "Init: Buffer size = " << bufferSize << " frames." << endl;

	// Display the bit size of samples.
	cout << "Init: Significant bits for linear samples = " << snd_pcm_hw_params_get_sbits(hw_params) << endl;

	// Free the hardware parameters now that we're done with them.
	snd_pcm_hw_params_free (hw_params);

	// Prepare interface for use.
	if ((err = snd_pcm_prepare (_soundDevice)) < 0)
	{
		cout << "Init: cannot prepare audio interface for use (" << snd_strerror (err) << ")" << endl;
		return false;
	}
	else
	{
		cout << "Audio device has been prepared for use." << endl;
	}

	return true;
}

int Playback::play(long length, short *buffer) {
	if (lock > 0) return 1;
	lock++;
	int blocksize = 1024*4;
	int divide = length / blocksize;
	for (int i = 0; i < divide;) {
		int g;
		if ((g = snd_pcm_avail_update(_soundDevice)) < blocksize) {
			usleep(10000);
			continue;
		}

		//cout << i << endl;
		snd_pcm_sframes_t written = snd_pcm_writei(_soundDevice, &buffer[i * blocksize], blocksize/2);
		if (written < 0) {
			cout << "playback failed: " << snd_strerror(written) << endl;
		} else if (written < blocksize/2) {
			cout << "incomplete write: " << written << endl;
		} else {
			++i;
		}

	}

	snd_pcm_prepare (_soundDevice);
	cout << "done" << endl;
	lock--;
	return 0;
}

int Playback::play(buffer *b) {
	return play(b->getLength(), b->getData());
}

Playback::~Playback() {
	snd_pcm_drain(_soundDevice);
	snd_pcm_close(_soundDevice);
}

} /* namespace std */
