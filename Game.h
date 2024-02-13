#include "SFML/Graphics.hpp"
#include"bird.h"
#include"pipes.h"
#include<memory>
#include<vector>
#include<unordered_map>
#include<iostream>
#include<cstdlib>
#include<ctime>
class Game {
private: 
	// variable
	sf::Event event; 
	sf::Texture bgtex; 
	sf::Sprite bgsprite;  
	sf::Text text; 
	sf::Font font; 

	std::unique_ptr<sf::RenderWindow> window; 
	std::unordered_map<std::string, std::unique_ptr<sf::Texture>> pipemap; 
	std::vector<std::unique_ptr<pipes>> p; 
	std::vector<std::unique_ptr<pipes>> p1;

	// private function
	void initwindow();
	void inittexture();
	void initvaraible();
	void pollevents();
	bird b; 
	int randno, randnoforpipe2, score; 
	bool gameover, is_scored; 
public: 
	Game(); 
	// public function
	const bool isGameRunning() const;
	void initpipetexture();
	void movepipe();
	void deletepipe();
	void birdpipecollison();
	void scoresystem();
	void update(); 
	void render(); 
 };