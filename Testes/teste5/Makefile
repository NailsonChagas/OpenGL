EXECUTAVEL = teste5
BIN = ./bin
MAIN = ./main/main.cpp
SRC = ./src
INCLUDE = ./include
OBJ = ./obj

FLAGS = -O3 -Wall 
LIBS = -lglfw -lGL -lGLEW -Iglm

all: library app

library: \
	$(OBJ)/vetor.o

#gera os .o
$(OBJ)/%.o: $(SRC)/%.cpp $(INCLUDE)/%.hpp
	g++ -c $< -I$(INCLUDE) $(LIBS) $(FLAGS) -o $@

app: 
	g++ $(MAIN) $(FLAGS) -I$(INCLUDE) $(LIBS) $(OBJ)/*.o -o $(BIN)/$(EXECUTAVEL)

run:
	$(BIN)/$(EXECUTAVEL)

cleanObj:
	rm $(OBJ)/*.o

cleanBin:
	rm $(BIN)/*

purge:
	rm $(OBJ)/*.o
	rm $(BIN)/*	