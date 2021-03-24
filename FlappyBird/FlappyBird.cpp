#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;
//func to return the size we need the backgroundSprite to be resized to
void setBackgroundSpriteTargetSize(Sprite & backgroundSprite);
//func to change the height of the bird sprite
void decreaseBirdHeight(Sprite& birdSprite, Time &dt);
void increaseBirdHeight(Sprite& birdSprite, Time& dt);
//func to change the rotating of the bird
void changeBirdRotation(Sprite& birdSprite, Time& dt, float& birdRot);
//func to check if the player has lost
bool playerHasLost(Sprite& birdSprite, RenderWindow& window);

//windows height and width
const int WINDOW_WIDTH = 640.0f;
const int WINDOW_HEIGHT = 480.0f;

//how much height will the bird gain every time the user flaps the wings
const int WINGS_FLAPPED = 700;
//how much height the bird is losing if not wings were flopeed
const int HEIGHT_LOSS = 120;

//max number of pipes in the screen
const int MAX_PIPES_IN_SCREEN = 2;

int main()
{
	VideoMode vm(640, 480);
	RenderWindow window(vm, "Flappy Bird", Style::Titlebar);

	//for the background
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("graphics/bg.png");
	Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	//resize the sprite
	setBackgroundSpriteTargetSize(backgroundSprite);
	//load the pipe texture
	Texture pipeTexture;
	pipeTexture.loadFromFile("graphics/pipe.png");
	//for the bird
	//when the bird is not flopping the wings
	Texture birdTexture1;
	birdTexture1.loadFromFile("graphics/bird2.png");
	//when the bird has just flopped the wings
	Texture birdTexture2;
	birdTexture2.loadFromFile("graphics/bird3.png");
	//when the wing flopping has just stopped
	Texture birdTexture3;
	birdTexture3.loadFromFile("graphics/bird1.png");
	//the bird will start withoud an wing flopping
	Sprite birdSprite;
	birdSprite.setTexture(birdTexture1);
	//set the original position of the bird
	birdSprite.setPosition(50, 240);


	//setup for the pipes
	Sprite topPipe;
	//code for top pipe
	topPipe.setTexture(pipeTexture);
	//generate a rand scale for the pipe between 0.4 and 1.3
	srand(time(0) +60);
	float random_height_scale = ( rand() % 16 ) + 0.2;
	random_height_scale = random_height_scale / 10;
	topPipe.setScale(1, random_height_scale);
	topPipe.setPosition(WINDOW_WIDTH - 300, WINDOW_HEIGHT - (320 * random_height_scale));

	//code for bottom pipe


	//my var to keep count of the rotation of the bird
	float birdRot = 0.f;

	Clock clock;
	while (window.isOpen())
	{
		Time dt = clock.restart();
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			if (birdSprite.getRotation() > -45.f)
			{
				birdSprite.setRotation(-45.f);
				birdRot = -45.f;
			}
			increaseBirdHeight(birdSprite, dt);
		}
		changeBirdRotation(birdSprite, dt, birdRot);
		decreaseBirdHeight(birdSprite, dt);
		//check if the bird has hit the roof or the bottom
		bool lost = playerHasLost(birdSprite, window);
		if (lost)
		{
			//window.close();
		}

		window.clear();
		window.draw(backgroundSprite);
		window.draw(birdSprite);
		window.draw(topPipe);
		window.display();
	};
	return 0;
}

void setBackgroundSpriteTargetSize(Sprite& backgroundSprite)
{
	//get the size of the background spite in pexels
	float backgroudSpriteWidth = backgroundSprite.getTexture()->getSize().x;
	float backgroudSpriteHeight = backgroundSprite.getTexture()->getSize().y;
	//targetSize of the backgroundSprite
	Vector2f targetSize(WINDOW_WIDTH / backgroudSpriteWidth, WINDOW_HEIGHT / backgroudSpriteHeight);
	backgroundSprite.setScale(targetSize.x, targetSize.y);
}
void decreaseBirdHeight(Sprite& birdSprite, Time& dt)
{
	//decrement the y position of the bird if no wings were flopped
	birdSprite.setPosition
	(
		birdSprite.getPosition().x,
		birdSprite.getPosition().y + (HEIGHT_LOSS * dt.asSeconds())
	);
}
void increaseBirdHeight(Sprite& birdSprite, Time& dt)
{
	//decrement the y position of the bird if no wings were flopped
	birdSprite.setPosition
	(
		birdSprite.getPosition().x,
		birdSprite.getPosition().y - (WINGS_FLAPPED * dt.asSeconds())
	);
}
void changeBirdRotation(Sprite& birdSprite, Time& dt, float& birdRot)
{
	//if bird rotation is between 45 and -45 deg decrease it 
	//untill it reaches -45deg
	if (birdRot <= 45.f && birdRot >= -45.f)
	{
		birdRot += (140 * dt.asSeconds());
		birdSprite.setRotation(birdRot);
	}
}
bool playerHasLost(Sprite& birdSprite, RenderWindow& window)
{
	if (birdSprite.getPosition().y <= 0 || birdSprite.getPosition().y >= WINDOW_HEIGHT)
	{
		//end the game
		return true;
	}

	return false;
}