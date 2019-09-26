
CFLAGS=-m32 -fomit-frame-pointer  -fno-pic   -fno-stack-protector


CC=gcc

LD=gcc
all: main.out

main.out : main.o sum.o print.o
	$(LD) $(CFLAGS)  $< sum.o print.o -o $@  


main.o : main.c
	$(CC) -g $(CFLAGS) -g -c ${<}

sum.o : sum.c
	$(CC) $(CFLAGS) -c -g  ${<}

print.o : print.c
	$(CC) $(CFLAGS) -c -O1 ${<}
#	strip --strip-debug  $@


clean :
	rm -f *.o main main.out
