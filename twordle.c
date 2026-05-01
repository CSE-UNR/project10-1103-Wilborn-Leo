//Author: Leo Wilborn
//Date: 04/28/2026
//Purpose: CS project 10

#include <stdio.h>
#include <stdbool.h>

#define SIZE 6


void getWord(char word[]);
int getLength(char str[]);
bool checkGuess(char guesses[][SIZE], int guessNumber);
void capitalizeLetters(char word[], char guesses[][SIZE], int guessNumber);
void printCaret(char word[], char guesses[][SIZE], int row, char wordCopy[]);
void history(char word[], char guesses[][SIZE], int guessNumber);

int main() {
    char word[SIZE];
    char guesses[6][SIZE]; 
    int guessNumber = 0;
    bool success = false;

    getWord(word);

    while (guessNumber < 6 && !success) {
        printf("Guess #%d: ", guessNumber + 1);
        scanf("%s", guesses[guessNumber]);

        if (!checkGuess(guesses, guessNumber)) {
            printf("Please enter a valid guess (5 lowercase letters).\n");
        } 
        else {
            capitalizeLetters(word, guesses, guessNumber);
            
            int correctLetters = 0;
            for (int i = 0; i < 5; i++) {
                if (guesses[guessNumber][i] == word[i] || guesses[guessNumber][i] == (word[i] - 32)) {
                    correctLetters++;
                }
            }

            history(word, guesses, guessNumber);

            if (correctLetters == 5) {
                success = true;
                printf("Wowza! You won in %d guesses.\n", guessNumber); 
            } else {
                guessNumber++;
            }
        }
    }

    if (!success) {
        printf("Sorry loser but you lost.");
    }

    return 0;
}

void getWord(char word[]) {
    FILE *fp = fopen("word.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open word.txt\n");
    } else {
        fscanf(fp, "%s", word);
        fclose(fp);
    }
}

int getLength(char str[]) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

bool checkGuess(char guesses[][SIZE], int guessNumber) {
    if (getLength(guesses[guessNumber]) != 5) {
        return false;
    }
    for (int i = 0; i < 5; i++) {
        if (guesses[guessNumber][i] < 'a' || guesses[guessNumber][i] > 'z') {
            return false;
        }
    }
    return true;
}

void capitalizeLetters(char word[], char guesses[][SIZE], int guessNumber) {
    for (int i = 0; i < 5; i++) {
        if (word[i] == guesses[guessNumber][i]) {
            guesses[guessNumber][i] = guesses[guessNumber][i] - 32;
        }
    }
}

void printCaret(char word[], char guesses[][SIZE], int row, char wordCopy[]) {
    for (int i = 0; i < 5; i++) {
        printf("%c", guesses[row][i]);
    }
    printf("\n");

    for (int i = 0; i < 5; i++) {
        bool needsCaret = false;

        if (guesses[row][i] >= 'a' && guesses[row][i] <= 'z') {
            for (int n = 0; n < 5; n++) {
                if (guesses[row][i] == word[n]) {
                    needsCaret = true;
                    break;
                }
            }
        }

        if (needsCaret) {
            printf("^");
        } else {
            printf(" ");
        }
    }
    printf("\n");
}

void history(char word[], char guesses[][SIZE], int guessNumber) {
    printf("\n--- Progress ---\n");
    for (int i = 0; i <= guessNumber; i++) {
        printCaret(word, guesses, i, word);
    }
    printf("----------------\n");
}
