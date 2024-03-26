#include "../include/usb.h"
#include "../include/ams.h"
#include "../include/define.h"
#include "../include/frame.h"
#include "../include/amp.h"

#include <unistd.h>

int main(int argc, char** argv) {
    FT_HANDLE handle = initUSB();

    s_song* mySong = calloc(4, sizeof(s_song));
    int nbSong = 0;

    if (argc == 2) {
        if (endWith(argv[1], ".txt")) {
            char* amsFileName = malloc(sizeof(char) * (strlen(argv[1]) + 1));
            strcpy(amsFileName, argv[1]);
            amsFileName[strlen(amsFileName) - 3] = 'a';
            amsFileName[strlen(amsFileName) - 2] = 'm';
            amsFileName[strlen(amsFileName) - 1] = 's';
            amsFileName[strlen(amsFileName)] = '\0';

            createAMS(argv[1], amsFileName);

            mySong[0] = readAMS(amsFileName);
            nbSong = 1;
            free(amsFileName);
        } else if (endWith(argv[1], ".ams")) {
            mySong[0] = readAMS(argv[1]);
            nbSong = 1;
        } else if (endWith(argv[1], ".amp")) {
            FILE* file = initAMP(argv[1]);
            for (int i = 0; i < 4; i++) {
                char song_filename[MAX_SIZE_TITLE];
                readAMP(file, song_filename);

                char folder[100];
                _splitpath_s(argv[1], NULL, 0, folder, sizeof(folder), NULL , 0, NULL, 0);

                // add folder
                char song_filename_with_folder[MAX_SIZE_TITLE];
                strcpy(song_filename_with_folder, folder);
                strcat(song_filename_with_folder, song_filename);

                if (!exists(song_filename_with_folder)) {
                    // check for the .txt file
                    char txt_filename[100];
                    strcpy(txt_filename, song_filename_with_folder);
                    txt_filename[strlen(txt_filename) - 4] = '\0';
                    strcat(txt_filename, ".txt");

                    if (exists(txt_filename)) {
                        createAMS(txt_filename, song_filename_with_folder);
                    } else {
                        printf("Error: File not found\n");
                        free(mySong);
                        return 1;
                    }
                }

                printf("%s\n", song_filename_with_folder);
                mySong[i] = readAMS(song_filename_with_folder);
                nbSong++;
                if (feof(file)) {
                    break;
                }
            }
        } else {
            printf("Error: File is not an .ams or .txt file\n");
            free(mySong);
            return 1;
        }
    } else {
        mySong[0] = readAMS("bohemian_rhapsody.ams");
        nbSong = 1;
    }

    if (mySong[0].nTicks == 0) {
        printf("Error: exit, music do not have any tick\n");
        free(mySong);
        return 1;
    }

    char temp[INIT_FRAME_MAX_SIZE];

    printf("nbSong: %d\n", nbSong);

    for (int i = 0; i < nbSong; i++) {
        printf("%d, Song : %s\n", i, mySong[i].title);

        char* toSend = calloc(INIT_FRAME_MAX_SIZE + mySong[i].nTicks * TICK_FRAME_SIZE, sizeof(char));

        createInitFrame(mySong[i], temp);

        strcpy(toSend, temp);
        // writeUSB(temp, handle);

        for (int j = 0; j < mySong[i].nTicks; j++) {
            createTickFrame(mySong[i].tickTab[j], temp);
            // writeUSB(temp, handle);
            strcat(toSend, temp);
        }

        writeUSB(toSend, handle);

        free(toSend);

        sleep(2);
    }

    closeUSB(handle);

    free(mySong);

    return 0;
}
