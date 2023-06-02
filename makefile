CC=gcc
FLAGS=-Wall -g

SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
INCS=-I${SDL_INC_DIR}
BIB=../__BIBLIOTHEQUE/

all: main.o biblio.o
	${CC} ${FLAGS} biblio.o main.o -o EscGame ${LIBS} ${INCS}
	
biblio.o: ${BIB}gen.c ${BIB}gen.h
	${CC} -c ${FLAGS} ${BIB}gen.c -o biblio.o ${LIBS} ${INCS}

main.o: main.c 
	${CC} -c ${FLAGS} main.c -o main.o ${LIBS} ${INCS}


