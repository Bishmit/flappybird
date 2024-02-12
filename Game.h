#include "SFML/Graphics.hpp"
#include"bird.h"
#include"pipes.h"
#include<vector>
#include<map>
#include<iostream>
#include<cstdlib>
#include<ctime>
class Game {
private: 
	// variable
	sf::RenderWindow* window; 
	sf::Event event; 
	sf::Texture bgtex; 
	sf::Sprite bgsprite;  

	// private function
	void initwindow();
	void inittexture();
	void initvaraible();

	void pollevents();
	std::map<std::string, sf::Texture*> pipemap; 
	bird b;
	std::vector<pipes*>p, p1; 
	int randno, randnoforpipe2; 
public: 
	Game(); 
	~Game(); 
	// public function
	const bool isGameRunning() const;
	void initpipetexture();
	void movepipe();
	void deletepipe();
	void deleteanotherpipe();
	void movebird();
	void update(); 
	void render(); 
 };