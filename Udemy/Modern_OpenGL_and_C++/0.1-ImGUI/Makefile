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

all: imgui library app

imgui:\
	$(OBJ)/imgui.o\
	$(OBJ)/imgui_demo.o\
	$(OBJ)/imgui_draw.o\
	$(OBJ)/imgui_impl_glfw.o\
	$(OBJ)/imgui_impl_opengl3.o\
	$(OBJ)/imgui_tables.o\
	$(OBJ)/imgui_widgets.o\
	

$(OBJ)/%.o: $(SRC)/ImGUI/%.cpp
	$(CC) -c $< -I $(INCLUDE)/ImGUI/ $(FLAGS) $(LIBS) -o $@

library:\
	$(OBJ)/window.o\
	$(OBJ)/mesh.o\
	$(OBJ)/shader.o\

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