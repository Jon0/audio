/*
 * Playback.h
 *
 *  Created on: Mar 11, 2013
 *      Author: remnanjona
 */

#ifndef PLAYBACK_H_
#define PLAYBACK_H_

#include <alsa/asoundlib.h>
#include "../playback//source.h"

namespace std {

class Playback {
	snd_pcm_uframes_t bufferSize;
	snd_pcm_t *_soundDevice;
	short *next;
	int lock;
	bool Init(const char *, int, int);
public:
	Playback();
	virtual ~Playback();

	int play(long length, short *buffer);
	int playnext(source *);
	int playall(source *);
	int playTest();
};

} /* namespace std */
#endif /* PLAYBACK_H_ */
