MAIN = Main.c
UTIL = Big_int.c Util.c
BINARY = main

all:
	gcc -Wall -Werror -g $(UTIL) $(MAIN) -o $(BINARY) -lm

run:
	./$(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)