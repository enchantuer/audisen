#include "../include/define.h"
#include "../include/amp.h"

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