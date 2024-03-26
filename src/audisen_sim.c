#include "../include/ams.h"
#include "../include/define.h"
#include "../include/frame.h"
#include "stdio.h"

int main() {
    s_song mySong = readAMS("bohemian_rhapsody.ams");

    FILE* f = fopen("bohemian_rhapsody.frm", "w");

    char line[INIT_FRAME_MAX_SIZE];

    createInitFrame(mySong, line);
    line[strlen(line)-2] = '\n';
    line[strlen(line)-1] = '\0';
    fprintf(f, "%s", line);

    for (int i = 0; i < mySong.nTicks-1; i++) {
        createTickFrame(mySong.tickTab[i], line);
        //remove the \r
        line[strlen(line)-2] = '\n';
        line[strlen(line)-1] = '\0';
        fprintf(f, "%s", line);
    }

    createTickFrame(mySong.tickTab[mySong.nTicks-1], line);
    line[strlen(line)-2] = '\0';
    fprintf(f, "%s", line);

    return 0;
}
