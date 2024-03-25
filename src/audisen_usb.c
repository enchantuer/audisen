#include "../include/usb.h"
#include "../include/ams.h"
#include "../include/define.h"
#include "../include/frame.h"

int main() {
    FT_HANDLE handle = initUSB();

    s_song mySong = readAMS("bohemian_rhapsody.ams");

    char line[INIT_FRAME_MAX_SIZE];

    createInitFrame(mySong, line);

    writeUSB(line, handle);

    for (int i = 0; i < mySong.nTicks; i++) {
        createTickFrame(mySong.tickTab[i], line);
        writeUSB(line, handle);
    }

    closeUSB(handle);

    return 0;
}