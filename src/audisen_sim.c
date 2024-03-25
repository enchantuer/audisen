#include "../include/ams.h"
#include "../include/define.h"
#include "../include/frame.h"
#include "stdio.h"

int main() {
    s_song mySong = readAMS("bohemian_rhapsody.ams");

    FILE* f = fopen("bohemian_rhapsody.frm", "w");

    char line[INIT_FRAME_MAX_SIZE];

    createInitFrame(mySong, line);

    fprintf(f, "%s", line);

    for (int i = 0; i < mySong.nTicks; i++) {
        createTickFrame(mySong.tickTab[i], line);
        fprintf(f, "%s", line);
    }

    return 0;
}