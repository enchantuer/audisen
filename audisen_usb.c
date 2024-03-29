#include "usb.h"
#include "ams.h"
#include "define.h"
#include "frame.h"
#include "amp.h"

#include <unistd.h>

// Send on USB using UART songs
int main(int argc, char** argv) {
    // Init USB connection
    FT_HANDLE handle = initUSB();

    s_song* mySong = calloc(4, sizeof(s_song));
    int nbSong = 0;

    if (argc >= 2) {
        // Handle .txt file
        if (endWith(argv[1], ".txt")) {
            // Create .ams filename based on .txt filename
            char* amsFileName = malloc(sizeof(char) * (strlen(argv[1]) + 1));
            strcpy(amsFileName, argv[1]);
            amsFileName[strlen(amsFileName) - 3] = 'a';
            amsFileName[strlen(amsFileName) - 2] = 'm';
            amsFileName[strlen(amsFileName) - 1] = 's';
            amsFileName[strlen(amsFileName)] = '\0';
            // Create .ams file based on .txt file
            createAMS(argv[1], amsFileName);
            // Store the song in memory
            mySong[0] = readAMS(amsFileName);
            // Update the number of song
            nbSong = 1;
            free(amsFileName);
        // Handle .ams file
        } else if (endWith(argv[1], ".ams")) {
            // Store the song in memory
            mySong[0] = readAMS(argv[1]);
            // Update the number of song
            nbSong = 1;
        // Handle .amp file
        } else if (endWith(argv[1], ".amp")) {
            // Open .amp file
            FILE* file = initAMP(argv[1]);
            // Store in memory each songs in the playlist
            for (int i = 0; i < 4; i++) {
                // Get the first music file name .amp
                char song_filename[MAX_SIZE_TITLE];
                readAMP(file, song_filename);
                // Get the playlist dir (only work on windows)
                // TODO : add support for linux
                char folder[100];
                _splitpath_s(argv[1], NULL, 0, folder, sizeof(folder), NULL , 0, NULL, 0);
                // Add folder path to song filename
                char song_filename_with_folder[MAX_SIZE_TITLE];
                strcpy(song_filename_with_folder, folder);
                strcat(song_filename_with_folder, song_filename);
                // Check if the song in .ams exist, if not try to use the .txt version
                if (!exists(song_filename_with_folder)) {
                    // Check if the song in .txt exist other stop and return 1
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
                // Store the song in memory
                mySong[i] = readAMS(song_filename_with_folder);
                // Update the number of song
                nbSong++;
                // If we have reached the end of file before we read 4 song, stop reading
                if (feof(file)) {
                    break;
                }
            }
        // If a music has an unhandled extension, stop and return 1
        } else {
            printf("Error: File is not an .ams, .amp or .txt file\n");
            free(mySong);
            return 1;
        }
    // If no file has been provided load a default one
    } else {
        mySong[0] = readAMS("bohemian_rhapsody.ams");
        nbSong = 1;
    }

    char temp[INIT_FRAME_MAX_SIZE];

    printf("nbSong: %d\n", nbSong);

    for (int i = 0; i < nbSong; i++) {
        // If a song has no ticks then it's not a song so skip and go to the next song
        printf("%d, Song : %s\n", i, mySong[i].title);
        if (mySong[i].nTicks == 0) {
            printf("Error: exit, music do not have any tick\n");
            free(mySong);
            return 1;
        }
        // Store all the frame to then send it using UART
        char* toSend = calloc(INIT_FRAME_MAX_SIZE + mySong[i].nTicks * TICK_FRAME_SIZE, sizeof(char));
        // Create the init frame and load it
        createInitFrame(mySong[i], temp);
        strcpy(toSend, temp);
        // Load each ticks
        for (int j = 0; j < mySong[i].nTicks; j++) {
            createTickFrame(mySong[i].tickTab[j], temp);
            strcat(toSend, temp);
        }
        // Send all the frame (the entire song) using UART
        writeUSB(toSend, handle);

        free(toSend);
        // Wait 1 seconde between each song to send
        sleep(1);
    }
    // Close the USB connection
    closeUSB(handle);

    free(mySong);

    return 0;
}
