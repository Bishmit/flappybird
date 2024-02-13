#include "pipes.h"

pipes::pipes(sf::Texture* pipetex, float pos_x, float pos_y, float dir_x, float dir_y, float movementspeed)
{
	pipesprite.setTexture(*pipetex); 
	pipesprite.setPosition(pos_x, pos_y); 
	dir.x = dir_x; 
	dir.y = dir_y;
	this->movementspeed = movementspeed; 
}

void pipes::update()
{
		this->pipesprite.move(this->movementspeed * this->dir);
}

void pipes::render(sf::RenderTarget* target)
{
	target->draw(pipesprite); 
}

sf::FloatRect pipes::getbounds()
{
	return pipesprite.getGlobalBounds();
}


sf::Vector2f pipes::getpos()
{
	return pipesprite.getPosition();
}
