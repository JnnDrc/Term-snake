CC := gcc
CFLAGS := -Wall -Wextra -O3
TGT := tsnk
OBJ := main.o game.o input.o

$(TGT): $(OBJ)
	$(CC) -o $@ $^ 

$(OBJ): %.o: src/%.c
	$(CC) -c $< $(CFLAGS)
