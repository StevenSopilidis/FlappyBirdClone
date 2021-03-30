#pragma once



class Pipe
{
public:
	float top_pipe_height;
	float bottom_pipe_height;
	sf::Sprite bottomPipe;
	sf::Sprite topPipe;
	Pipe(sf::Texture& pipeTexture,int WINDOW_WIDTH,int WINDOW_HEIGHT);
	void updatePipePosition(sf::Time& dt);
	static void genNewPipe(std::vector<Pipe *>& pipes, sf::Texture& pipeTexture, const float WINDOW_WIDTH, const float WINDOW_HEIGHT,int& currentScore);
private:
	const float PIPE_SPEED = 160.f;
};


