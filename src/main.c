#include <portaudio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sounds.h"

#define SAMPLE_RATE (44100)
#define NUM_SECONDS 5

enum sounds {
    SAW,
    SQUARE,
    TRIANGLE
};

paTestData data;

int main(int argc, char** argv)
{
    // Input handling

    const char saw[] = "saw";
    const char square[] = "square";
    const char triangle[] = "triangle";
    int selected_sound;
    if (argc < 2) {
        printf("Specify sound to play: %s, %s, %s.\n", saw, square, triangle);
        exit(1);
    }
    if (strcmp(argv[1], "saw") == 0)
        selected_sound = SAW;
    else if (strcmp(argv[1], "square") == 0)
        selected_sound = SQUARE;
    else if (strcmp(argv[1], "triangle") == 0)
        selected_sound = TRIANGLE;
    else {
        printf("%s doesnt equal any valid input.\n", argv[1]);
        printf("Specify sound to play: %s, %s, %s.\n", saw, square, triangle);
        exit(1);
        
    }

    // Initialization
    PaError err = Pa_Initialize();
    if( err != paNoError ) goto error;
    
    PaStream *stream;
    /* Open an audio I/O stream. */
    switch (selected_sound) {
        case SAW:
            set_data_params_saw(&data);
            err = Pa_OpenDefaultStream( &stream,
                0,
                2,
                paFloat32,
                SAMPLE_RATE,
                256,
                play_saw,
                &data );
            break;
        case SQUARE:
            set_data_params_square(&data);
            err = Pa_OpenDefaultStream( &stream,
                0,
                2,
                paFloat32,
                SAMPLE_RATE,
                256,
                play_square,
                &data );
            break;
        case TRIANGLE:
            set_data_params_triangle(&data);
            err = Pa_OpenDefaultStream( &stream,
                0,
                2,
                paFloat32,
                SAMPLE_RATE,
                256,
                play_triangle,
                &data );
            break;
        default:
        set_data_params_saw(&data);
        err = Pa_OpenDefaultStream( &stream,
            0,
            2,
            paFloat32,
            SAMPLE_RATE,
            256,
            play_saw,
            &data );
        break;
    }
    if( err != paNoError ) goto error;
    
    //Start streaming
    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error;

    /* Sleep for several seconds. */
    Pa_Sleep(NUM_SECONDS*1000);

    //Stop the stream
    err = Pa_StopStream( stream );
    if( err != paNoError ) goto error;

    // Close stream to clean up recources
    err = Pa_CloseStream( stream );
    if( err != paNoError ) goto error;

    //Stop PortAudio
    err = Pa_Terminate();
    if( err != paNoError )
    printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );

error:
    Pa_Terminate();
    fprintf( stderr, "An error occurred while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    return err;

}