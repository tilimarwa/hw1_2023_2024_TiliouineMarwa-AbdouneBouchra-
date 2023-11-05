all:	mmm

mmm:	main.o initMatrix.o displayMatrix.o multiThreadedProgramExample.o
	gcc -Wall main.o initMatrix.o displayMatrix.o multiThreadedProgramExample.o -lpthread -lm -o mmm

main.o:	main.c
	gcc -c main.c -o main.o

initMatrix.o:	initMatrix.c
	gcc -c initMatrix.c -o initMatrix.o
	
displayMatrix.o:	displayMatrix.c
	gcc -c displayMatrix.c -o displayMatrix.o

multiThreadedProgramExample.o:	multiThreadedProgramExample.c
	gcc -c multiThreadedProgramExample.c -o multiThreadedProgramExample.o	

clean:
	rm -fr mmm *.o
