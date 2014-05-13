CXX = clang++
CXXFLAGS = -Wall -std=c++11

choice_game: main.o Player.o Weapon.o
	$(CXX) -o $@ $^
