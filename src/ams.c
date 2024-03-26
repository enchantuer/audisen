#include "../include/define.h"
#include "../include/ams.h"

s_song readAMS(char* fileName){
	s_song mySong;

	if (!endWith(fileName, ".ams")){
		printf("Error: File is not an .ams file\n");
		return mySong;
	}

	FILE* file = fopen(fileName, "r");

	if (file == NULL){
		printf("Error: File not found\n");
		return mySong;
	}

	char line[MAX_SIZE_LINE];
	int i = 0;
	fgets(line, sizeof(line), file);
	// remove the last \n
	line[strlen(line)-1] = '\0';
	strcpy(mySong.title, line);
	fgets(line, sizeof(line), file);
	mySong.tpm = 2 * atoi(line);
	fgets(line, sizeof(line), file);
	fgets(line, sizeof(line), file);

	while (fgets(line, sizeof(line), file)) {
		s_tick tick = {0, {0, 0, 0, 0}};
		int k = 0;
		int j = 4;
		for (int l = 1; l <= 60; l++) {
			if (line[j] == '^') {
				tick.accent = 1;
				tick.note[k] = l;
				k++;
			} else if (line[j] == 'x') {
				tick.note[k] = l;
				k++;
			}
			j+=3;
		}
		mySong.tickTab[i] = tick;
		i++;
	}

	mySong.nTicks = i;

	fclose(file);

	return mySong;
}


void createAMS(char* txtFileName, char* amsFileName){
	FILE* srcFile = fopen(txtFileName, "r");
	FILE* distFile = fopen(amsFileName, "w");

	if (srcFile == NULL){
		printf("Error: File not found\n");
		return;
	}
	if (distFile == NULL){
		printf("Error: File not found\n");
		return;
	}

	char line[MAX_SIZE_LINE];

	fgets(line, sizeof(line), srcFile);
	fprintf(distFile, "%s", line);
	fgets(line, sizeof(line), srcFile);
	fprintf(distFile, "%s", line);
	fgets(line, sizeof(line), srcFile);
	fprintf(distFile, "\n");

	fprintf(distFile, "    ");
	for (int i = 1; i <= 60; i++) {
		fprintf(distFile, "%02d ", i);
	}
	fprintf(distFile, "\n");

	// TODO change that, make it dynamic
	int notes[MAX_NUMBER_TICKS][60];
	int i = 0;
	while (fgets(line, sizeof(line), srcFile)) {
		int j = 0;

		for (int n = 0; n < 4; n++) {
			char note[4] = "";
			int m = 0;
			while (line[j] != ' ') {
				note[m] = line[j];
				j++;
				m++;
			}
			note[m] = '\0';
			int noteIndex = returnNoteIndex(note);
			if (noteIndex == -1) {
				printf("Error: Note not found\n");
				return;
			}

			int nbToSet = numberOfTimeToSetNote(line[j+1]);

			notes[i][noteIndex] = 1;
			for (int k = 1; k < nbToSet; k++) {
				notes[i+k][noteIndex] = 2;
			}

			if (line[j+2] != ',') {
				break;
			}

			j+=4;
		}
		i++;
	}


	for (int ii = 0; ii < i; ii++) {
		fprintf(distFile, "%03d", ii+1);
		for (int jj = 0; jj < 60; jj++) {
			if (notes[ii][jj] == 1) {
				fprintf(distFile, "|^ ");
			} else if (notes[ii][jj] == 2) {
				fprintf(distFile, "|x ");
			} else {
				fprintf(distFile, "|  ");
			}
		}
		fprintf(distFile, "|\n");
	}

	// fprintf(distFile, "%03d ", i+1);
	//
	// fprintf(distFile, "%s", line);


	fclose(srcFile);
	fclose(distFile);
}

int returnNoteIndex(const char *str) {
	char** corespondanceNote = (char*[]){"C1", "C1#", "D1", "D1#", "E1", "F1", "F1#", "G1", "G1#", "A1", "A1#", "B1",
		"C2", "C2#", "D2", "D2#", "E2", "F2", "F2#", "G2", "G2#", "A2", "A2#", "B2",
		"C3", "C3#", "D3", "D3#", "E3", "F3", "F3#", "G3", "G3#", "A3", "A3#", "B3",
		"C4", "C4#", "D4", "D4#", "E4", "F4", "F4#", "G4", "G4#", "A4", "A4#", "B4",
		"C5", "C5#", "D5", "D5#", "E5", "F5", "F5#", "G5", "G5#", "A5", "A5#", "B5"};

	char** corespondanceNoteHashtagBefore = (char*[]){"C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1",
		"C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2",
		"C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3",
		"C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4",
		"C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "B5"};

	for (int i = 0; i < 60; i++) {
		if (strcmp(str, corespondanceNote[i]) == 0) {
			return i;
		}
		if (strcmp(str, corespondanceNoteHashtagBefore[i]) == 0) {
			return i;
		}
	}
	return -1;
}

int numberOfTimeToSetNote(char character) {
	switch (character) {
		case 'R':
			return 8;
		case 'B':
			return 4;
		case 'N':
			return 2;
		case 'C':
			return 1;
		case 'D':
			return 1;
		default:
			return -1;
	}
}
