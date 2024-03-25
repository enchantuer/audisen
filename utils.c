
#include "define.h"
#include "utils.h"

// AMP
void trim(char* string, char toTrim) {
    int length = strlen(string);
    if (length == 0) {
        return;
    }
    // Trim the end
    while (string[length - 1] == toTrim) {
        length --;
        string[length] = '\0';
        if (length == 0) {
            break;
        }
    }
    // Trim the beginning
    int i = 0;
    while (string[i] == toTrim) {
        i ++;
    }
    // Shift to the left
    for (int j = 0; j < length-i; j ++) {
        string[j] = string[j+i];
    }
    string[length-i] = '\0';
}

int isNumeric(char c) {
    return c >= '0' && c <= '9';
}
int isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
int isAlphanumeric(char c) {
    return isNumeric(c) ||isAlpha(c);
}

void replaceSpecialChar(char* string) {
    int length = strlen(string);
    for (int i = 0; i < length; i++) {
        if (!isAlphanumeric(string[i])) {
            string[i] = '_';
        }
    }
}

void removeDuplicateUnderscore(char* string) {
    int length = strlen(string);
    if (length == 0) {
        return;
    }
    char* temp = (char *) malloc(length + 1);
    int count = 1;
    temp[0] = string[0];

    for (int i = 1; i < length; i++) {
        if (!(string[i] == '_' && string[i-1] == '_')) {
            temp[count] = string[i];
            count ++;
        }
    }
    temp[count] = '\0';
    strcpy(string, temp);
    free(temp);
}

void addAMPExtension(char* string) {
    int length = strlen(string);
    string[length] = '.';
    string[length + 1] = 'a';
    string[length + 2] = 'm';
    string[length + 3] = 's';
    string[length + 4] = '\0';
}

void formatString(char* string) {
    replaceSpecialChar(string);
    trim(string, '_');
    removeDuplicateUnderscore(string);
    strlwr(string);
    addAMPExtension(string);
}

int endWith(const char *str, const char *suffix){
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

// Frame
int addDigitsNumberToString(char* string, int start, int number, int nbOfDigits) {
    if (nbOfDigits == -1) {
        if (number == 0) {
            string[start] = '0';
            return start + 1;
        }
        nbOfDigits = 1;
        int temp = number;
        while (temp > 9) {
            temp /= 10;
            nbOfDigits ++;
        }
    }
    for (int i =0; i < nbOfDigits; i++) {
        string[start] = number / (int)(pow(10, nbOfDigits-i-1)) % 10 + '0';
        start ++;
    }
    return start;
}
int add2DigitsHexToString(char* string, int start, int hex) {
    char hexString[16] = "0123456789abcdef";
    string[start] = hexString[hex / 16];
    string[start + 1] = hexString[hex % 16];

    return start + 2;
}