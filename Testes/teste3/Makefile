EXECUTAVEL = teste3
MAIN = ./main/main.cpp
BIN = ./bin

FLAGS = -O3 -Wall
LIBS = -lglfw -lGL

all:
	g++ $(MAIN) $(LIBS) $(FLAGS) -o $(BIN)/$(EXECUTAVEL)

run:
	$(BIN)/$(EXECUTAVEL)

clean:
	rm $(BIN)/*