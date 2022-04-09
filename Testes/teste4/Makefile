EXECUTAVEL = teste4
MAIN = ./main/main.cpp
BIN = ./bin

FLAGS = -O3 -Wall
LIBS = -lglfw -lGL -lGLEW

all:
	g++ $(MAIN) $(LIBS) $(FLAGS) -o $(BIN)/$(EXECUTAVEL)

run:
	$(BIN)/$(EXECUTAVEL)

clean:
	rm $(BIN)/*