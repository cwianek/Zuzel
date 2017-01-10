#include "headers.h"

const int PORT = 1234;

Player * enemy;
void * receiveMessage(void * socket);

int main(){

    Game game;
    enemy = new Player(300,350,20,5);
    Player * player = new Player(300,320,20,5);

    game.setEnemy(*enemy);
    game.setPlayer(*player);

    int sock = createSocket();
    bindSocketServer(sock,PORT);
    listen(sock,QUEUE_SIZE);
    int clientSock = handleConnection(sock,receiveMessage); //thread will die when program ends

    game.setSocket(clientSock);
    game.run();
	
    close(sock);

    return 0;
}


void * receiveMessage(void * socket) {
    int sockfd = (intptr_t) socket;

    while(1) {

        Message message;

        read(sockfd,(void*)&message,sizeof(Message));

        enemy->body.setPosition(message.x, message.y);
        enemy->body.setRotation(message.rot);

    }
}



