choice_game: main.o Player.o Weapon.o
	clang -o choice_game main.o Player.o Weapon.o
main.o: main.cpp
	clang -c -o main.o main.cpp
Player.o: Player.cpp
	clang -c -o Player.o Player.cpp
Weapon.o: Weapon.cpp
	clang -c -o Weapon.o Weapon.cpp