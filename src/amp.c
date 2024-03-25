
#include "define.h"
#include "amp.h"

FILE* initAMP(char* filename){
    FILE * pf = NULL;
    pf = fopen(filename, "r");
    return pf;
}

void readAMP(FILE* pf, char * song_filename){
    char * buffer = (char *) malloc(MAX_SIZE_TITLE + 1);
    fgets(buffer, MAX_SIZE_TITLE + 1, pf);
    strcpy(song_filename, buffer);
    formatString(song_filename);
    while (!(feof(pf) || buffer[strlen(buffer) - 1] == '\n')) {
        fgets(buffer, MAX_SIZE_TITLE + 1, pf);
    }
    free(buffer);
}

void closeAMP(FILE* pf){
    if (pf != NULL) {
        fclose(pf);
    }
}