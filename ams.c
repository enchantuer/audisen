#include "ams.h"

// read .ams file and return the s_song object
s_song readAMS(char* fileName){
	s_song mySong;
	// Check file extension
	if (!endWith(fileName, ".ams")){
		printf("Error: File is not a .ams file\n");
		return mySong;
	}
	// Open the file
	FILE* file = fopen(fileName, "r");
	if (file == NULL){
		printf("Error: File not found\n");
		return mySong;
	}
	// Buffer that correpond to one line of the file
	char line[MAX_SIZE_LINE];
	int i = 0;
	// Get the name of the song
	fgets(line, MAX_SIZE_LINE, file);
	// Remove the end of line char
	line[strlen(line)-1] = '\0';
	strcpy(mySong.title, line);
	// Get the bpm of the song
	fgets(line, MAX_SIZE_LINE, file);
	mySong.tpm = 2 * atoi(line);
	// Ignore blank lines
	fgets(line, MAX_SIZE_LINE, file);
	// Remove the array horizontal header
	fgets(line, MAX_SIZE_LINE, file);
	// Get tick's notes
	while (fgets(line, MAX_SIZE_LINE, file)) {
		s_tick tick = {0, {0, 0, 0, 0}};
		int k = 0;
		int j = 4;
		for (int l = 1; l <= 60; l++) {
			// If their is a ^ then the note has an accent
			if (line[j] == '^') {
				tick.accent = 1;
				tick.note[k] = l;
				k++;
			}
			// If the note is a x then it's a normal note
			else if (line[j] == 'x') {
				tick.note[k] = l;
				k++;
			}
			j+=3;
			// If it's a blank then then note isn't played
		}
		// Add the tick to the song
		mySong.tickTab[i] = tick;
		i++;
	}
	// Store the number of tick
	mySong.nTicks = i;
	// Close the file
	fclose(file);

	return mySong;
}

// Convert a .txt file into a .ams file
void createAMS(char* txtFileName, char* amsFileName){
	// Open the .txt in read mode
	FILE* srcFile = fopen(txtFileName, "r");
	// Open the .ams in write mode
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
	// Print the content of .txt in .ams in the right format
	// Song name
	fgets(line, MAX_SIZE_LINE, srcFile);
	fprintf(distFile, "%s", line);
	// Tempo in bpm
	fgets(line, MAX_SIZE_LINE, srcFile);
	fprintf(distFile, "%s", line);
	// Blank line
	fgets(line, MAX_SIZE_LINE, srcFile);
	fprintf(distFile, "\n");
	// Matrix of note by ticks
	// Horizontal header
	fprintf(distFile, "    ");
	for (int i = 1; i <= 60; i++) {
		fprintf(distFile, "%02d ", i);
	}
	fprintf(distFile, "\n");
	// The reste of the matrix
	// Get the note for all the ticks
	// TODO change that, make it dynamic
	int notes[MAX_NUMBER_TICKS][60];
	int i = 0;
	while (fgets(line, MAX_SIZE_LINE, srcFile)) {
		int j = 0;
		// Get the notes (max 4)
		for (int n = 0; n < 4; n++) {
			char note[4] = "";
			int m = 0;
			// Get the note
			while (line[j] != ' ') {
				note[m] = line[j];
				j++;
				m++;
			}
			note[m] = '\0';
			// Converte note into a number between 1 and 60
			int noteIndex = returnNoteIndex(note);
			// If the note is not in our 60 note, then throw an error
			if (noteIndex == -1) {
				printf("Error: Note not found\n");
				return;
			}
			// Get the duration of the note based on the char following the note and white space
			int nbToSet = numberOfTimeToSetNote(line[j+1]);
			// Fill the matrix of note by tick using 1 if the note is to play with accentuation, 1 to play normaly and 0 otherwith (matrix initialized with 0)
			// For the first tick we play a note, accentuate it
			notes[i][noteIndex] = 1;
			// For the reminding duration of the note, play it normaly (1)
			for (int k = 1; k < nbToSet; k++) {
				notes[i+k][noteIndex] = 2;
			}
			// If their is no other note, stop adding note for that tick
			// Their is no other note if their is no ',' after the note duration char
			if (line[j+2] != ',') {
				break;
			}

			j+=4;
		}
		i++;
	}

	// Fill the matrix with the notes by tick (by row)
	for (int ii = 0; ii < i; ii++) {
		// Matrix Vertical header
		fprintf(distFile, "%03d", ii+1);
		// Print each note : 0 = ' ', 1 = '^' and 2 = 'x'
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

	// Close the files
	fclose(srcFile);
	fclose(distFile);
}
// Return the numeric value of a string note
int returnNoteIndex(const char *str) {
	// Correspondence between the string note and it's numeric value
	char** corespondanceNote = (char*[]){"C1", "C1#", "D1", "D1#", "E1", "F1", "F1#", "G1", "G1#", "A1", "A1#", "B1",
		"C2", "C2#", "D2", "D2#", "E2", "F2", "F2#", "G2", "G2#", "A2", "A2#", "B2",
		"C3", "C3#", "D3", "D3#", "E3", "F3", "F3#", "G3", "G3#", "A3", "A3#", "B3",
		"C4", "C4#", "D4", "D4#", "E4", "F4", "F4#", "G4", "G4#", "A4", "A4#", "B4",
		"C5", "C5#", "D5", "D5#", "E5", "F5", "F5#", "G5", "G5#", "A5", "A5#", "B5"};
	// Look for the index of the note into the array
	for (int i = 0; i < 60; i++) {
		if (strcmp(str, corespondanceNote[i]) == 0) {
			return i;
		}
	}
	// If no index found, return -1
	return -1;
}
// Return the numeric duration a note based on it's type in char
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
