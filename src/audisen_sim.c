#include "../include/ams.h"
#include "../include/define.h"
#include "../include/frame.h"
#include "stdio.h"

int main(int argc, char** argv) {

    s_song mySong;
    FILE* f;

    if (argc == 2) {
        if (endWith(argv[1], ".ams")) {
            mySong = readAMS(argv[1]);

            char* frmFileName = malloc(sizeof(char) * (strlen(argv[1]) + 1));
            strcpy(frmFileName, argv[1]);
            frmFileName[strlen(frmFileName) - 3] = 'f';
            frmFileName[strlen(frmFileName) - 2] = 'r';
            frmFileName[strlen(frmFileName) - 1] = 'm';
            frmFileName[strlen(frmFileName)] = '\0';

            f = fopen(frmFileName, "wb");

            free(frmFileName);
        } else if (endWith(argv[1], ".txt")) {
            char* amsFileName = malloc(sizeof(char) * (strlen(argv[1]) + 1));
            strcpy(amsFileName, argv[1]);
            amsFileName[strlen(amsFileName) - 3] = 'a';
            amsFileName[strlen(amsFileName) - 2] = 'm';
            amsFileName[strlen(amsFileName) - 1] = 's';
            amsFileName[strlen(amsFileName)] = '\0';

            createAMS(argv[1], amsFileName);

            mySong = readAMS(amsFileName);

            char* frmFileName = malloc(sizeof(char) * (strlen(argv[1]) + 1));
            strcpy(frmFileName, argv[1]);
            frmFileName[strlen(frmFileName) - 3] = 'f';
            frmFileName[strlen(frmFileName) - 2] = 'r';
            frmFileName[strlen(frmFileName) - 1] = 'm';
            frmFileName[strlen(frmFileName)] = '\0';

            f = fopen(frmFileName, "wb");

            free(amsFileName);
            free(frmFileName);
        } else {
            printf("Error: File is not an .ams or .amp file\n");
            return 1;
        }
    } else {
        mySong = readAMS("music/bohemian_rhapsody.ams");

        f = fopen("music/bohemian_rhapsody.frm", "wb");
    }


    char line[INIT_FRAME_MAX_SIZE];

    createInitFrame(mySong, line);
    fprintf(f, "%s", line);

    for (int i = 0; i < mySong.nTicks; i++) {
        createTickFrame(mySong.tickTab[i], line);
        fprintf(f, "%s", line);
    }

    return 0;
}
