#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
class ground
{
private: 
	float movement; 
	sf::Vector2f dir; 
	sf::Texture groundtex; 
	sf::Sprite groundsprite; 

public: 
	ground(float dir_x, float dir_y, float pos_x, float pos_y, float movement); 

	// function
	void update(); 
	void render(sf::RenderTarget* target);
	sf::FloatRect getbounds();

};

