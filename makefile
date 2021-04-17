# Copyright 2021 AvaniSheth asheth@bu.edu
# Copyright 2021 SamanthaDowning sdown@bu.edu
# all: adjustableclock

# adjustableclock: adjustableclock.cpp
# 	g++ adjustableclock.cpp -o adjustableclock -lsfml-graphics -lsfml-window -lsfml-systems
all: game

game: game.cpp
	g++ game.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system