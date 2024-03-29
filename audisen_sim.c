#include "ams.h"
#include "amp.h"
#include "define.h"
#include "frame.h"
#include "stdio.h"

// Create .frm file to play on a simulator. Can optionaly also directly play them
int main(int argc, char** argv) {

    s_song* mySong = calloc(4, sizeof(s_song));
    char** fileNames = calloc(4, sizeof(char*));
    for (int i = 0; i < 4; i++) {
        fileNames[i] = calloc(100, sizeof(char));
    }
    int nbSong = 0;
    if (argc >= 2) {
        // Handle .txt file input
        if (endWith(argv[1], ".txt")) {
            // Create the .ams file and store the song in memory based on the .txt file
            // Create the .ams file name
            char* amsFileName = malloc(sizeof(char) * (strlen(argv[1]) + 1));
            strcpy(amsFileName, argv[1]);
            strcpy(fileNames[0], argv[1]);
            amsFileName[strlen(amsFileName) - 3] = 'a';
            amsFileName[strlen(amsFileName) - 2] = 'm';
            amsFileName[strlen(amsFileName) - 1] = 's';
            amsFileName[strlen(amsFileName)] = '\0';
            // Create the .frm file name
            fileNames[0][strlen(fileNames[0]) - 3] = 'f';
            fileNames[0][strlen(fileNames[0]) - 2] = 'r';
            fileNames[0][strlen(fileNames[0]) - 1] = 'm';
            fileNames[0][strlen(fileNames[0])] = '\0';
            // Create the .ams based on the .txt
            createAMS(argv[1], amsFileName);
            // Store in memory the song based on the .ams
            mySong[0] = readAMS(amsFileName);
            // Update the number of song to send
            nbSong = 1;
            free(amsFileName);
        // Handle .ams file input
        } else if (endWith(argv[1], ".ams")) {
            // Store in memory the song based on the .ams
            mySong[0] = readAMS(argv[1]);
            // Update the number of song
            nbSong = 1;
            // Create the .frm file name
            strcpy(fileNames[0], argv[1]);
            fileNames[0][strlen(fileNames[0]) - 3] = 'f';
            fileNames[0][strlen(fileNames[0]) - 2] = 'r';
            fileNames[0][strlen(fileNames[0]) - 1] = 'm';
            fileNames[0][strlen(fileNames[0])] = '\0';
        // Handle .amp file input
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
                    // If the .txt exist, create .ams file based on it
                    if (exists(txt_filename)) {
                        createAMS(txt_filename, song_filename_with_folder);
                    } else {
                        printf("Error: File not found\n");
                        free(mySong);
                        free(fileNames);
                        return 1;
                    }
                }
                // Create the .frm filename
                strcpy(fileNames[i], song_filename_with_folder);
                fileNames[i][strlen(fileNames[i]) - 3] = 'f';
                fileNames[i][strlen(fileNames[i]) - 2] = 'r';
                fileNames[i][strlen(fileNames[i]) - 1] = 'm';
                fileNames[i][strlen(fileNames[i])] = '\0';

                printf("%s\n", song_filename_with_folder);
                // Load in memory the song
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
            free(fileNames);
            return 1;
        }
    // If no file has been provided load a default one
    } else {
        mySong[0] = readAMS("bohemian_rhapsody.ams");
        nbSong = 1;
    }
    // Create a .frm for each song
    char line[INIT_FRAME_MAX_SIZE];

    for (int i = 0; i < nbSong; i++) {
        // If a song has no ticks then it's not a song so skip and go to the next song
        if (mySong[i].nTicks == 0) {
            printf("Error: Skip, music do not have any tick\n");
            continue;
        }
        // Open the .frm file
        FILE* f = fopen(fileNames[i], "wb");
        // Create the init frame and load it into the .frm
        createInitFrame(mySong[i], line);
        fprintf(f, "%s", line);
        // Add each ticks to the .frm file
        for (int j = 0; j < mySong[i].nTicks; j++) {
            createTickFrame(mySong[i].tickTab[j], line);
            fprintf(f, "%s", line);
        }
        // Close the .frm file
        fclose(f);
        // If the exe was called with the -play-python option, call play.py to play the .frm on the simulator
        if (argc >= 3) {
            if (startWith(argv[2], "-play-python")) {
                char* pythonCommand = calloc(strlen(fileNames[i]) + 25, sizeof(char));

                strcat(pythonCommand, "py .\\play.py ");
                strcat(pythonCommand, fileNames[i]);

                system(pythonCommand);

                free(pythonCommand);
            }
        }
    }

    free(mySong);
    for (int i = 0; i < 4; i++) {
        free(fileNames[i]);
    }
    free(fileNames);

    return 0;
}