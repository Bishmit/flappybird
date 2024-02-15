#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
class bird
{
private: 
	sf::Texture birdtex1; 
	sf::Texture birdtex2;
	sf::Sprite birdsprite; 

	sf::SoundBuffer wingbuffer;
	sf::Sound wingsound;
	
	float gravity, speed; 
	bool isflapping;
	sf::Event event; 
	// function 
	void initbird(); 
	void initvariable(); 
public: 
	bool iskeypressed,is_flying; 
	bird(); 

	void update();
	void restrictboundarycollison(const sf::RenderWindow* target);
	void render(sf::RenderTarget* target);

	sf::FloatRect getbounds();

	sf::Vector2f getpos();

	void setposition(float,float);

};

