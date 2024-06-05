all : main.o
	g++ -o BS BattleShip.o Map.o Grid.o Game.o Ship.o 

main.o: game.o
	g++ -o BattleShip.o -c BattleShip.cpp

game.o: map.o grid.o ship.o
	g++ -o Game.o -c Game.cpp

map.o: grid.o ship.o
	g++ -o Map.o -c Map.cpp

grid.o:
	g++ -o Grid.o -c Grid.cpp

ship.o:
	g++ -o Ship.o -c Ship.cpp

clean:
	rm -f *.o