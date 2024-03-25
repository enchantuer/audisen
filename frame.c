#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "frame.h"
#include "define.h"

#include <math.h>

void createInitFrame(s_song mySong, char* frame){
	frame[0] = '#';
	int count = 1;
	int length = strlen(mySong.title);
	for (int i = 0; i < length; i++) {
		frame[count] = mySong.title[i];
		count ++;
	}
	frame[count] = ',';
	count ++;
	count = addDigitsNumberToString(frame, count, mySong.tpm, -1);
	frame[count] = ',';
	count ++;
	count = addDigitsNumberToString(frame, count, mySong.nTicks, -1);
	frame[count] = '*';
	count ++;
	__int16 checkSum = 0x0;
	for (int i = 1; i < count-1; i++) {
		checkSum ^= frame[i];
	}
	count = add2DigitsHexToString(frame, count, checkSum);
	frame[count] = '\r';
	frame[count + 1] = '\n';
}

void createTickFrame(s_tick myTick, char* frame){
	frame[0] = '#';
	int count = 1;
	frame[count] = '0';
	count ++;
	frame[count] = ',';
	count ++;
	frame[count] = myTick.accent + '0';
	count ++;
	frame[count] = ',';
	count ++;
	for (int i = 0; i < 4; i++) {
		count = addDigitsNumberToString(frame, count, myTick.note[i], 2);
		frame[count] = ',';
		count ++;
	}
	frame[count-1] = '*';
	__int16 checkSum = 0x0;
	for (int i = 1; i < count-1; i++) {
		checkSum ^= frame[i];
	}
	count = add2DigitsHexToString(frame, count, checkSum);
	frame[count] = '\r';
	frame[count + 1] = '\n';
}
