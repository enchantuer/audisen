
#include "define.h"
#include "amp.h"


FILE* initAMP(char* filename){
    FILE * pf = NULL;
    pf = fopen(filename, "r");
    return pf;
}

void removeEndLine(char* string) {
    int strLength = strlen(string);
    if (strLength == 0) {
        return;
    }
    while (string[strLength - 1] == '\n' || string[strLength - 1] == '\r') {
        strLength --;
        string[strLength] = '\0';
        if (strLength == 0) {
            break;
        }
    }
}

void readAMP(FILE* pf, char * song_filename){
    char * buffer = (char *) malloc(MAX_SIZE_TITLE + 1);
    fgets(buffer, MAX_SIZE_TITLE + 1, pf);
    removeEndLine(buffer);
    strcpy(song_filename, buffer);
    while ((!feof(pf)) || (buffer[strlen(buffer) - 1] != '\n')) {
        fgets(buffer, MAX_SIZE_TITLE + 1, pf);
    }
    free(buffer);
}

void closeAMP(FILE* pf){
    if (pf != NULL) {
        fclose(pf);
    }
}