#pragma once
#include<SFML/Graphics.hpp>
class bird
{
private: 
	sf::Texture birdtex1; 
	sf::Texture birdtex2;
	sf::Sprite birdsprite; 
	bool isflapping;
	float gravity, speed; 
	sf::Event event; 
	// function 
	void initbird(); 
	void initvariable(); 
public: 
	bird(); 

	void update();
	void render(sf::RenderTarget* target);

};

