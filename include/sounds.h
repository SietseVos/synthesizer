#ifndef SOUDNS_H
#define SOUNDS_H

/*
contains variables for sound output(left_pahse and right_phase)
and adsr components, init at 0
time: determines the age of the sound, init at 0
envelope: starting lvl of sound, recommand to init at 0
attack: attack speed, init between 0 and 1
attack_peak: maximum volume after attack, init between 0 and 1,
decay: decay speed from attack peak to sustain, init between 0 and 1,
sustain: sustain lvl, init between 0 and 1,
sustain_time: used to emutale a key pressed, time may vary depending
on buffer and sample rate settings
release: release speed from sustain to 0, init between 0 and 1,
mode: init at ATTACK
*/
typedef struct
{
    float   left_phase;
    float   right_phase;
    float   time;
    float   envelope;
    float   attack;
    float   attack_peak;
    float   decay;
    float   sustain;
    float   sustain_time;
    float   release;
    int     mode;
}   
paTestData;

enum adsr_mode {
    ATTACK,
    DECAY,
    SUSTAIN,
    RELEASE
};


int play_saw( const void *inputBuffer, void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData );
void set_data_params_saw(paTestData* data);

int play_square( const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData );
void set_data_params_square(paTestData* data);

int play_triangle( const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData );
void set_data_params_triangle(paTestData* data);

#endif