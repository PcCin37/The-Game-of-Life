
# code details

EXE = ./lifegame
SRC= main.c menu.c game.c test.c

# generic build details

CC=      gcc
CFLAGS= -std=c99 -Wall
CLINK= -lSDL2 -lSDL2_image

# compile to object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

# build executable: type 'make'

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CLINK) -o $(EXE) 

# clean up and remove object code and executable: type 'make clean'

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o: main.c game.h menu.h
menu.o: menu.c menu.h game.h
game.o: game.c game.h
test.o: test.c


