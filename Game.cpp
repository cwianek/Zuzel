#include "headers.h"

void Game::run(){
    
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
    
    sf::Texture texture;
    texture.loadFromFile("background.jpg");
    sf::Image image = texture.copyToImage();
    sf::Sprite background;
    sf::Color color = image.getPixel(10,10);
    background.setTexture(texture,true);
    
    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.f/60.f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    
          while (window.isOpen())
        {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
                
            if(event.type == sf::Event::GainedFocus) 
                focus = true;
                
            if(event.type == sf::Event::LostFocus) 
                focus = false;
        }
        
        
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > timePerFrame){
            timeSinceLastUpdate -= timePerFrame;   
            
            float elapsedTime = timePerFrame.asMilliseconds();
            player->setElapsedTime(elapsedTime);
            if(focus) player->checkInput(elapsedTime);
            player->move(elapsedTime);
            sendPosition(player->body,*socket);
            checkCollision(*player,image);
        } 
        
      
       window.clear();
       window.draw(background);
       
       player->draw(window);
       enemy->draw(window);
       window.display();
       
    }
    

}

void Game::checkCollision(Player &player,sf::Image &image){
      float xShape = player.body.getPosition().x;
      float yShape = player.body.getPosition().y;
      
      sf::Color color = image.getPixel(xShape,yShape);
      if(color.r == 0 && color.g==60 && color.b == 81){
        player.slowDown = true;
      }else{
        player.slowDown = false;
      }
      
}

void Game::setEnemy(Player &enemy){
    this->enemy = &enemy;
    this->enemy->body.setFillColor(sf::Color::Red);
}

void Game::setPlayer(Player &player){
    this->player = &player;
    this->player->body.setFillColor(sf::Color::Blue);
}

void Game::setSocket(int & socket){
    this->socket = &socket;
}

void Game::sendPosition(sf::RectangleShape &shape,int &sock){
    char posX[10];
    char posY[10];
    char rotation[10];
 
    sprintf(posX,"%f",shape.getPosition().x);
    sprintf(posY,"%f",shape.getPosition().y);
    sprintf(rotation,"%f",shape.getRotation());
    
    posX[9] = 1;
    write(sock,posX,sizeof(posX));
    
    posY[9] = 2;
    write(sock,posY,sizeof(posY));
    
    rotation[9] = 3;
    write(sock,rotation,sizeof(rotation));
}
