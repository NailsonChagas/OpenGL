EXECUTAVEL = teste6
BIN = ./bin
MAIN = ./main/main.cpp

FLAGS = -O3 -Wall 
LIBS = -lglfw -lGL -lGLEW -Iglm

all: app

app: 
	g++ $(MAIN) $(FLAGS) $(LIBS) -o $(BIN)/$(EXECUTAVEL)

run:
	$(BIN)/$(EXECUTAVEL)

cleanBin:
	rm $(BIN)/*

purge:
	rm $(BIN)/*	