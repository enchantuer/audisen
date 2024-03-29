#include "define.h"
#include "amp.h"

// Open the .amp file
FILE* initAMP(char* filename){
    if (!endWith(filename, ".amp")){
        printf("Error: File is not a .amp file\n");
        return NULL;
    }
    FILE * pf = fopen(filename, "r");
    if (pf == NULL){
        printf("Error: File not found\n");
    }
    return pf;
}

// song_filname must have 40 char allocated for song name + 4 char for the file extension (.ams)
void readAMP(FILE* pf, char * song_filename){
    // Buffer to store the file name, limited to 40 char + the end of string char ('\0')
    do {
        char buffer[MAX_SIZE_TITLE + 1];
        // Get the song name
        fgets(buffer, MAX_SIZE_TITLE + 1, pf);
        // Store it
        strcpy(song_filename, buffer);
        // Format it so it follow the sandard and have the file extension ().ams
        formatString(song_filename);
		if (!exists(song_filename)) {
            // Check if the song in .txt exist other
            char txt_filename[100];
            strcpy(txt_filename, song_filename);
            txt_filename[strlen(txt_filename) - 4] = '\0';
            strcat(txt_filename, ".txt");
			// If it exist, create .ams file based on .txt
            if (exists(txt_filename)) {
                createAMS(txt_filename, song_filename);
            }
        }
        // Make sure that the end of line has been reach so that next time it read the next song name
        while (!(feof(pf) || buffer[strlen(buffer) - 1] == '\n')) {
            fgets(buffer, MAX_SIZE_TITLE + 1, pf);
        }
    } while (strcmp(".ams", song_filename) == 0 && !feof(pf));
}
// Close the .amp file
void closeAMP(FILE* pf){
    if (pf != NULL) {
        fclose(pf);
    }
}