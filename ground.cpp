#include "ground.h"

ground::ground(float dir_x, float dir_y, float pos_x, float pos_y, float movement)
{
	if (!groundtex.loadFromFile("Assets/base.png")) {
		std::cout << "Error loading ground texture" << "\n"; 
	}
	//std::cout << "aaxa" << "\n"; 
	groundsprite.setTexture(groundtex); 
	groundsprite.setPosition(pos_x, pos_y); 
	dir.x = dir_x;
	dir.y = dir_y; 
	this->movement = movement; 
}

void ground::update()
{
	this->groundsprite.move(this->movement * this->dir);
}

void ground::render(sf::RenderTarget* target)
{
	target->draw(groundsprite); 
}

sf::FloatRect ground::getbounds()
{
	return groundsprite.getGlobalBounds();
}


