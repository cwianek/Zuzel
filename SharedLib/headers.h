#pragma once

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <string>
#include <pthread.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "sockets.h"
#include "Player.h"
#include "Game.h"

const int WIDTH = 650;
const int HEIGHT = 479;

struct Message {
    float x;
    float y;
    float rot;
};
