all: serwer client
CC=g++
CFLAGS=
LFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -pthread -Wall
OBJS=sockets.o player.o game.o serwer.o
OBJS2=sockets.o player.o game.o client.o

serwer: $(OBJS)
	$(CC) $(OBJS) -o serwer $(LFLAGS)

client: $(OBJS2)
	$(CC) $(OBJS2) -o client $(LFLAGS)
	
sockets.o: sockets.cpp
	$(CC) $(CFLAGS) -c sockets.cpp -o sockets.o

player.o: Player.cpp
	$(CC) $(CFLAGS) -c Player.cpp -o player.o
	
game.o: Game.cpp
	$(CC) $(CFLAGS) -c Game.cpp -o game.o

client.o: client.cpp
	$(CC) $(CFLAGS) -c client.cpp -o client.o

serwer.o: serwer.cpp
	$(CC) $(CFLAGS) -c serwer.cpp -o serwer.o
