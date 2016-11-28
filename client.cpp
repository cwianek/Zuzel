#include "headers.h"

#define BUF_SIZE 1000

int PORT = 1234;
char * SERVER_ADDR = "127.0.0.1";

Player * enemy;
void * receiveMessage(void * socket);

int main(){

    Game game;
    enemy = new Player(300,300,20,5);
    Player * player = new Player(400,300,20,5);

    game.setEnemy(*enemy);
    game.setPlayer(*player);

    int sock = createSocket();
    connectServer(sock,PORT,SERVER_ADDR);
    createThreadForCommunication(sock,receiveMessage);
    game.setSocket(sock);

    game.run();

    return 0;
}

void * receiveMessage(void * socket) {
    int sockfd = (intptr_t) socket;

    while(1) {
        Message message;
        read(sockfd, (void*)&message, sizeof(Message));
        enemy->body.setPosition(message.x, message.y);
        enemy->body.setRotation(message.rot);
    }
}

