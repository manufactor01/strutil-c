CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VFLAGS = --leak-check=full --show-reachable=yes --track-origins=yes
EXEC = pruebas
OBJFILE = strutil.o pruebas_strutil.o main.o
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
$(EXEC): $(OBJFILE)
	$(CC) $(CFLAGS) $(OBJFILE) -o $(EXEC)
all: $(EXEC)

run: all clear
	./$(EXEC)
clear:
	clear
valgrind: all clear
	valgrind $(VFLAGS) ./$(EXEC)
free: $(EXEC) $(OBJFILE)
	rm -f $(EXEC) *.o
gdb: all clear
	gdb -tui ./$(EXEC)
