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
	this->gravity = 2.f; 
	this->speed = -5.f; 
}

bird::bird():isflapping(false)
{
	initbird(); 
	initvariable(); 
}

void bird::update()
{
	birdsprite.move(0.f, gravity*1.5f); 
	birdsprite.setTexture(birdtex2);
	static sf::Clock cooldownClock;
	const sf::Time cooldownTime = sf::milliseconds(200);
	if (cooldownClock.getElapsedTime() >= cooldownTime && !is_flying) {
		birdsprite.setTexture(birdtex1);
		cooldownClock.restart();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !iskeypressed) {
		isflapping = true; 
		
		this->birdsprite.move(0,this->speed);
		float rotation = birdsprite.getRotation();
		if (rotation >= -15.f) {
			birdsprite.setRotation(-15.f); // Set rotation to -15 degrees
		}
	}
	else {
		isflapping = false; 
		float rotation = birdsprite.getRotation();
		if (rotation >= 15.f) {
			birdsprite.setRotation(15.f); // Set rotation to 15 degrees
		}
	}
}

void bird::restrictboundarycollison(const sf::RenderWindow *target) {
	if (this->birdsprite.getGlobalBounds().top <= 0.f) {
		this->birdsprite.setPosition(this->birdsprite.getGlobalBounds().left, 3.f);
	}
	if (this->birdsprite.getGlobalBounds().top + this->birdsprite.getGlobalBounds().height >= target->getSize().y) {
		this->birdsprite.setPosition(0.f+ this->birdsprite.getGlobalBounds().left, target->getSize().y - this->birdsprite.getGlobalBounds().height);
	}
}

void bird::render(sf::RenderTarget* target)
{
	target->draw(birdsprite); 
}

sf::FloatRect bird::getbounds()
{
	return birdsprite.getGlobalBounds();
}
sf::Vector2f bird::getpos()
{
	return birdsprite.getPosition();
}
