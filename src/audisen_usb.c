#include "../include/usb.h"
#include "../include/ams.h"
#include "../include/define.h"
#include "../include/frame.h"

int main(int argc, char** argv) {
    FT_HANDLE handle = initUSB();

    s_song mySong;

    if (argc == 2) {
        if (endWith(argv[1], ".txt")) {
            char* amsFileName = malloc(sizeof(char) * (strlen(argv[1]) + 1));
            strcpy(amsFileName, argv[1]);
            amsFileName[strlen(amsFileName) - 3] = 'a';
            amsFileName[strlen(amsFileName) - 2] = 'm';
            amsFileName[strlen(amsFileName) - 1] = 's';
            amsFileName[strlen(amsFileName)] = '\0';

            createAMS(argv[1], amsFileName);

            mySong = readAMS(amsFileName);
        } else if (endWith(argv[1], ".ams")) {
            mySong = readAMS(argv[1]);
        } else {
            printf("Error: File is not an .ams or .txt file\n");
            return 1;
        }
    } else {
        mySong = readAMS("bohemian_rhapsody.ams");
    }

    char temp[INIT_FRAME_MAX_SIZE];

    char* toSend = malloc(sizeof(char) * (INIT_FRAME_MAX_SIZE + mySong.nTicks * TICK_FRAME_SIZE));

    createInitFrame(mySong, temp);

    strcpy(toSend, temp);
    // writeUSB(temp, handle);

    for (int i = 0; i < mySong.nTicks; i++) {
        createTickFrame(mySong.tickTab[i], temp);
        // writeUSB(temp, handle);
        strcat(toSend, temp);
    }

    writeUSB(toSend, handle);
    closeUSB(handle);

    free(toSend);
    return 0;
}