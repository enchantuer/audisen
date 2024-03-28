#ifndef AUDISEN2024_UTILS_H
#define AUDISEN2024_UTILS_H

#include "define.h"

#include <math.h>

// AMP
void trim(char* string, char toTrim);

int isNumeric(char c);
int isAlpha(char c);
int isAlphanumeric(char c);

void replaceSpecialChar(char* string);
void removeDuplicateUnderscore(char* string);

void addAMPExtension(char* string);

void formatString(char* string);

// Frame
int addDigitsNumberToString(char* string, int start, int number, int nbOfDigits);
int add2DigitsHexToString(char* string, int start, int hex);

int endWith(const char *str, const char *suffix);

int startWith(const char *str, const char *prefix);

int exists(const char *fname);

#endif //AUDISEN2024_UTILS_H
