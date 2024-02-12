#pragma once
#include<SFML/Graphics.hpp>
class pipes
{
private: 
	sf::Sprite pipesprite; 
	float movementspeed; 
	sf::Vector2f dir;
	sf::Vector2f scale; 
public: 
	pipes(sf::Texture *pipetex, float pos_x, float pos_y, float dir_x, float dir_y, float movementspeed); 
	void update(); 
	void render(sf::RenderTarget* target); 
	sf::FloatRect getbounds(); 
};

