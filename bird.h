#pragma once
#include<SFML/Graphics.hpp>
class bird
{
private: 
	sf::Texture birdtex1; 
	sf::Texture birdtex2;
	sf::Sprite birdsprite; 
	
	float gravity, speed; 
	bool isflapping;
	sf::Event event; 
	// function 
	void initbird(); 
	void initvariable(); 
public: 
	bool iskeypressed; 
	bird(); 

	void update();
	void render(sf::RenderTarget* target);

	sf::FloatRect getbounds();

	sf::Vector2f getpos();

};

