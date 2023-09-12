CC=gcc

FLAGS=-Wall -g

SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include

fich= testsdl.o suis_souris.o

LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
INCS=-I${SDL_INC_DIR}

SRC=src/
HDIR=lib/

PROG=sdl_test

all: test

test: ${fich}
	${CC} ${FLAGS} ${fich} -o ${PROG} ${LIBS} ${INCS}

testsdl.o: ${SRC}testsdl.c 
	${CC} -c ${FLAGS} ${SRC}testsdl.c -o testsdl.o ${LIBS} ${INCS}

suis_souris.o: ${SRC}suis_souris.c ${HDIR}suis_souris.h
	${CC} -c ${FLAGS} ${SRC}suis_souris.c -o suis_souris.o ${LIBS} ${INCS}

clean:
	rm -f ${PROG}
	rm -f *.o

cleano:
	rm -f *.o