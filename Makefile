runcrossword: crossword.o crossfunc.o
	gcc crossword.o crossfunc.o -o runcrossword

crossfunc.o: crossfunc.c crossfunc.h
	gcc -c crossfunc.c -o crossfunc.o

crossword.o: crossword.c crossfunc.h
	gcc -c crossword.c -o crossword.o

clean:
	rm *.o
	rm crossword
