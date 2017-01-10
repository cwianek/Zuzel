#include "headers.h"

const int NUM_LAPS = 5;

void Game::run(){

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    sf::Texture texture;
    texture.loadFromFile("background.jpg");
    sf::Image image = texture.copyToImage();
    sf::Sprite background;
    background.setTexture(texture,true);

    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.f/60.f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
    sf::Font font;
    font.loadFromFile("arial.ttf");
    
    sf::Text playerLapsText;
    sf::Text enemyLapsText;
    playerLapsText.setFont(font);
    enemyLapsText.setFont(font);

    int playerLap = 1;
    int enemyLap = 1;
    bool start = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
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
            if(focus)player->checkInput(elapsedTime);
            player->move(elapsedTime);
            sendPosition(player->body,*socket);
            checkCollision(*player,image);
	    trackPositions(player->body,checkPoints);
	    trackPositions(enemy->body,enemyCheckPoints);

            displayLaps(enemyLapsText,playerLapsText, playerLap, enemyLap);
	    playerLap = checkIfLapDone(player->body,playerLap,checkPoints);
            enemyLap = checkIfLapDone(enemy->body,enemyLap,enemyCheckPoints);
	    handleEndOfGame(window,playerLap,enemyLap,font);
        } 
	
        window.clear();
        window.draw(background);

        player->draw(window);
        enemy->draw(window);
	window.draw(playerLapsText);
	window.draw(enemyLapsText);
        window.display();
	
	if(!start){
	handleStart(window,clock, background);
	start = true;
}
    }
}

void Game::handleEndOfGame(sf::RenderWindow & window, int laps1, int laps2,sf::Font & font){
	if(laps1 > NUM_LAPS){
		sf::Text text;
		text.setFont(font);
		getTextFromInt(0,text,sf::Vector2f(100,150),100);
		text.setString("Player wins");
		endGame(window,text);
	}else if(laps2 > NUM_LAPS){
		sf::Text text;
		text.setFont(font);
		getTextFromInt(0,text,sf::Vector2f(100,150),100);
		text.setString("Enemy wins");
		endGame(window,text);
	}
}

void Game::endGame(sf::RenderWindow & window, sf::Text & text){
		window.draw(text);
		window.display();
		sleep(3);
		window.close();
}

int Game::checkIfLapDone(sf::RectangleShape body,int lap,bool checkPoints[]){

	if(checkPoints[0] && checkPoints[1] && body.getPosition().x > 240){
		lap+=1;
		checkPoints[0] = false;
		checkPoints[1] = false;
	}
	return lap;
}

void Game::displayLaps(sf::Text & enemyLaps, sf::Text & playerLaps, int playerLap, int enemyLap){
            getTextFromInt(enemyLap,enemyLaps,sf::Vector2f(550,10),15);
	    sf::String s = enemyLaps.getString();
	    enemyLaps.setString("Enemy:  " + s + " lap");
            getTextFromInt(playerLap,playerLaps,sf::Vector2f(550,30),15);
	    s = playerLaps.getString();
	    playerLaps.setString("Player:  " + s + " lap");
}

void Game::trackPositions(sf::RectangleShape & shape, bool checkPoints[]){
	
	if(shape.getPosition().x > WIDTH - 175 && !checkPoints[0]){
		checkPoints[0] = true;
	
	}else if(shape.getPosition().x < 175 && !checkPoints[1]){
		checkPoints[1] = true;
	}
}

void Game::handleStart(sf::RenderWindow & window, sf::Clock & clock, sf::Sprite & background){
		sf::Font font;
	font.loadFromFile("arial.ttf");
		sf::Text text;
		text.setFont(font);

		for(int i=3;i>0;i--){		
			getTextFromInt(i,text,sf::Vector2f(300,180),80);		

	       		window.clear();
	        	window.draw(background);

	 	       	player->draw(window);
	        	enemy->draw(window);
			window.draw(text);
	        	window.display(); 
			sleep(1);
		}
		clock.restart();
}

void Game::getTextFromInt(int i, sf::Text &text, sf::Vector2f pos,int size){
	std::stringstream ss;
	ss << i;

       	text.setString(ss.str());
	text.setCharacterSize(size);
	text.setColor(sf::Color::White);
	text.setPosition(pos);
}

void Game::checkCollision(Player &player,sf::Image &image){
    float xShape = player.body.getPosition().x;
    float yShape = player.body.getPosition().y;

    sf::Color color = image.getPixel(xShape,yShape);
    if(color.r == 1 && color.g==98 && color.b == 151){
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
    Message message;

    message.x = shape.getPosition().x;
    message.y = shape.getPosition().y;
    message.rot =  shape.getRotation();

    write(sock,(void*)&message,sizeof(Message));
    
}
