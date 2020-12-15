#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "MIDITable.h"
#include "steppaMIDI.h"

// Output file name
#define FILE_NAME "testFile.txt"

// Arguments:
// 1. - u for USB, k for keyboard, f for file
// 2. - filename
int main(int argc, char **argv) {
    int file_desc = open(FILE_NAME, O_RDWR);

    if (file_desc < 0) {
        printf("Error, %s not opened\n", FILE_NAME);
        return EXIT_FAILURE;
    }

    if (argc == 1 || strcmp(argv[1], "u") == 0) {
        // Read from USB
        snd_rawmidi_t *midiIn = NULL;
        if (rawmidiInit(midiIn)) {
            char buffer[2];
            if (getRawmidiCommand(buffer, midiIn)) {
                // Send to file
                int ret_val = write(file_desc, buffer, 2);

                if (ret_val == 0) {
                    printf("Error writing to file\n");
                    close(file_desc);
                    return EXIT_FAILURE;
                }
            }
            rawmidiClose(midiIn);
        }

    } else if (strcmp(argv[1], "f") == 0 && argc > 2) {
        // Read from file
        midiFile = fopen(argv[2], "rb");
        if (midiFile == NULL) {
            fprintf(stderr, "Error while opening file %s\n", argv[1]);
            return EXIT_FAILURE;
        }

        readMidiData(&midiData);

        fclose(midiFile);
        freeMidiData(&midiData);

    } else if (strcmp(argv[1], "k") == 0) {
        // Read from keyboard
        int ret_val;
        char input;
        int octave;

        printf("Choose octave [1-7]: ");
        scanf("%d", &octave);
        getch(); //da pokupi enter

        printf("Start playing notes\n");

        while (1) {
            input = getch();

            switch (input) {
            //donji red
            case 'a':
                input = (char)C[octave].MIDINumber;
                break;
            case 's':
                input = (char)D[octave].MIDINumber;
                break;
            case 'd':
                input = (char)E[octave].MIDINumber;
                break;
            case 'f':
                input = (char)F[octave].MIDINumber;
                break;
            case 'g':
                input = (char)G[octave].MIDINumber;
                break;
            case 'h':
                input = (char)A[octave].MIDINumber;
                break;
            case 'j':
                input = (char)B[octave].MIDINumber;
                break;

            //gornji red
            case 'w':
                input = (char)M[5 * (octave - 1)].MIDINumber;
                break;
            case 'e':
                input = (char)M[5 * (octave - 1) + 1].MIDINumber;
                break;
            case 't':
                input = (char)M[5 * (octave - 1) + 2].MIDINumber;
                break;
            case 'y':
                input = (char)M[5 * (octave - 1) + 3].MIDINumber;
                break;
            case 'u':
                input = (char)M[5 * (octave - 1) + 4].MIDINumber;
                break;

            default:
                continue;
            }

            if (input == 'q') {
                close(file_desc);
                break;
            }

            ret_val = write(file_desc, &input, 1);

            if (ret_val == 0) {
                printf("Error writing to file\n");
                close(file_desc);
                return 2;
            }
        }

    } else {
        printf("Invalid arguments!\n");
        printf("Use: steppatron [MODE] [FILENAME]\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}