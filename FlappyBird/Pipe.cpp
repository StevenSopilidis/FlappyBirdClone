#include <SFML/Graphics.hpp>
#include "Pipe.h"
#include <iostream>

Pipe::Pipe(sf::Texture& pipeTexture, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
	bottomPipe = sf::Sprite(pipeTexture);
	//inititalize top pipe
	bottomPipe.setTexture(pipeTexture);
	//generate a rand scale for the pipe between 0.4 and 1.3
	srand(time(0) + 60);
	float bottom_pipe_random_height_scale = (rand() % 10);
	bottom_pipe_random_height_scale = bottom_pipe_random_height_scale / 10;
	this->bottom_pipe_height = bottom_pipe_random_height_scale * 320;
	bottomPipe.setScale(1, bottom_pipe_random_height_scale);
	//if the top_pipe_random_height_scale is greated that 1.2 scale it down a little
	bottomPipe.setPosition(WINDOW_WIDTH, WINDOW_HEIGHT - (320 * bottom_pipe_random_height_scale));

	//initialize bottom pipe
	topPipe.setTexture(pipeTexture);
	topPipe.setOrigin(26, 160);
	float top_pipe_scale = 1.2 - bottom_pipe_random_height_scale;
	this->top_pipe_height = 320 * top_pipe_scale;
	topPipe.setScale(1, top_pipe_scale);
	topPipe.setRotation(180);
	topPipe.setPosition(WINDOW_WIDTH + 26, 160 * top_pipe_scale);
}

void Pipe::updatePipePosition(sf::Time& dt)
{
	bottomPipe.setPosition(
		bottomPipe.getPosition().x - PIPE_SPEED * dt.asSeconds(),
		bottomPipe.getPosition().y
	);
	topPipe.setPosition(
		bottomPipe.getPosition().x - PIPE_SPEED * dt.asSeconds() + 26,
		topPipe.getPosition().y
	);
}

void Pipe::genNewPipe(std::vector<Pipe *>& pipes, sf::Texture& pipeTexture, const float WINDOW_WIDTH,const float WINDOW_HEIGHT,int& currentScore)
{
	if (pipes.size() == 1)
	{
		if (pipes[0]->bottomPipe.getPosition().x < WINDOW_WIDTH / 2)
		{
			pipes.push_back(new Pipe(pipeTexture, WINDOW_WIDTH, WINDOW_HEIGHT));
		}
	}

	//if the first pipe is getting out of the scene
	if (pipes[0]->bottomPipe.getPosition().x < -60)
	{
		Pipe* new_pipe = new Pipe(pipeTexture, WINDOW_WIDTH, WINDOW_HEIGHT);
		std::vector<Pipe*> new_pipe_vector{pipes[1], new_pipe};
		pipes = new_pipe_vector;
		currentScore++;
	}

}