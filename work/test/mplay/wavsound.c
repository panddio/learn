/*************************************************************************
	> File Name: wavsound.c
	> Author:
	> Mail:
	> Created Time: Fri 14 Oct 2016 02:26:26 PM CST
 ************************************************************************/

#include <tinyalsa/asoundlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

/*
 * Macro
 */
#define	ID_RIFF		0x46464952
#define	ID_WAVE		0x45564157
#define	ID_FMT		0x20746d66
#define	ID_DATA		0x61746164
#define FORMAT_PCM  1

/*
 * Struct
 */
struct riff_wave_header {
    uint32_t riff_id;
    uint32_t riff_sz;
    uint32_t wave_id;
};

struct chunk_header {
    uint32_t id;
    uint32_t sz;
};

struct chunk_fmt {
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
};

struct wav_header {
	uint32_t  riff_id;
	uint32_t  riff_sz;
	uint32_t  riff_fmt;
	uint32_t  fmt_id;
	uint32_t  fmt_sz;
	uint16_t  audio_format;
	uint16_t  num_channels;
	uint32_t  sample_rate;
	uint32_t  byte_rate;
	uint16_t  block_align;
	uint16_t  bits_per_sample;
	uint32_t  data_id;
	uint32_t  data_sz;
};

extern int close_flag;

void play_sample(char *filename, unsigned int device)
{
	char *buffer = NULL;
	int size, num_read;
	static FILE *file = NULL;
	struct pcm *pcm;
	struct pcm_config config;
	struct wav_header header;

	printf("entry: %s\n", __FUNCTION__);

	bzero(&config, sizeof(struct pcm_config));

	file = fopen(filename, "rb");
	if(!file) {
		printf("Unable to open file '%s'\n", filename);
		return;
	}

	fread(&header, sizeof(struct wav_header), 1, file);

	if((header.riff_id != ID_RIFF) || (header.riff_fmt != ID_WAVE) ||
	   (header.fmt_id != ID_FMT) || (header.audio_format != FORMAT_PCM) ||
	   (header.fmt_sz != 16)) {
		printf("Error: '%s' is not a PCM riff/wave file\n", filename);
		fclose(file);
		return;
	}

	config.channels = header.num_channels;
	config.rate = header.sample_rate;
	config.period_size = 1024;
	config.period_count = 4;

	if(header.bits_per_sample == 32)
		config.format = PCM_FORMAT_S32_LE;
	else if(header.bits_per_sample == 16)
		config.format = PCM_FORMAT_S16_LE;
	config.start_threshold = 0;
	config.stop_threshold = 0;
	config.silence_threshold = 0;

	pcm = pcm_open(0, device, PCM_OUT, &config);
	if(!pcm || !pcm_is_ready(pcm)) {
		printf("Unable to open PCM device %u (%s)\n", device, pcm_get_error(pcm));
		return;
	}

	size = pcm_frames_to_bytes(pcm, pcm_get_buffer_size(pcm));
	buffer = malloc(size);
	if(!buffer) {
		printf("Unable to allocate %d bytes\n", size);
		pcm_close(pcm);
		return;
	}

	printf("Playing sample: %u ch, %u hz, %u bit\n", header.num_channels,
			header.sample_rate, header.bits_per_sample);

	do {
		num_read = fread(buffer, 1, size, file);
		if(num_read > 0) {
			if(pcm_write(pcm, buffer, num_read)) {
				printf("Error playing sample\n");
				break;
			}
		}
	} while(num_read > 0);

	printf("pcm_write over...\n");
	fclose(file);
	free(buffer);
	pcm_close(pcm);
}
