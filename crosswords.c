// Max Lajoie
// crossword.c

#include "crossfunc.h"


int main(int argc, char *argv[]){
    printf("\nAnagram Crossword Puzzle Generator\n");
    printf("----------------------------------\n\n");
    char words[MAX_WORDS][MAX_LETTERS];
    clues hints[MAX_WORDS];
    for (int i = 0; i<MAX_WORDS;i++) hints[i].orientation =2;
    if (argc==3){
        FILE *fp1 = fopen(argv[argc-2],"r");
        FILE *fp2 = fopen(argv[argc-1],"w");
        if (!fp1){
            printf("couldn't open file. Aborting.\n");
            return 1;
        }
        if (!fp2){
            printf("couldn't create file. Aborting.\n");
            return 1;
        }
        file2fileMode(words,fp1,fp2,hints);
    } else if (argc ==2){
        FILE *fp = fopen(argv[argc-1],"r");
        if (!fp){
            printf("couldn't open file. Aborting.\n");
            return 1;
        }
        fileMode(words, fp, hints);
    
    } else if (argc ==1){
        standard(words,hints);
    } else {
        printf("Not a valid number of arguments\n");
        return 1;
    }
    return 0;
}