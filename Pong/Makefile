flags := -Wall -Wextra -std=c++17
linkers := -lraylib -lm -lpthread

raylib: main.cpp
	g++ -O2 $(flags) main.cpp -o pong $(linkers) && ./pong
