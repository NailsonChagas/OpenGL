MAIN = ./main/main.c
BIN = ./bin
#PATHGLFW = /usr/include/GLFW  
#PATHGL = /usr/include/GL
#LIBS = -lglfw -lGL -L$(PATHGLFW) -L$(PATHGL)
LIBS = -lglfw -lGL

all:
	gcc $(MAIN) $(LIBS) -o $(BIN)/teste

run:
	$(BIN)/teste

clear:
	rm $(BIN)/*