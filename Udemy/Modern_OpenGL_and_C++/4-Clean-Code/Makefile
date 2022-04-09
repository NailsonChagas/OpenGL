EXECUTAVEL = janela
CC = g++

FLAGS = -O3 -g -Wall -no-pie -D_FORTIFY_SOURCE=2 -grecord-gcc-switches
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW

MAIN = ./main/main.cpp
INCLUDE = ./include
SRC = ./src
OBJ = ./obj
BIN = ./bin

EXT = .c
ifeq ($(CC), g++)
	EXT = .cpp
endif

all: library app

library:\
	$(OBJ)/window.o\
	$(OBJ)/mesh.o\
	$(OBJ)/shader.o

$(OBJ)/%.o: $(SRC)/%.cpp $(INCLUDE)/%.h
	$(CC) -c $< -I $(INCLUDE) $(FLAGS) $(LIBS) -o $@

app:
	$(CC) $(MAIN) $(OBJ)/*.o $(FLAGS) $(LIBS) -I  $(INCLUDE) -o $(BIN)/$(EXECUTAVEL)

run:
	$(BIN)/$(EXECUTAVEL)

clearBin:
	rm $(BIN)/*

clearObj:
	rm $(OBJ)/*.o

purge:
	rm $(OBJ)/*.o
	rm $(BIN)/*