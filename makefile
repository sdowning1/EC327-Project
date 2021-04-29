all: memory_game

memory_game: final_memorygame2.cpp
	g++ final_memorygame2.cpp -o memory -lsfml-graphics -lsfml-window -lsfml-system
