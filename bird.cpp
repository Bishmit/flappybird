#include "bird.h"
#include<iostream>

void bird::initbird()
{
	if (!birdtex1.loadFromFile("Assets/birddown.png") || !birdtex2.loadFromFile("Assets/birdup.png")) {

	}
	birdsprite.setTexture(birdtex1); 
	birdsprite.setPosition(10.f, 10.f); 
	std::cout << "flap flap" << "\n"; 
}

void bird::initvariable()
{
	this->gravity = 0.2f; 
	this->speed = -0.15f; 
}

bird::bird():isflapping(false)
{
	initbird(); 
	initvariable(); 
}

void bird::update()
{
	birdsprite.move(0.f, gravity*0.5f); 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		isflapping = true; 
		birdsprite.setTexture(birdtex2);
		this->birdsprite.move(0,this->speed);
	}
	else {
		isflapping = false; 
		birdsprite.setTexture(birdtex1); 
	}
}

void bird::render(sf::RenderTarget* target)
{
	target->draw(birdsprite); 
}

