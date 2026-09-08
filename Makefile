.PHONY: clean

CFLAGS ?= -O2 -Wextra -Wpedantic -Wall -Iinclude/ -lreadline
CC ?= gcc

SRC = src/main.c src/kmp.c
OBJ = $(patsubst src/%.c, %.o, $(SRC))
EXE = kmp

all: $(EXE)

%.o: src/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o $(EXE)

