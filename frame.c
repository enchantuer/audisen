#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "frame.h"
#include "define.h"

#include <math.h>
// Create the init frame of a song. It contain the name, the tempo, the number of ticks and a check sum
void createInitFrame(s_song mySong, char* frame){
	// Intial char for a frame
	frame[0] = '#';
	int count = 1;
	// Song name
	int length = strlen(mySong.title);
	for (int i = 0; i < length; i++) {
		frame[count] = mySong.title[i];
		count ++;
	}
	frame[count] = ',';
	count ++;
	// Tempo
	count = addDigitsNumberToString(frame, count, mySong.tpm, -1);
	frame[count] = ',';
	count ++;
	// Number of ticks
	count = addDigitsNumberToString(frame, count, mySong.nTicks, -1);
	frame[count] = '*';
	count ++;
	// Check sum using XOR on each byte between # and *
	int checkSum = 0x00;
	for (int i = 1; i < count-1; i++) {
		checkSum ^= frame[i];
	}
	count = add2DigitsHexToString(frame, count, checkSum);
	// End of frame chars
	frame[count] = '\r';
	frame[count + 1] = '\n';
	frame[count + 2] = '\0';
}
// Create the frame for one tick. It contain the mode, the accentuation, the 4 notes, the check sum
void createTickFrame(s_tick myTick, char* frame){
	// Intial char for a frame
	frame[0] = '#';
	int count = 1;
	// Mode
	frame[count] = '0';
	count ++;
	frame[count] = ',';
	count ++;
	// Accentuation
	frame[count] = myTick.accent + '0';
	count ++;
	frame[count] = ',';
	count ++;
	// The 4 notes
	for (int i = 0; i < 4; i++) {
		count = addDigitsNumberToString(frame, count, myTick.note[i], 2);
		frame[count] = ',';
		count ++;
	}
	frame[count-1] = '*';
	// Check sum using XOR on each byte between # and *
	int checkSum = 0x00;
	for (int i = 1; i < count-1; i++) {
		checkSum ^= frame[i];
	}
	count = add2DigitsHexToString(frame, count, checkSum);
	// End of frame chars
	frame[count] = '\r';
	frame[count + 1] = '\n';
	frame[count + 2] = '\0';
}
