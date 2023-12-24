SFML_INCLUDE_PATH = ./SFML-2.5.1/include
SFML_LIB_PATH = ./SFML-2.5.1/lib
STACK_SIZE = 60000000  # Set the desired stack size here (e.g., 16 MB)

all: compile link

compile:
	g++ -c -std=c++17 *.cpp -I$(SFML_INCLUDE_PATH) -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas

	g++ -c -std=c++17 ./Reuseable/*.cpp -I$(SFML_INCLUDE_PATH) -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas
	g++ -c -std=c++17 ./RPN/*.cpp -I$(SFML_INCLUDE_PATH) -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas
	g++ -c -std=c++17 ./Pratt/*.cpp -I$(SFML_INCLUDE_PATH) -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas
	g++ -c -std=c++17 ./Text/*.cpp -I$(SFML_INCLUDE_PATH) -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas
	g++ -c -std=c++17 ./Expression/*.cpp -I$(SFML_INCLUDE_PATH) -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas
	g++ -c -std=c++17 ./IMGUI/*.cpp -I$(SFML_INCLUDE_PATH) -DSFML_STATIC -O2 

link:
	g++ *.o -o main -L$(SFML_LIB_PATH) -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lsfml-main -Wl,--stack,$(STACK_SIZE)
