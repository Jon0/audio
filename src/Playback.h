/*
 * Playback.h
 *
 *  Created on: Mar 11, 2013
 *      Author: remnanjona
 */

#ifndef PLAYBACK_H_
#define PLAYBACK_H_

#include <alsa/asoundlib.h>
#include "buffer.h"

namespace std {

class Playback {
	snd_pcm_uframes_t bufferSize;
	snd_pcm_t * _soundDevice;
	int lock;
	bool Init(const char *);
public:
	Playback();
	int play(long length, short *buffer);
	int play(buffer *);
	virtual ~Playback();
};

} /* namespace std */
#endif /* PLAYBACK_H_ */
