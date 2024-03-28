#include "ams.h"
#include "amp.h"
#include "define.h"
#include "frame.h"
#include "stdio.h"

int main(int argc, char** argv) {

    s_song* mySong = calloc(4, sizeof(s_song));
    char** fileNames = calloc(4, sizeof(char*));
    for (int i = 0; i < 4; i++) {
        fileNames[i] = calloc(100, sizeof(char));
    }
    int nbSong = 0;

    if (argc >= 2) {
        if (endWith(argv[1], ".txt")) {
            char* amsFileName = malloc(sizeof(char) * (strlen(argv[1]) + 1));
            strcpy(amsFileName, argv[1]);
            strcpy(fileNames[0], argv[1]);
            amsFileName[strlen(amsFileName) - 3] = 'a';
            amsFileName[strlen(amsFileName) - 2] = 'm';
            amsFileName[strlen(amsFileName) - 1] = 's';
            amsFileName[strlen(amsFileName)] = '\0';

            fileNames[0][strlen(fileNames[0]) - 3] = 'f';
            fileNames[0][strlen(fileNames[0]) - 2] = 'r';
            fileNames[0][strlen(fileNames[0]) - 1] = 'm';
            fileNames[0][strlen(fileNames[0])] = '\0';

            createAMS(argv[1], amsFileName);

            mySong[0] = readAMS(amsFileName);
            nbSong = 1;
            free(amsFileName);
        } else if (endWith(argv[1], ".ams")) {
            mySong[0] = readAMS(argv[1]);
            nbSong = 1;

            strcpy(fileNames[0], argv[1]);
            fileNames[0][strlen(fileNames[0]) - 3] = 'f';
            fileNames[0][strlen(fileNames[0]) - 2] = 'r';
            fileNames[0][strlen(fileNames[0]) - 1] = 'm';
            fileNames[0][strlen(fileNames[0])] = '\0';

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
                        free(fileNames);
                        return 1;
                    }
                }

                strcpy(fileNames[i], song_filename_with_folder);
                fileNames[i][strlen(fileNames[i]) - 3] = 'f';
                fileNames[i][strlen(fileNames[i]) - 2] = 'r';
                fileNames[i][strlen(fileNames[i]) - 1] = 'm';
                fileNames[i][strlen(fileNames[i])] = '\0';

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
            free(fileNames);
            return 1;
        }
    } else {
        mySong[0] = readAMS("bohemian_rhapsody.ams");
        nbSong = 1;
    }

    if (mySong[0].nTicks == 0) {
        printf("Error: exit, music do not have any tick\n");
        free(mySong);
        free(fileNames);
        return 1;
    }


    char line[INIT_FRAME_MAX_SIZE];

    for (int i = 0; i < nbSong; i++) {
        FILE* f = fopen(fileNames[i], "wb");

        createInitFrame(mySong[i], line);
        fprintf(f, "%s", line);

        for (int j = 0; j < mySong[i].nTicks; j++) {
            createTickFrame(mySong[i].tickTab[j], line);
            fprintf(f, "%s", line);
        }

        fclose(f);

        if (argc >= 3) {
            if (startWith(argv[2], "play-pyhton")) {
                char* pythonCommand = calloc(strlen(fileNames[i]) + 25, sizeof(char));

                strcat(pythonCommand, "py .\\play.py ");
                strcat(pythonCommand, fileNames[i]);

                system(pythonCommand);

                free(pythonCommand);
            }
        }
    }

    free(mySong);
    free(fileNames);

    return 0;
}