#ifndef AUDISEN2024_AMS_H
#define AUDISEN2024_AMS_H

#include "define.h"

struct song initSong();
struct song readAMS(char* fileName);
void createAMS(char* txtFileName, char* amsFileName);

int endWith(const char *str, const char *suffix);

int returnNoteIndex(const char *str);

int numberOfTimeToSetNote(char character);

#endif //AUDISEN2024