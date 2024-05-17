#@ symbol used in front of echo so that the echo command itself isn't printed and only whats in the "" is printed

#-o renames the executable to whatever is after it instead of the default "a.out"

#-c compiles without linking any files

#the way "all" command works is that it compiler looks at "all" call which is linked to "final" call. "final" call is linked to "main.o" call, which is the bottom of the call chain. It runs "main.o" first and then "final.
CFLAGS = -g -Wall


all : final


final : main.o
	@echo "Linking all files and producing final app"
	gcc $(CFLAGS) main.o -o RPS_Game

main.o: main.c
	@echo "Compiling main file"
	gcc $(CFLAGS) -c main.c

clean:
	@echo "Removing everything but source files"
	rm RPS_Game main.o
