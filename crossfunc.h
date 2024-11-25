// Max Lajoie
// crossfunc.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_WORDS 20
#define MAX_LETTERS 16
#define BOARD_SIZE 15

typedef struct{
    char word[MAX_LETTERS];
    int row;
    int col;
    int orientation; // a 0 for across a 1 for vertical a 2 for not used
} clues;

void convert2Upper(char [MAX_WORDS][MAX_LETTERS]);
void makeSolutionBoard(char [BOARD_SIZE][BOARD_SIZE]);
void makePuzzleBoard(char [BOARD_SIZE][BOARD_SIZE]);
void displayBoard(char [BOARD_SIZE][BOARD_SIZE]);
void sortWords(char [MAX_WORDS][MAX_LETTERS],int,clues [MAX_WORDS]);
int checkValid(char [MAX_LETTERS], int);
int enterWords(char [MAX_WORDS][MAX_LETTERS]);
void standard(char words[MAX_WORDS][MAX_LETTERS] , clues [MAX_WORDS]);
void firstWord(char [MAX_LETTERS], char [BOARD_SIZE][BOARD_SIZE], char [BOARD_SIZE][BOARD_SIZE],clues [MAX_WORDS]);
void generateAnagramClues(char [MAX_WORDS][MAX_LETTERS], int, clues [MAX_WORDS]);
void placeHorizontally(char [BOARD_SIZE][BOARD_SIZE], char [BOARD_SIZE][BOARD_SIZE], const char *, int, int);
void placeVertically(char [BOARD_SIZE][BOARD_SIZE], char [BOARD_SIZE][BOARD_SIZE], const char *, int, int);
int canPlaceVertically(char [BOARD_SIZE][BOARD_SIZE], const char *, int, int);
int canPlaceHorizontally(char [BOARD_SIZE][BOARD_SIZE], const char *, int, int);
int placeWord(char [MAX_LETTERS], char [BOARD_SIZE][BOARD_SIZE], char [BOARD_SIZE][BOARD_SIZE], clues [MAX_WORDS]);
void fileMode(char [MAX_WORDS][MAX_LETTERS], FILE*, clues [MAX_WORDS]);
int readFile(FILE*, char [MAX_WORDS][MAX_LETTERS]);
void file2fileMode(char [MAX_WORDS][MAX_LETTERS], FILE*, FILE*, clues [MAX_WORDS]);
void displayBoardFile(char [BOARD_SIZE][BOARD_SIZE], FILE*);
void generateAnagramCluesFile(char [MAX_WORDS][MAX_LETTERS], int, FILE*,clues [MAX_WORDS]);
int readFile2File(FILE*,char [MAX_WORDS][MAX_LETTERS], FILE*);