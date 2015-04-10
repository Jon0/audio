#ifndef MIXER_H_
#define MIXER_H_

#include <alsa/asoundlib.h>

#include "../device/Source.h"

namespace device {

/**
 * mixes multiple audio sources and sends to
 * to audio device for playback
 */
class Mixer {
public:
	/**
	 * creates a single channel 44100 output
	 */
	Mixer();
	virtual ~Mixer();

	/**
	 * plays the given audio source
	 */
	int play(long length, short *buffer);
	int playnext(Source *);
	int playall(Source *);
	int playTest();

private:
	snd_pcm_uframes_t bufferSize;
	snd_pcm_t *_soundDevice;
	int lock;
	bool Init(const char *, int, int);

};

} /* namespace device */

#endif
