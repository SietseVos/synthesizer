#include <portaudio.h>
#include <stdio.h>
#include <math.h>
#include "../include/sounds.h"

void set_data_params_triangle(paTestData *data)
{
    data->left_phase = data->right_phase = 0.0;
    data->time = 0;
    data->envelope = 0;
    data->attack = 0.01;
    data->attack_peak = 1;
    data->decay = 0.01;
    data->sustain = 0.9;
    data->sustain_time = 3;
    data->release = 0.1;
    data->mode = ATTACK;
}

/* This routine will be called by the PortAudio engine when audio is needed.
 * It may called at interrupt level on some machines so don't do anything
 * that could mess up the system like calling malloc() or free().
 */
int play_triangle(const void *inputBuffer, void *outputBuffer,
             unsigned long framesPerBuffer,
             const PaStreamCallbackTimeInfo *timeInfo,
             PaStreamCallbackFlags statusFlags,
             void *userData)
{
    /* Cast data passed through stream to our structure. */
    paTestData *data = (paTestData *)userData;
    float *out = (float *)outputBuffer;
    unsigned int i;
    (void)inputBuffer; /* Prevent unused variable warning. */

    for (i = 0; i < framesPerBuffer; i++)
    {
        if (data->left_phase < 0)
        {
            *out++ = data->right_phase * -1 * data->envelope; /* right */
            *out++ = data->left_phase * -1 * data->envelope;  /* left */
        }
        else
        {
            *out++ = data->left_phase * data->envelope;  /* left */
            *out++ = data->right_phase * data->envelope; /* right */
        }
        data->left_phase += 0.01f;
        if (data->left_phase >= 1.0f)
            data->left_phase -= 2.0f;
        data->right_phase += 0.03f;
        if (data->right_phase >= 1.0f)
            data->right_phase -= 2.0f;
    }
    // change envelope
    if (data->envelope < data->attack_peak && data->mode == ATTACK)
        data->envelope += data->attack;
    if (data->envelope >= data->attack_peak && data->mode == ATTACK)
        data->mode = DECAY;
    if (data->envelope > data->sustain && data->mode == DECAY)
        data->envelope -= data->decay;
    if (data->envelope <= data->sustain && data->mode == DECAY)
        data->mode = SUSTAIN;
    if (data->sustain_time > 0 && data->mode == SUSTAIN)
        data->sustain_time -= 0.01;
    if (data->sustain_time <= 0 && data->mode == SUSTAIN)
        data->mode = RELEASE;
    if (data->envelope > 0 && data->mode == RELEASE)
        data->envelope -= data->release;
    if (data->envelope < 0)
        data->envelope = 0;
    if (data->envelope > 1)
        data->envelope = 1;
    return 0;
}