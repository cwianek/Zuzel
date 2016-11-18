#pragma

#include "headers.h"

class Game{

public:
      Player * enemy;
      Player * player;
      bool focus;
      int * socket;
      void run();
      void checkCollision(Player &player,sf::Image &image);
      void setEnemy(Player & enemy);
      void setPlayer(Player & player);
      void setSocket(int & socket);
      void sendPosition(sf::RectangleShape &shape,int &sock);
};
