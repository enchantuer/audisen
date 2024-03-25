
#ifndef AUDISEN2024_UTILS_H
#define AUDISEN2024_UTILS_H

void trim(char* string, char toTrim);

int isNumeric(char c);
int isAlpha(char c);
int isAlphanumeric(char c);

void replaceSpecialChar(char* string);
void removeDuplicateUnderscore(char* string);

void addAMPExtension(char* string);

void formatString(char* string);

#endif //AUDISEN2024_UTILS_H
