SFML_INCLUDE_PATH = ./SFML-2.5.1/include
SFML_LIB_PATH = ./SFML-2.5.1/lib
STACK_SIZE = 60000000  # Set the desired stack size here (e.g., 16 MB)

all: compile link

compile:
	g++ -c *.cpp -I$(SFML_INCLUDE_PATH) -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas

	g++ -c ./Reuseable/*.cpp -I$(SFML_INCLUDE_PATH) -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas
	g++ -c ./RPN/*.cpp -I$(SFML_INCLUDE_PATH) -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas

link:
	g++ *.o -o main -L$(SFML_LIB_PATH) -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lsfml-main -Wl,--stack,$(STACK_SIZE)
