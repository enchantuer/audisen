#include "../include/define.h"
#include "../include/frame.h"
#include "../include/usb.h"


FT_HANDLE initUSB(){
    FT_HANDLE ftHandle;

    int port = 0;

    FT_STATUS ftStatus = FT_Open(port, &ftHandle);

    if (ftStatus != FT_OK) {
        printf("Error: FT_Open(%d) failed\n", port);
        return 0;
    }

    ftStatus = FT_SetBaudRate(ftHandle, 9600);

    if (ftStatus != FT_OK) {
        printf("Error: FT_SetBaudRate failed\n");
        return 0;
    }

    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);

    if (ftStatus != FT_OK) {
        printf("Error: FT_SetDataCharacteristics failed\n");
        return 0;
    }

    // No flow controle
    ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0, 0);

    if (ftStatus != FT_OK) {
        printf("Error: FT_SetFlowControl failed\n");
        return 0;
    }

    return ftHandle;
}
void closeUSB(FT_HANDLE ftHandle){
    FT_STATUS ftStatus = FT_Close(ftHandle);
    if (ftStatus == FT_OK) {
        printf("USB Closed !\n");
    }
    else {
        printf("USB Error !\n");
    }
}


void writeUSB(char* frame, FT_HANDLE ftHandle){
    DWORD BytesWritten;

    FT_STATUS ftStatus = FT_Write(ftHandle, frame, strlen(frame), &BytesWritten);
    if (ftStatus == FT_OK) {
        printf("USB Work !, Write : %ld bit\n", BytesWritten);
    }
    else {
        printf("USB Error !\n");
    }
}