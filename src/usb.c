#include "../include/define.h"
#include "../include/frame.h"
#include "../include/usb.h"


FT_HANDLE initUSB(){
    FT_HANDLE ftHandle;

    FT_STATUS ftStatus = FT_Open(0, &ftHandle);

    if (ftStatus != FT_OK) {
        printf("Error: FT_Open(%d) failed\n", 0);
        return 0;
    }

    return ftHandle;

}
void closeUSB(FT_HANDLE ftHandle){
    FT_STATUS ftStatus = FT_Close(ftHandle);
    if (ftStatus == FT_OK) {
        printf("USB Closed !");
    }
    else {
        printf("USB Error !");
    }
}


void writeUSB(char* frame, FT_HANDLE ftHandle){
    DWORD BytesWritten;
    char TxBuffer[256]; // Contains data to write to device
    strcpy(TxBuffer, frame);

    FT_STATUS ftStatus = FT_Write(ftHandle, TxBuffer, sizeof(TxBuffer), &BytesWritten);
    if (ftStatus == FT_OK) {
        printf("USB Work !");
    }
    else {
        printf("USB Error !");
    }
}