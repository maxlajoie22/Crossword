// Max Lajoie
// crossfunc.c

#include "crossfunc.h"


void standard(char words[MAX_WORDS][MAX_LETTERS], clues hints[MAX_WORDS]){
    char solutionBoard[BOARD_SIZE][BOARD_SIZE];
    char puzzleBoard[BOARD_SIZE][BOARD_SIZE];
    makeSolutionBoard(solutionBoard);
    makePuzzleBoard(puzzleBoard);

    int count = enterWords(words);
    convert2Upper(words);
    sortWords(words,count,hints);
    firstWord(words[0],solutionBoard,puzzleBoard,hints);

    
    char rejects[count][MAX_LETTERS];
    int rejectSpot =0;
    // skips words it cant place
    for (int i = 1; i < count; i++) {
        if (!placeWord(words[i], solutionBoard, puzzleBoard,hints)) {
            strcpy(rejects[rejectSpot],words[i]);
            rejectSpot++;
        }
    }
    
    // keeps looping until it can no longer place anything
    int rejectsNum = -1;

    while (rejectsNum != rejectSpot) {
        rejectsNum = rejectSpot; 
        rejectSpot = 0; //

        // try to place each word in the rejects array again
        for (int i = 0; i < rejectsNum; i++) {
            if (!placeWord(rejects[i], solutionBoard, puzzleBoard,hints)) {
                strcpy(rejects[rejectSpot], rejects[i]); // keep the word in the rejects array
                rejectSpot++; // increment the count of rejects for this iteration
            }
        }
    }

    // print all words that couldn't be placed after the loop
    if (rejectSpot > 0) {
        printf("The following words could not be placed:\n");
        for (int i = 0; i < rejectSpot; i++) {
            printf("%s\n", rejects[i]);
        }
    } else {
        printf("All words were successfully placed.\n");
    }
    
    printf("\nSolution Board:");
    displayBoard(solutionBoard);
    printf("\nPuzzle Board:");
    displayBoard(puzzleBoard);
    generateAnagramClues(words, count,hints);

    
}

void fileMode(char words[MAX_WORDS][MAX_LETTERS], FILE *fp,clues hints[MAX_WORDS]){
    char solutionBoard[BOARD_SIZE][BOARD_SIZE];
    char puzzleBoard[BOARD_SIZE][BOARD_SIZE];
    makeSolutionBoard(solutionBoard);
    makePuzzleBoard(puzzleBoard);

    int count = readFile(fp, words);
    convert2Upper(words);
    sortWords(words,count,hints);
    firstWord(words[0],solutionBoard,puzzleBoard,hints);

    char rejects[count][MAX_LETTERS];
    int rejectSpot =0;
    // skips words it cant place
    for (int i = 1; i < count; i++) {
        if (!placeWord(words[i], solutionBoard, puzzleBoard,hints)) {
            strcpy(rejects[rejectSpot],words[i]);
            rejectSpot++;
        }
    }
    
    // keeps looping until it can no longer place anything
    int rejectsNum = -1;

    while (rejectsNum != rejectSpot) {
        rejectsNum = rejectSpot; 
        rejectSpot = 0; //

        // try to place each word in the rejects array again
        for (int i = 0; i < rejectsNum; i++) {
            if (!placeWord(rejects[i], solutionBoard, puzzleBoard,hints)) {
                strcpy(rejects[rejectSpot], rejects[i]); // keep the word in the rejects array
                rejectSpot++; // increment the count of rejects for this iteration
            }
        }
    }

    // print all words that couldn't be placed after the loop
    if (rejectSpot > 0) {
        printf("The following words could not be placed:\n");
        for (int i = 0; i < rejectSpot; i++) {
            printf("%s\n", rejects[i]);
        }
    } else {
        printf("All words were successfully placed.\n");
    }

    printf("\nSolution Board:");
    displayBoard(solutionBoard);
    printf("\nPuzzle Board:");
    displayBoard(puzzleBoard);
    generateAnagramClues(words, count,hints);
}

void file2fileMode(char words[MAX_WORDS][MAX_LETTERS], FILE *fp1, FILE *fp2,clues hints[MAX_WORDS]){
    char solutionBoard[BOARD_SIZE][BOARD_SIZE];
    char puzzleBoard[BOARD_SIZE][BOARD_SIZE];
    makeSolutionBoard(solutionBoard);
    makePuzzleBoard(puzzleBoard);

    int count = readFile2File(fp1, words,fp2);
    convert2Upper(words);
    sortWords(words,count,hints);
    firstWord(words[0],solutionBoard,puzzleBoard,hints);
    
    int placedWords = count;
    char rejects[count][MAX_LETTERS];
    int rejectSpot =0;
    // skips words it cant place
    for (int i = 1; i < count; i++) {
        if (!placeWord(words[i], solutionBoard, puzzleBoard,hints)) {
            strcpy(rejects[rejectSpot],words[i]);
            rejectSpot++;
        }
    }
    
    // keeps looping until it can no longer place anything
    int rejectsNum = -1;

    while (rejectsNum != rejectSpot) {
        rejectsNum = rejectSpot; 
        rejectSpot = 0; //

        // try to place each word in the rejects array again
        for (int i = 0; i < rejectsNum; i++) {
            if (!placeWord(rejects[i], solutionBoard, puzzleBoard,hints)) {
                strcpy(rejects[rejectSpot], rejects[i]); // keep the word in the rejects array
                rejectSpot++; // increment the count of rejects for this iteration
            }
        }
    }

    // print all words that couldn't be placed after the loop
    if (rejectSpot > 0) {
        fprintf(fp2,"The following words could not be placed:\n");
        for (int i = 0; i < rejectSpot; i++) {
            fprintf(fp2,"%s\n", rejects[i]);
            placedWords--;
        }
    } else {
        fprintf(fp2,"All words were successfully placed.\n");
    }

    fprintf(fp2,"\nSolution Board:");
    displayBoardFile(solutionBoard, fp2);
    fprintf(fp2,"\nPuzzle Board:");
    displayBoardFile(puzzleBoard, fp2);
    generateAnagramCluesFile(words, count, fp2,hints);

    printf("Successfully created file\n");
}

// reads words reject invalid words until told to stop by . or too many words
int enterWords(char words[MAX_WORDS][MAX_LETTERS]){
    int count = 0;
    char tempWord[200];
    printf("Enter a list of words:\n");
    while(count < MAX_WORDS){
        fgets(tempWord, 200, stdin);
        if (strcmp(tempWord,".\n")==0) break;
        int len = strlen(tempWord);
        for (int i = 0; i<len;i++){
            if (tempWord[i]=='\n'){
                tempWord[i] =='\0';
                break;
            }
        }
        if (checkValid(tempWord,len)==1){
            strcpy(words[count],tempWord);
            count++;
        } else {
            printf("Not a valid response\n");
        }
    }
    return count;
}

int checkValid(char tempWord[MAX_LETTERS], int len){
    if (len <=2 || len>MAX_LETTERS) return 0;
    for (int i = 0; i<len; i++){
        if (!isalpha(tempWord[i]) && tempWord[i] != '\n') return 0;
    }
    return 1;
}


// set word to all UPPER
void convert2Upper(char words[MAX_WORDS][MAX_LETTERS]){
    for (int i =0; i <MAX_WORDS; i++){
        for (int j=0; j<MAX_LETTERS;j++){
            if (words[i][j] == '.') break;
            else words[i][j] = toupper(words[i][j]);
        }
    }
}

// blank board with all .
void makeSolutionBoard(char solutionBoard[BOARD_SIZE][BOARD_SIZE]){
    for (size_t i = 0; i < BOARD_SIZE; i++){
        for (size_t j = 0; j < BOARD_SIZE; j++){
            solutionBoard[i][j] = '.';
        }     
    }   
}

// blank board with all #
void makePuzzleBoard(char puzzleBoard[BOARD_SIZE][BOARD_SIZE]){
    for (size_t i = 0; i < BOARD_SIZE; i++){
        for (size_t j = 0; j < BOARD_SIZE; j++){
            puzzleBoard[i][j] = '#';
        }     
    }   
}

// sort words in descending order
void sortWords(char words[MAX_WORDS][MAX_LETTERS], int count,clues hints[MAX_WORDS]){
    char temp[MAX_LETTERS];
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strlen(words[j]) < strlen(words[j + 1])) {
                // Swap the elements
                strcpy(temp,words[j]);
                strcpy(words[j],words[j+1]);
                strcpy(words[j+1],temp);
            }
        }
    }

    //cpy it to hints
    for (int z =0;z<count;z++){
        strcpy(hints[z].word,words[z]);
    }
}

// print board
void displayBoard(char board[BOARD_SIZE][BOARD_SIZE]){
    printf("\n+");
    for (size_t k = 0; k <BOARD_SIZE; k++){
        printf("-");
    }
    printf("+\n");

    for (size_t i = 0; i < BOARD_SIZE; i++){
        printf("|");
        for (size_t j = 0; j < BOARD_SIZE; j++){
            printf("%c",board[i][j]);
        }
        printf("|\n");
    } 

    printf("+");
    for (size_t k = 0; k <BOARD_SIZE; k++){
        printf("-");
    }
    printf("+\n");
}

// format the longest word after it is sorted
void firstWord(char word[MAX_LETTERS], char solutionBoard[BOARD_SIZE][BOARD_SIZE], char puzzleBoard[BOARD_SIZE][BOARD_SIZE], clues hints[MAX_WORDS]){
    int len = strlen(word) -1;
    if (len == BOARD_SIZE) {
        // place the word horizontally in the middle row
        for (int i = 0; i < len; i++) {
            solutionBoard[BOARD_SIZE / 2][i] = word[i];
            puzzleBoard[BOARD_SIZE / 2][i] = ' ';
        }
        hints[0].col = 0;
    } else {
        // place the word horizontally in the middle row, centered
        int left = (BOARD_SIZE - len) / 2;
        int right = left + len - 1;
        hints[0].col = left;

        for (int i = left; i <= right; i++) {
            puzzleBoard[BOARD_SIZE / 2][i] = ' ';
            solutionBoard[BOARD_SIZE / 2][i] = word[i - left];
        }
    }
    
    strcpy(hints[0].word,word);
    hints[0].row = BOARD_SIZE/2;
    hints[0].orientation = 0;

}


// shuffles the words around
void generateAnagramClues(char words[MAX_WORDS][MAX_LETTERS], int count,clues hints[MAX_WORDS]) {
    srand(time(0));
    printf("\nClues:\n");
    for (int i = 0; i < count; i++) {
        char word[MAX_LETTERS];
        strcpy(word, words[i]);
        int len = strlen(word)-1;

        // Shuffle word for anagram clue
        for (int j = 0; j < len; j++) {
            int k = rand() % len;
            char temp = word[j];
            word[j] = word[k];
            word[k] = temp;
        }
        if (hints[i].orientation!=2) {
            printf("%d,%d",hints[i].row,hints[i].col);
            if (hints[i].orientation==1){
                printf("    Down  %s",word);
            } else {
                printf("  Across  %s",word);
            }
        }
    }
}

// checks if they can place
int canPlaceHorizontally(char board[BOARD_SIZE][BOARD_SIZE], const char *word, int row, int col) {
    int len = strlen(word)-1;

    // check if the word would go out of bounds horizontally
    if (col < 0 || col + len > BOARD_SIZE) return 0;

    // ensure no adjacent letters horizontally (left and right of word)
    if (col > 0 && board[row][col - 1] != '.') return 0;                 // left of word
    if (col + len < BOARD_SIZE && board[row][col + len] != '.') return 0; // right of word

    // check each character position for conflicts and adjacency restrictions
    for (int i = 0; i < len; i++) {
        int currentCol = col + i;

        // if this position already has a letter that doesn't match the word, reject
        if (board[row][currentCol] != '.' && board[row][currentCol] != word[i]) return 0;

        // check above and below the current position if not intersecting
        if (row > 0 && board[row - 1][currentCol] != '.' && board[row][currentCol] != word[i]) return 0;
        if (row < BOARD_SIZE - 1 && board[row + 1][currentCol] != '.' && board[row][currentCol] != word[i]) return 0;
    }

    return 1;
}

int canPlaceVertically(char board[BOARD_SIZE][BOARD_SIZE], const char *word, int row, int col) {
    
    int len = strlen(word)-1;

    // check if the word would go out of bounds vertically
    if (row < 0 || row + len > BOARD_SIZE) return 0;

    // ensure no adjacent letters vertically (above and below word)
    if (row > 0 && board[row - 1][col] != '.') return 0;                 // above word
    if (row + len < BOARD_SIZE && board[row + len][col] != '.') return 0; // below word

    // Check each character position for conflicts and adjacency restrictions
    for (int i = 0; i < len; i++) {
        int currentRow = row + i;

        // if this position already has a letter that doesn't match the word, reject
        if (board[currentRow][col] != '.' && board[currentRow][col] != word[i]) return 0; 

        // check left and right of the current position if not intersecting
        if (col > 0 && board[currentRow][col - 1] != '.' && board[currentRow][col] != word[i]) return 0;
        if (col < BOARD_SIZE - 1 && board[currentRow][col + 1] != '.' && board[currentRow][col] != word[i]) return 0;
    }

    return 1;
}


// attempts to place word on the board intersecting with common letters
int placeWord(char word[MAX_LETTERS], char solutionBoard[BOARD_SIZE][BOARD_SIZE], char puzzleBoard[BOARD_SIZE][BOARD_SIZE], clues hints[MAX_WORDS]) {
    int len = strlen(word) - 1;

    // Iterate through each cell on the board
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            // Check if this cell contains a letter that matches one in the word
            for (int i = 0; i < len; i++) {
                if (solutionBoard[row][col] == word[i]) {
                    // Try placing the word vertically
                    if (canPlaceVertically(solutionBoard, word, row - i, col)) {
                        placeVertically(solutionBoard, puzzleBoard, word, row - i, col);
                        // Update hints for the word
                        for (int z = 1; z < MAX_WORDS; z++) {
                            if (strcmp(hints[z].word, word) == 0 && hints[z].orientation == 2) {
                                hints[z].orientation = 1; // Vertical
                                hints[z].row = row - i;
                                hints[z].col = col;
                                break;
                            }
                        }
                        return 1;
                    }

                    // Try placing the word horizontally
                    if (canPlaceHorizontally(solutionBoard, word, row, col - i)) {
                        placeHorizontally(solutionBoard, puzzleBoard, word, row, col - i);
                        // Update hints for the word
                        for (int z = 1; z < MAX_WORDS; z++) {
                            if (strcmp(hints[z].word, word) == 0 && hints[z].orientation == 2) {
                                hints[z].orientation = 0; // Horizontal
                                hints[z].row = row;
                                hints[z].col = col - i;
                                break;
                            }
                        }
                        return 1;
                    }
                }
            }
        }
    }

    // Return 0 if the word could not be placed
    return 0;
}


// place words
void placeHorizontally(char solutionBoard[BOARD_SIZE][BOARD_SIZE], char puzzleBoard[BOARD_SIZE][BOARD_SIZE], const char *word, int row, int col) {
    int len = strlen(word)-1;
    for (int i = 0; i < len; i++) {
        solutionBoard[row][col + i] = word[i];
        puzzleBoard[row][col + i] = ' ';
    }
}

void placeVertically(char solutionBoard[BOARD_SIZE][BOARD_SIZE], char puzzleBoard[BOARD_SIZE][BOARD_SIZE], const char *word, int row, int col) {
    int len = strlen(word)-1;
    for (int i = 0; i < len; i++) {
        solutionBoard[row + i][col] = word[i];
        puzzleBoard[row + i][col] = ' ';
    }
}

int readFile(FILE *fp, char words[MAX_WORDS][MAX_LETTERS]){
    int count = 0;
    char tempWord[200];

    while (count < MAX_WORDS && fgets(tempWord, sizeof(tempWord), fp)) {
        // Remove newline character, if any
        int len = strlen(tempWord);
        if (len > 0 && tempWord[len - 1] == '\n') {
            tempWord[len - 1] = '\0';
            len--; // Adjust length after removing newline
        }

        // Check if the line read is "."
        if (strcmp(tempWord, ".") == 0) {
            break; // End reading
        }

        // Validate and copy the word
        if (checkValid(tempWord, len)) {
            strncpy(words[count], tempWord, MAX_LETTERS - 1);
            words[count][MAX_LETTERS - 1] = '\0'; // Ensure null-termination
            count++;
        } else {
            printf("Invalid word skipped: %s\n", tempWord);
        }
    }

    fclose(fp);
    return count;
}


// REDOING ALL DISPLAY FUNCTION BUT WITH FILES
void displayBoardFile(char board[BOARD_SIZE][BOARD_SIZE], FILE *fp){
    fprintf(fp,"\n+");
    for (size_t k = 0; k <BOARD_SIZE; k++){
        fprintf(fp,"-");
    }
    fprintf(fp,"+\n");

    for (size_t i = 0; i < BOARD_SIZE; i++){
        fprintf(fp,"|");
        for (size_t j = 0; j < BOARD_SIZE; j++){
            fprintf(fp,"%c",board[i][j]);
        }
        fprintf(fp,"|\n");
    } 

    fprintf(fp,"+");
    for (size_t k = 0; k <BOARD_SIZE; k++){
        fprintf(fp,"-");
    }
    fprintf(fp,"+\n");
}

void generateAnagramCluesFile(char words[MAX_WORDS][MAX_LETTERS], int count, FILE* fp,clues hints[MAX_WORDS]){
    srand(time(0));
    fprintf(fp,"\nClues:\n");
    for (int i = 0; i < count; i++) {
        char word[MAX_LETTERS];
        strcpy(word, words[i]);
        int len = strlen(word)-1;

        // Shuffle word for anagram clue
        for (int j = 0; j < len; j++) {
            int k = rand() % len;
            char temp = word[j];
            word[j] = word[k];
            word[k] = temp;
        }
        if (hints[i].orientation!=2) {
            fprintf(fp,"%d,%d",hints[i].row,hints[i].col);
            if (hints[i].orientation==1){
                fprintf(fp,"    Down  %s",word);
            } else {
                fprintf(fp,"  Across  %s",word);
            }
        }
    }
}



int readFile2File(FILE *fp, char words[MAX_WORDS][MAX_LETTERS], FILE *fp2){
    int count = 0;
    char tempWord[200];

    fprintf(fp2,"Reading words from file:\n");
    while (count < MAX_WORDS && fgets(tempWord, sizeof(tempWord), fp)) {
        // Remove newline character, if any
        int len = strlen(tempWord);
        if (strcmp(tempWord, ".") == 0) break;
        if (checkValid(tempWord, len)) {
            strncpy(words[count], tempWord, MAX_LETTERS - 1);
            words[count][MAX_LETTERS - 1] = '\0'; // Ensure null-termination
            count++;
        } else {
            fprintf(fp2,"Invalid word skipped: %s\n", tempWord);
        }
    }

    fclose(fp);
    return count;
}