#include "utils.h"

// AMP
// Remove the inputed char from the end and the start of the string (if their is multiple instance of this char, at the end or start, remove all of them)
void trim(char* string, char toTrim) {
    int length = strlen(string);
    // Trim the end
    while (length > 0 && string[length - 1] == toTrim) {
        length --;
        string[length] = '\0';
    }
    // Trim the beginning
    int i = 0;
    while (i < length && string[i] == toTrim) {
        i ++;
    }

    if (length - i == 0) {
        return;
    }

    // Shift to the left
    for (int j = 0; j < length-i; j ++) {
        string[j] = string[j+i];
    }
    string[length-i] = '\0';
}
// Return true if the char is a digit
int isNumeric(char c) {
    return c >= '0' && c <= '9';
}
// Return true if the char is a letter
int isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
// Return true if the char is a digit or a letter
int isAlphanumeric(char c) {
    return isNumeric(c) ||isAlpha(c);
}
// Replace all char that are not alphanumeric by an '_'
void replaceSpecialChar(char* string) {
    int length = strlen(string);
    for (int i = 0; i < length; i++) {
        if (!isAlphanumeric(string[i])) {
            string[i] = '_';
        }
    }
}
// Remove all multiple occurence at once of underscore and let only one
void removeDuplicateUnderscore(char* string) {
    int length = strlen(string);
    if (length == 0) {
        return;
    }
    // Buffer to update the string
    char* temp = (char *) malloc(length + 1);
    // Ignore the first char and since we check two by two char
    temp[0] = string[0];
    int count = 1;
    // Check for duplicate
    for (int i = 1; i < length; i++) {
        // If it's a duplicate, ignore it. Otherwith add it to the buffer
        if (!(string[i] == '_' && string[i-1] == '_')) {
            temp[count] = string[i];
            count ++;
        }
    }
    temp[count] = '\0';
    // Replace the string content with the buffer content
    strcpy(string, temp);
    // Free memory for the buffer
    free(temp);
}
// Add the .amp extension to a file name
void addAMPExtension(char* string) {
    int length = strlen(string);
    string[length] = '.';
    string[length + 1] = 'a';
    string[length + 2] = 'm';
    string[length + 3] = 's';
    string[length + 4] = '\0';
}
// Appli all the wanted transformation to the song name so it become the song filename
void formatString(char* string) {
    replaceSpecialChar(string);
    trim(string, '_');
    removeDuplicateUnderscore(string);
    strlwr(string);
    addAMPExtension(string);
}
// AMS
// Check for a filename extension
int endWith(const char *str, const char *suffix){
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

// AMS
// Check the start a char*
int startWith(const char *str, const char *prefix){
    if (!str || !prefix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lenprefix = strlen(prefix);
    if (lenprefix >  lenstr)
        return 0;
    return strncmp(str, prefix, lenprefix) == 0;
}

// Frame
// Add digit of variable / fixed number of digit at the given index of a string
// If nbOfDigits is -1, adapte to the number of digits of the number. Otherwith, add it with a fixed number of digits
int addDigitsNumberToString(char* string, int start, int number, int nbOfDigits) {
    if (nbOfDigits == -1) {
        if (number == 0) {
            string[start] = '0';
            // Return the index just after the added number
            return start + 1;
        }
        // Calculate the number of digit
        nbOfDigits = 1;
        int temp = number;
        while (temp > 9) {
            temp /= 10;
            nbOfDigits ++;
        }
    }
    // Add each digit
    for (int i =0; i < nbOfDigits; i++) {
        string[start] = number / (int)(pow(10, nbOfDigits-i-1)) % 10 + '0';
        start ++;
    }
    // Return the index just after the added number
    return start;
}
// Add the a 2 digit hexadecimal value into a string a start index
int add2DigitsHexToString(char* string, int start, int hex) {
    // Correspondance deciaml-hexa
    char hexString[16] = "0123456789abcdef";
    string[start] = hexString[hex / 16];
    string[start + 1] = hexString[hex % 16];
    // Return the index just after the added number
    return start + 2;
}

int exists(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}