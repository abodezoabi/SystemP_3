
all: StrList

StrList: StrList.o Main.o
	gcc -Wall -g StrList.o Main.o -o StrList

StrList.o: StrList.c StrList.h
	gcc -Wall -g -c StrList.c

main.o: Main.c StrList.h
	gcc -Wall -g -c Main.c

clean:
	rm -f *.o StrList
