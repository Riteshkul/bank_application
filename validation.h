#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>


int isValidNameFormat(const char name[]) {
    int spaceCount = 0;

    for (int i = 0; i < strlen(name); i++) {
        if (isalpha(name[i]) || isspace(name[i])) {
            if (isspace(name[i])) {
                spaceCount++;
            }
        } else {
            return 0;  // Invalid character in the name
        }
    }

    // Check for at least two spaces (first name, middle name, last name)
    return spaceCount >= 2;
}

int isValidAge(int age) {
    return age > 18 && age < 100;
}

int isValidGender(const char gender[]) {
    return strcmp(gender, "male") == 0 || strcmp(gender, "female") == 0 || strcmp(gender, "other") == 0;
}


int isValidDOB(const char dob[]) {
    int day, month, year;
    if (sscanf(dob, "%2d/%2d/%4d", &day, &month, &year) != 3) {
        return 0;  // Incorrect format
    }

    if (day < 1 || day > 31 || month < 1 || month > 12 || year >= 2024) {
        return 0;  // Invalid day, month, or year
    }

    return 1;
}

int checkAadhar(char str[]) {
    if (strlen(str) == 12) {
        for (int i = 0; i < strlen(str); i++) {
            if (!isdigit(str[i])) return 0;
        }
        return 1;
    } else {
        return 0;
    }
}

int checkPanCard(char str[]) {
    if (strlen(str) == 10){
        for (int i = 0; i <= 4; i++) {
        if (!isupper(str[i])) return 0;
        }
        for (int i = 5; i <= 8; i++) {
            if (!isdigit(str[i])) return 0;
        }
        if (!isupper(str[9])) return 0;
        return 1;
    }
    else return 0;
}

void generateAccNo(const char accHolderName[], char accNo[]) {
    // Your implementation for generating account number
    // For simplicity, using a static counter as part of the account number
    static int counter = 1;

    // Extracting the initials from the name
    char initials[4];
    int index = 0;
    initials[index++] = toupper(accHolderName[0]);

    for (int i = 1; i < strlen(accHolderName); i++) {
        if (accHolderName[i - 1] == ' ' && accHolderName[i] != ' ') {
            initials[index++] = toupper(accHolderName[i]);
        }
    }

    // Adding 3 random digits without leading zeros
    sprintf(accNo, "%s%03d", initials, counter++);
}



int isValidAddress(const char *address) {
    for (int i = 0; i < strlen(address); i++) {
        if (!isalnum(address[i]) && !isspace(address[i])) {
            return 0; // Invalid address
        }
    }
    return 1; // Valid address
}

int isValidCity(const char *city) {
    for (int i = 0; i < strlen(city); i++) {
        if (!isalpha(city[i]) && !isspace(city[i])) {
            return 0; // Invalid city
        }
    }
    return 1; // Valid city
}

int isValidAccountType(const char *accType) {
    return (strcmp(accType, "saving") == 0 || strcmp(accType, "current") == 0);
}

#endif
